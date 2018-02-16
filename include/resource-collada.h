/**
 * @file
 * Resources - COLLADA declaration file.
 */

#ifndef RESOURCE_COLLADA_H
#define RESOURCE_COLLADA_H

#include "std.h"
#include "resource.h"

namespace cuttlefish {
  using XmlBase = rapidxml::xml_base<> *;
  using XmlNode = rapidxml::xml_node<> *;
  using XmlAttr = rapidxml::xml_attribute<> *;

  /**
   * A COLLADA resource.
   */
  class ResourceCollada : public ResourceMesh {
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
    ResourceCollada(const String &filename);
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
    };

    struct Source : Element {
      Source(XmlNode node);
      FloatArray sequence;
    };

    struct Vertices : Element {
      Vertices(XmlNode node);
      String semantic;
      std::vector<Source> sources;
    };

    struct Input : Element {
      Input(XmlNode node);
      String semantic;
      String sourceId;
      uint8_t offset;
    };

    struct Polylist : Element {
      typedef uint16_t int_t;
      
      Polylist(XmlNode node);
      // @TODO Replace with proper class.
      String materialId;
      uint32_t count;
      std::vector<Input> inputs;
      std::vector<int_t> vcounts;
      std::vector<int_t> indices;
    };

    struct Mesh : Element {
      Mesh(XmlNode node);
      std::vector<Source> sources;
      std::vector<Polylist> polylists;
      std::unique_ptr<Vertices> vertices;
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
  std::ostream& operator<<(std::ostream& out, const Xml::Polylist& p);
}

#endif // RESOURCE_COLLADA_H
