/**
 * @file
 * Resources declaration file.
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include "std.h"
#include "mesh.h"

namespace cuttlefish::asset {
  // Gets the game's resources absolute directory path.
  String getResourcePath(const String &subDir = "");
}

#endif // RESOURCE_H
