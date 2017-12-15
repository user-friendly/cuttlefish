/**
 * @file
 * Resources declaration file.
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include "std.h"
#include "mesh.h"

namespace cuttlefish {
  class ResourceMesh {
    virtual Mesh getMesh() const = 0;
  };
  
  /**
   * @TODO Is this function even needed?
   */
  String getResourcePath(const String &subDir = "");

  void readDaeFile(const String name);
}

#endif // RESOURCE_H
