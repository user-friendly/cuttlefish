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
    xml_node<> *root_ = doc_.first_node("COLLADA");
    if (root_ == nullptr) {
      Exception e {"Collada file missing root element: "};
      e << filename;
      throw e;
    }
    xml_attribute<> *attr = root_->first_attribute("version");
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

  Mesh ResourceCollada::getMesh()
  {
    Mesh tmp {};

    // There can be multiple libraries, but we'll use only the first one.
    XmlNode lib_geo = root_->first_node("library_geometries");
    
    
    // @TODO Will the POD object be moved or copied?
    return tmp;
  }
}
