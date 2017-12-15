/**
 * @file
 * Mesh declaration file.
 */

#ifndef MESH_H
#define MESH_H

#include "std.h"

namespace cuttlefish {
  struct Mesh {
    /**
     * A flat array of points.
     */
    FloatArray points;
  };
}

#endif // MESH_H
