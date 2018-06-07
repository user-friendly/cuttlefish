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
      vert_count {}, norm_count {},
      // Index counts for vertices and normals.
      vert_index_count {}, norm_index_count {}
    ;
    // Set indices counts.
    vert_index_count = face_count * Mesh::faceVertCount;
    norm_index_count = face_count * Mesh::faceVertCount;
    
    // Ignore the vcount - we know we're dealing with triangles and that there are two sets - vectors and normals.
    IndexArray indices {};
    indices.reserve(vert_index_count + norm_index_count);
    // Later on, based on the offsets, this vector will be split by moving it.
    parseNumberList(indices, mesh_node->first_node("polylist")->first_node("p")->value());

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
    if (vert_offset == 0) {
      std::move(indices.begin(), std::next(indices.begin(), vert_index_count), std::back_inserter(mesh.vertIndices));
      std::move(std::next(indices.begin(), vert_index_count), std::next(indices.begin(), vert_index_count + norm_index_count), std::back_inserter(mesh.normIndices));
    }
    else {
      std::move(indices.begin(), std::next(indices.begin(), norm_index_count), std::back_inserter(mesh.normIndices));
      std::move(std::next(indices.begin(), norm_index_count), std::next(indices.begin(), norm_index_count + vert_index_count), std::back_inserter(mesh.vertIndices));
    }

    return mesh;
  }
}
