/**
 * @file
 * Resources declaration file.
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "std.h"

namespace cuttlefish {

  /**
   * Get the resource path for resources located in res/subDir
   * It's assumed the project directory is structured like:
   * bin/
   *  the executable
   * res/
   *  Lesson1/
   *  Lesson2/
   *
   * Paths returned will be Lessons/res/subDir
   */
  std::string getResourcePath(const std::string &subDir = "");

  void testXmlReader(const char *name);
}

#endif
