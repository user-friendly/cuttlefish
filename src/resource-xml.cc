/**
 * @file
 * Resources - XML definition file.
 */

#include "exception.h"
#include "resource.h"
#include "resource-xml.h"

namespace cuttlefish
{
  using namespace rapidxml;
  
  ResourceXml::ResourceXml(const std::string &filename)
    :kFileName {filename}
  {
    doc_.parse<0>(buffer_.data());
    xml_node<> *node = doc_.first_node("COLLADA");
    if (node) {
      //std::cout << "COLLADA: " << doc_ << std::endl;
      std::cout << doc_;
    }
    else {
      std::cerr << "Could not find root node of Collada file!" << std::endl;
    }
  }
}
