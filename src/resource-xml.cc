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

    xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(doc_);
    if (context != nullptr) {
      result = xmlXPathEvalExpression((xmlChar*) "/COLLADA/asset/contributor/author", context);
      if (result != nullptr) {
        if (!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
          xmlChar *text;
          xmlNodeSetPtr nodeset = result->nodesetval;
          for (int i = 0; i < nodeset->nodeNr; i++) {
            text = xmlNodeListGetString(doc_, nodeset->nodeTab[i]->xmlChildrenNode, 1);
            std::cout << (char*) text << std::endl;
            xmlFree(text);
          }
        }
        else {
          std::cout << "no result!" << std::endl;
        }
      
        xmlXPathFreeObject(result); 
      }
    }
  }

  ResourceXml::~ResourceXml() noexcept
  {
    if (doc_ != nullptr) {
      xmlFreeDoc(doc_);
    }
  }
}
