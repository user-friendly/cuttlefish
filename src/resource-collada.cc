/**
 * @file
 * Resources - XML definition file.
 */

#include "exception.h"
#include "resource.h"
#include "resource-collada.h"
#include "mesh.h"
#include "string_utils.h"

namespace cuttlefish
{
  using namespace rapidxml;
  using namespace Xml;
  
  ResourceCollada::ResourceCollada(const String &filename)
    :kFileName {filename}
  {
    doc_.parse<0>(buffer_.data());
    root_ = doc_.first_node("COLLADA");
    if (root_ == nullptr) {
      Exception e {"Collada file missing root element: "};
      e << filename;
      throw e;
    }
    XmlAttr attr = root_->first_attribute("version");
    if (attr == nullptr) {
      Exception e {"Could not determine Collada file version: "};
      e << filename;
      throw e;
    }
    // @TODO Check only major and minor versions.
    if (kVersion != attr->value()) {
      Exception e {"Unsupported Collada version "};
      e << attr->value() << ", file: " << kFileName;
      e << "\n\t" << "Currently supported version is: " << kVersion;
      throw e;
    }
  }

  cuttlefish::Mesh ResourceCollada::getMesh() const
  {
    cuttlefish::Mesh tmp_mesh {};
    
    // There can be multiple libraries, but we'll use only the first one.
    XmlNode tmp_node = root_->first_node("library_geometries"),
      mesh_node {}, polylist_node {};
    
    if (!tmp_node) {
      throw Exception {"No geometry libraries found."};
    }
    tmp_node = tmp_node->first_node("geometry");
    if (!tmp_node) {
      throw Exception {"No geometry, in library, found."};
    }

    Geometry geo {tmp_node};
    std::cout << "Found geometry: " << geo << std::endl;

    for (const Xml::Mesh& mesh : geo.meshes) {
      std::cout << "Found mesh: " << mesh << std::endl;

      for (const Source& src : mesh.sources) {
        std::cout << "\tFound source: " << src << std::endl;
      }
      std::cout << "\tFound vertices: " << mesh.vertices << std::endl;
      for (const Polylist& poly : mesh.polylists) {
        std::cout << "\tFound polylist: " << poly << std::endl;
      }
    }
    
    // @TODO Will the POD object be moved or copied?
    return tmp_mesh;
  }

  
  Xml::Element::Element(XmlNode node)
    :node {node}
  {
    tag = node->name();
    id << node->first_attribute("id");
    name << node->first_attribute("name");
  };

  Xml::Source::Source(XmlNode node)
    :Element {node}
  {
    // @TODO Sources can get quite complicated. Only
    //       implement the "common" case.
    XmlNode tmp {node->first_node("float_array")};
    if (!tmp) {
      std::ostringstream oss {};
      oss << "Source (" << id << ", " << name << ") does not have float_array element.";
      throw Exception(oss.str());
    }

    uint16_t count {0};
    XmlAttr attr {node->first_attribute("count")};
    if (attr && attr->value_size()) {
      count = boost::lexical_cast<uint8_t>(attr->value());
    }
    else {
      throw Exception("Source's float_array does not have a count attribute.");
    }
    std::cout << tmp->value() << std::endl;
  };

  Xml::Vertices::Vertices(XmlNode node)
    :Element {node}, input {}
  {
    if (!node) {
      throw Exception("Mesh has no vertices element");
    }
    XmlNode tmp {node->first_node("input")};
    if (!tmp) {
      throw Exception("No input element found");
    }
    String attr {};
    for (; tmp; tmp = tmp->next_sibling("input")) {
      attr << tmp->first_attribute("semantic");
      if (attr == "POSITION") {
        input = std::make_unique<Input>(tmp);
        break;
      }
    }
  };

  Xml::Input::Input(XmlNode node)
    :Element {node}
  {
    semantic << node->first_attribute("semantic");
    sourceId << node->first_attribute("source");
    if (!sourceId.empty() && sourceId[0] == '#') {
      sourceId.erase(0, 1);
    }
    if (node->first_attribute("offset") && node->first_attribute("offset")->value_size()) {
      offset = boost::lexical_cast<uint8_t>(node->first_attribute("offset")->value());
    }
  };

  Xml::Polylist::Polylist(XmlNode node)
    :Element {node}
  {
    materialId << node->first_attribute("material");
    XmlAttr attr {node->first_attribute("count")};
    count = castToNumber<uint32_t>(node->first_attribute("count"));
    
    StringView str {};
    XmlNode tmp_node = node->first_node("vcount");
    if (tmp_node && tmp_node->value_size()) {
      str = tmp_node->value();
      vcounts << str;
    }
    tmp_node = node->first_node("p");
    if (tmp_node && tmp_node->value_size()) {
      str = tmp_node->value();
      indices << str;
    }

    for (tmp_node = node->first_node("input"); tmp_node; tmp_node = tmp_node->next_sibling("input")) {
      inputs.push_back(Input {tmp_node});
    }
  };

  Xml::Mesh::Mesh(XmlNode node)
    :Element {node}, vertices {node->first_node("vertices")}
  {
    if (tag != "mesh") {
      throw Exception("Element is not 'mesh'");
    }
    XmlNode tmp {};
    for (tmp = node->first_node("source"); tmp; tmp = tmp->next_sibling("source")) {
      sources.push_back(std::move(Source {tmp}));
    }
    if (sources.size() <= 0) {
      throw Exception("Mesh has no source elements");
    }
    for (tmp = node->first_node("polylist"); tmp; tmp = tmp->next_sibling("polylist")) {
      polylists.push_back(std::move(Polylist {tmp}));
      Polylist& last = polylists.back();
      for (Input& x : last.inputs) {
        
      }
    }
    if (polylists.size() <= 0) {
      throw Exception("Mesh has no polylist elements (currently, the only geometric primitive supported)");
    }
  };

  Xml::Geometry::Geometry(XmlNode node)
    :Element {node}
  {
    if (tag != "geometry") {
      throw Exception("Element is not 'geometry'");
    }
    XmlNode tmp {};
    for (tmp = node->first_node("mesh"); tmp; tmp = tmp->next_sibling("mesh")) {
      meshes.push_back(std::move(Mesh {tmp}));
    }
  };

  String& operator<<(String& str, const XmlBase& base) {
    if (base && base->value_size() > 0) {
      str = base->value();
    }
    return str;
  };

  std::ostream& operator<<(std::ostream& out, const Xml::Element& e) {
    std::cout << "ResourceCollada::Element: " << e.tag << ", id: " << e.id << ", name: " << e.name;
    return out;
  };
  
  std::ostream& operator<<(std::ostream& out, const Xml::Polylist& p) {
    std::cout << "ResourceCollada::Element: " << p.tag << ", id: " << p.id << ", name: " << p.name;
    std::cout << " material: " << p.materialId << ", count: " << p.count;
    std::cout << ", vcount: ";
    for (auto x : p.vcounts) {
      std::cout << x << " ";
    }
    std::cout << " indices: ";
    for (auto x : p.indices) {
      std::cout << x << " ";
    }
    std::cout << " inputs: ";
    for (const Input& e : p.inputs) {
      std::cout << "[" << e.semantic << ", " << e.sourceId << ", " << e.offset << "] ";
    }
    return out;
  };
}
