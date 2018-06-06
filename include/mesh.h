/**
 * @file
 * Mesh declaration file.
 */

#ifndef MESH_H
#define MESH_H

#include "std.h"

namespace cuttlefish {
  /**
   * A simple mesh.
   *
   * The number sequences shouldn't really be dynamic and
   * probably this mesh struct should be converted to a class
   * and handle its resources appropriately.
   */
  struct Mesh
  {
    static const std::uint16_t faceVertCount = 3;
    
    /**
     * A flat array of points.
     *
     * Holds the 3D coordinates for a vector in the order X, Y, Z.
     * The size must be devisible by 3.
     */
    FloatArray vertices;
    /**
     * The index of the vertices.
     */
    IndexArray vertIndices;
    
    /**
     * A flat array of normals.
     * 
     * The same applies for normals as for vertices.
     */
    FloatArray normals;
    IndexArray normIndices;
  };
}

#endif // MESH_H
