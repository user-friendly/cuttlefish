/**
 * @file
 * Mesh definition file.
 */

#include "std.h"
#include "mesh.h"

namespace cuttlefish {

  void debugPrintMesh(const Mesh& mesh)
  {
    std::cout << "cube vertices (" << mesh.vertices.size() << "): ";
    for (auto &val : mesh.vertices) {
      std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "cube vertex indices: (" << mesh.vertIndices.size() << "): ";
    for (auto &val : mesh.vertIndices) {
      std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "cube normals: (" << mesh.normals.size() << "): ";
    for (auto &val : mesh.normals) {
      std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "cube normal indices: (" << mesh.normIndices.size() << "): ";
    for (auto &val : mesh.normIndices) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
  
}
