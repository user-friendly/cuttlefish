/**
 * @file
 * Resources - XML definition file.
 */

#include "asset/resource.h"
#include "asset/collada.h"
#include "mesh.h"
#include "string_utils.h"

namespace cuttlefish::asset::collada {
  using namespace rapidxml;

  const CharType* kSupportedVersion {"1.4.1"};

  Mesh getMesh(const String &filename)
  {
    rapidxml::file<> buffer {filename.c_str()};
    rapidxml::xml_document<> doc {};
    doc.parse<0>(buffer.data());
    
    XmlNode root_node {doc.first_node("COLLADA")};

    if (std::strcmp(kSupportedVersion, root_node->first_attribute("version")->value()) != 0) {
      std::cerr << "Unsupported Collada version " << root_node->first_attribute("version")->value();
      std::cerr << ", file: " << filename << "\n\t" << "Currently supported version is: " << kSupportedVersion << std::endl;
      return Mesh {};
    }
    
    XmlNode geometry_node = root_node->first_node("library_geometries")->first_node("geometry");
    XmlNode mesh_node = geometry_node->first_node("mesh");
    // Probably won't be used?
    String mesh_name {geometry_node->first_attribute("name")->value()};

    // The float_array element of the vertices and normals.
    XmlNode vert_node {}, norm_node {};
    // Face (triangles) count for the whole mesh.
    std::uint16_t face_count {boost::lexical_cast<std::uint16_t>(mesh_node->first_node("polylist")->first_attribute("count")->value())},
      // Indices offsets, because COLLADA is that cool.
      vert_offset {}, norm_offset {},
      // Counts that will be retrieved from the float_array elements later on.
      vert_count {}, norm_count {}
    ;

    // The ids are not known in advance, as opposed to the general structure.
    String vert_id {}, norm_id {};
    for (XmlNode tmp_node = mesh_node->first_node("polylist")->first_node("input"); tmp_node; tmp_node = tmp_node->next_sibling("input")) {
      if (std::strcmp(tmp_node->first_attribute("semantic")->value(), "VERTEX") == 0) {
        vert_id = tmp_node->first_attribute("source")->value();
        vert_id.erase(0, 1);
        if (std::strcmp(mesh_node->first_node("vertices")->first_attribute("id")->value(), vert_id.c_str()) == 0) {
          vert_id = mesh_node->first_node("vertices")->first_node("input")->first_attribute("source")->value();
          vert_id.erase(0, 1);
        }
        vert_offset = boost::lexical_cast<std::uint16_t>(tmp_node->first_attribute("offset")->value());
      }
      else if (std::strcmp(tmp_node->first_attribute("semantic")->value(), "NORMAL") == 0) {
        norm_id = tmp_node->first_attribute("source")->value();
        norm_id.erase(0, 1);
        norm_offset = boost::lexical_cast<std::uint16_t>(tmp_node->first_attribute("offset")->value());
      }
    }

    for (XmlNode tmp_node = mesh_node->first_node("source"); tmp_node; tmp_node = tmp_node->next_sibling("source")) {
      if (std::strcmp(tmp_node->first_attribute("id")->value(), vert_id.c_str()) == 0) {
        vert_node = tmp_node->first_node("float_array");
      }
      else if (std::strcmp(tmp_node->first_attribute("id")->value(), norm_id.c_str()) == 0) {
        norm_node = tmp_node->first_node("float_array");
      }
    }

    // Get the number counts.
    vert_count = boost::lexical_cast<std::uint16_t>(vert_node->first_attribute("count")->value());
    norm_count = boost::lexical_cast<std::uint16_t>(norm_node->first_attribute("count")->value());

    Mesh mesh {};
    mesh.vertices.reserve(vert_count);
    mesh.normals.reserve(norm_count);

    // Finally do the actual data parsing.
    parseNumberList(mesh.vertices, vert_node->value());
    parseNumberList(mesh.normals, norm_node->value());

    StringView indices {mesh_node->first_node("polylist")->first_node("p")->value()};
    uint8_t len {}, icount {};
    for (auto iter = indices.begin(); iter <= indices.end(); iter++) {
      if (std::isdigit(*iter) || *iter == '-' || *iter == '.' || *iter == 'e') {
        len++;
      }
      else {
        if (len > 0) {
          if (icount % 2 == 0) {
            // TODO A better type deduction of the index's value type.
            mesh.vertIndices.push_back(boost::lexical_cast<IndexType>(iter - len, len));
          }
          else {
            // TODO A better type deduction of the index's value type.
            mesh.normIndices.push_back(boost::lexical_cast<IndexType>(iter - len, len));
          }
          icount++;
        }
        len = 0;
      }
    }
    
    return mesh;
  }

}
