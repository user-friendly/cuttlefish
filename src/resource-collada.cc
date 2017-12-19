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

  Mesh ResourceCollada::getMesh() const
  {
    Mesh tmp_mesh {};
    
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

    String semantic_vertex {"VERTEX"}, semantic_normal {"NORMAL"}, semantic {};
    XmlNode source_vertex {}, source_normals {};

    if (polylist_node->first_node("input") && polylist_node->first_node("input")->first_attribute("semantic")) {
      semantic = polylist_node->first_node("input")->first_attribute("semantic")->value();
      
    }
    
    for (tmp_node = polylist_node->first_node("input"); tmp_node; tmp_node = tmp_node->next_sibling("input")) {
      if (tmp_node->first_attribute("semantic")) {
        if (semantic_vertex == tmp_node->first_attribute("semantic")->value()) {
           
        }
        else if (semantic_normal == tmp_node->first_attribute("semantic")->value()) {
          
        }
      }
    }

    tmp_node = mesh_node->first_node("source");
    if (tmp_node) {
      tmp_node = tmp_node->first_node("float_array");
      if (tmp_node) {
        char *str_end {nullptr};
        uint16_t count {static_cast<uint16_t>(std::strtoul(tmp_node->first_attribute("count")->value(), &str_end, 10))};
        std::cout << "source: " << tmp_node->first_attribute("id")->value() << ", count: " << count << std::endl;
        std::cout << "\tvalues: " << tmp_node->value() << std::endl;
        
        std::istringstream raw_floats {tmp_node->value()};
        FloatArray fa {std::istream_iterator<float>(raw_floats), std::istream_iterator<float>()};
        std::cout << "\tvalues: ";
        for (auto &val : fa) {
          std::cout << val << " ";
        }
        std::cout << std::endl;
      }
    }

    

    tmp_node = mesh_node->first_node("source")->next_sibling("source");
    if (tmp_node) {
      tmp_node = tmp_node->first_node("float_array");
      if (tmp_node) {
        char *str_end {nullptr};
        uint16_t count {static_cast<uint16_t>(std::strtoul(tmp_node->first_attribute("count")->value(), &str_end, 10))};
        std::cout << "source: " << tmp_node->first_attribute("id")->value() << ", count: " << count << std::endl;
        std::cout << "\tvalues: " << tmp_node->value() << std::endl;
        
        std::istringstream raw_floats {tmp_node->value()};
        FloatArray fa {std::istream_iterator<float>(raw_floats), std::istream_iterator<float>()};
        std::cout << "\tvalues: ";
        for (auto &val : fa) {
          std::cout << val << " ";
        }
        std::cout << std::endl;
      }
    }
    
    // @TODO Will the POD object be moved or copied?
    return tmp_mesh;
  }
}
