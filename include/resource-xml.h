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
  private:
    xmlDocPtr doc_;
    
  public:
    const std::string kFileName;

    ResourceXml(const std::string &filename);
    ~ResourceXml() noexcept;
  };
}

#endif
