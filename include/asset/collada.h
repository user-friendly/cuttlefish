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
  using XmlBase = rapidxml::xml_base<CharT> *;
  using XmlNode = rapidxml::xml_node<CharT> *;
  using XmlAttr = rapidxml::xml_attribute<CharT> *;

  /**
   * A COLLADA resource.
   */
  class Collada {
  public:
    // Currently supported version;
    const String kVersion {"1.4.1"};
    const String kFileName;
    
  protected:
    
    // @TODO Figure out what character type to use.
    rapidxml::file<> buffer_ {kFileName.c_str()};
    rapidxml::xml_document<> doc_ {};
    XmlNode root_ {};
    
  public:
    Collada(const String &filename);
    cuttlefish::Mesh getMesh() const;
  };


  namespace Xml {
    struct Element {
      Element(XmlNode node);
      String tag;
      String id;
      String name;
      XmlNode node;
      XmlNode extra;
      
      template <typename NumT>
      NumT castToNumber(const XmlBase &base) {
        if (base && base->value_size()) {
          return boost::lexical_cast<NumT>(base->value());
        }
        return 0;
      }
    };

    struct Source : Element {
      Source(XmlNode node);
      FloatArray sequence;
    };
    using SourcePtr = std::unique_ptr<Source>;

    struct Input : Element {
      Input(XmlNode node);
      String semantic;
      String sourceId;
      uint8_t offset;
    };
    using InputPtr = std::unique_ptr<Input>;

    struct Vertices : Element {
      Vertices(XmlNode node);
      InputPtr input;
    };

    struct Polylist : Element {
      typedef uint16_t int_t;
      
      Polylist(XmlNode node);
      // @TODO Replace with proper class.
      String materialId;
      // @TODO Count size might be too big. 16 bits might be enough.
      uint32_t count;
      std::vector<Input> inputs;
      std::vector<int_t> vcounts;
      std::vector<int_t> indices;
    };

    struct Mesh : Element {
      Mesh(XmlNode node);
      std::vector<Source> sources;
      std::vector<Polylist> polylists;
      Vertices vertices;
    };

    struct Geometry : Element {
      Geometry(XmlNode node);
      String materialId;
      uint32_t count;
      std::vector<Element> sources;
      std::vector<Mesh> meshes;
    };
  }

  String& operator<<(String& str, const XmlBase& base);
  std::ostream& operator<<(std::ostream& out, const Xml::Element& e);
  std::ostream& operator<<(std::ostream& out, const Xml::Source& e);
  std::ostream& operator<<(std::ostream& out, const Xml::Polylist& p);
  // Cannot be overloaded - XmlBase is a pointer, both are built-in types.
  //uint32_t& operator<<(uint32_t& num, const XmlBase& base)

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
