/**
 * @file
 * Resources - COLLADA declaration file.
 */

/**
 * COLLADA should be used only by tools and not the game engine.
 */

#ifndef RESOURCE_COLLADA_H
#define RESOURCE_COLLADA_H

#include "std.h"
#include "asset/resource.h"

namespace cuttlefish::asset::collada {
  using XmlBase = rapidxml::xml_base<CharType> *;
  using XmlNode = rapidxml::xml_node<CharType> *;
  using XmlAttr = rapidxml::xml_attribute<CharType> *;
  
  extern const CharType* kSupportedVersion;
  
  Mesh getMesh(const String &filename);

  inline Mesh getMeshFromResource(const String name)
  {
    return getMesh(getResourcePath() + name);
  };
}

#endif // RESOURCE_COLLADA_H
