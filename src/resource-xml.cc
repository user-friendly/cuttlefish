/**
 * @file
 * Resources - XML definition file.
 */

#include "exception.h"
#include "resource.h"
#include "resource-xml.h"

namespace cuttlefish
{
  ResourceXml::ResourceXml(const std::string &filename)
    :kFileName {filename}
  {
    doc_ = xmlParseFile(filename.c_str());
    if (doc_ == nullptr) {
      Exception e {"Failed to read XML file: "};
      e << filename;
      throw e;
    }

    xmlNodePtr cur;
    cur = xmlDocGetRootElement(doc_);
    if (cur != nullptr) {
      std::cout << "\nroot node: " << cur->name << std::endl;
    }
  }

  ResourceXml::~ResourceXml() noexcept
  {
    if (doc_ != nullptr) {
      xmlFreeDoc(doc_);
    }
  }
}
