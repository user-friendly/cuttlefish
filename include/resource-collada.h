/**
 * @file
 * Resources - COLLADA declaration file.
 */

#ifndef RESOURCE_COLLADA_H
#define RESOURCE_COLLADA_H

#include "std.h"
#include "resource.h"

namespace cuttlefish {
  /**
   * A COLLADA resource.
   */
  class ResourceCollada : public ResourceMesh {
  public:
    // Currently supported version;
    const String kVersion {"1.4.1"};
    const String kFileName;
    
  private:
    using XmlNode = rapidxml::xml_node<>;
    
    // @TODO Figure out what character type to use.
    rapidxml::file<> buffer_ {kFileName.c_str()};
    rapidxml::xml_document<> doc_ {};
    XmlNode *root_ {};
    
  public:
    ResourceCollada(const String &filename);
    Mesh getMesh();
  };
}

#endif // RESOURCE_COLLADA_H
