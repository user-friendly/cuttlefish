/**
 * @file
 * Resources - XML definition file.
 */

#include "exception.h"
#include "resource.h"
#include "resource-collada.h"
#include "mesh.h"

namespace cuttlefish
{
  using namespace rapidxml;
  
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
    mesh_node = tmp_node->first_node("mesh");
    if (!mesh_node) {
      throw Exception {"No mesh, in geometry, found."};
    }
    polylist_node = mesh_node->first_node("polylist");
    if (!polylist_node) {
      throw Exception {"No polylist, in mesh, found."};
    }

    // 
    std::map<const String, XmlNode> mesh_elements {};

    String source_id {}, semantic {};
    std::map<const String, String> semantic_ids {
      {"VERTEX", {}},
      {"NORMAL", {}}
    };
    
    for (tmp_node = polylist_node->first_node("input"); tmp_node; tmp_node = tmp_node->next_sibling("input")) {
      if (tmp_node->first_attribute("semantic")) {
        semantic = tmp_node->first_attribute("semantic")->value();
        if (semantic_ids.count(semantic)) {
          semantic_ids[semantic] = tmp_node->first_attribute("source")->value();
          semantic_ids[semantic].erase(0, 1);
        }
      }
    }

    XmlNode tmp_node_fa {};

    auto extract_floats = [](XmlNode& node) {
          char *str_end {nullptr};
          uint16_t count {static_cast<uint16_t>(std::strtoul(node->first_attribute("count")->value(), &str_end, 10))};
          std::istringstream raw_floats {node->value()};
          FloatArray fa {std::istream_iterator<float>(raw_floats), std::istream_iterator<float>()};
          if (count != fa.size()) {
            Exception e {"Float array size mismatch, id: "};
            e << node->first_attribute("id")->value();
            throw e;
          }
          return fa;
    };
  
    
    for (tmp_node = mesh_node->first_node("source"); tmp_node; tmp_node = tmp_node->next_sibling("source")) {
      tmp_node_fa = tmp_node->first_node("float_array");
      if (!tmp_node_fa) {
        continue;
      }
      
      source_id = tmp_node->first_attribute("id")->value();
      if (source_id == semantic_ids["VERTEX"]) {
        String tag = tmp_node->name();
        if (tag == "vertices") {
          XmlNode verts = mesh_node->first_node("input");
          if (verts) {
            semantic = verts->first_attribute("semantic")->value();
            if (semantic == "POSITION") {
              source_id = verts->first_attribute("source")->value();
              source_id.erase(0, 1);
              
            }
          }
        }
        else {
          tmp_mesh.vertices = extract_floats(tmp_node_fa);
        }
      }
      else if (source_id == semantic_ids["NORMAL"]) {
        tmp_mesh.normals = extract_floats(tmp_node_fa);
      }
    }

    // @TODO Will the POD object be moved or copied?
    return tmp_mesh;
  }
}
