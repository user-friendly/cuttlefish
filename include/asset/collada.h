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

namespace cuttlefish::asset {
  using XmlBase = rapidxml::xml_base<CharType> *;
  using XmlNode = rapidxml::xml_node<CharType> *;
  using XmlAttr = rapidxml::xml_attribute<CharType> *;

  /**
   * A COLLADA resource.
   */
  class Collada {
  public:
    // Currently supported version;
    const String kVersion {"1.4.1"};
    const String kFileName;
    
  protected:
    rapidxml::file<> buffer_ {kFileName.c_str()};
    rapidxml::xml_document<> doc_ {};
    XmlNode root_ {};
    
  public:
    Collada(const String &filename);
    cuttlefish::Mesh getMesh() const;
  };

  class Exception
  {
  public:
    Exception ();
    Exception (const char* message);
    Exception (const String& message);
    String message();
    Exception& operator<<(const char* append);
    Exception& operator<<(const String& append);
  protected:
    String msg;
  };
}

#endif // RESOURCE_COLLADA_H
