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
    using XmlNode = rapidxml::xml_node<> *;
    using XmlAttr = rapidxml::xml_attribute<> *;
    
    // @TODO Figure out what character type to use.
    rapidxml::file<> buffer_ {kFileName.c_str()};
    rapidxml::xml_document<> doc_ {};
    XmlNode root_ {};
    
  public:
    ResourceCollada(const String &filename);
    cuttlefish::Mesh getMesh() const;

  protected:
    // The following are nested helper classes.
    struct Element {
      String tag;
      String id;
      XmlNode node;
    }
    
    struct Geometry : Element {
      Geometry(XmlNode node);
      std::vector<Mesh> meshes;
    };

    struct Mesh : Element {
      Mesh(XmlNode node);
      std::vector<Source> sources;
    };

    struct Source : Element {
      Source(XmlNode node);
      FloatArray sequence;
    };

    struct Vertices : Element {
      String semantic;
      std::vector<Source> sources;
    };

    struct Polylist : Element {
      String materialId;
      uint32 count;
      std::vector<Element> sources;
    };
  };

}

#endif // RESOURCE_COLLADA_H
