/**
 * @file
 * Resources - XML declaration file.
 */

#ifndef RESOURCE_XML_HPP
#define RESOURCE_XML_HPP

#include "std.h"

namespace cuttlefish {
  /**
   * An XML resource.
   */
  class ResourceXml {
  public:
    const std::string kFileName;
    
  private:
    rapidxml::file<> buffer_ {kFileName.c_str()};
    rapidxml::xml_document<> doc_ {};
    
  public:
    ResourceXml(const std::string &filename);
  };
}

#endif
