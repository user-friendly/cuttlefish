/**
 * @file
 * Resource definition file.
 */

#include "asset/resource.h"
#include "asset/collada.h"

namespace cuttlefish::asset {
  String getResourcePath(const String &subDir) {
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static String baseRes;
	if (baseRes.empty()) {
      //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
      char *basePath = SDL_GetBasePath();
      if (basePath) {
        baseRes = basePath;
        SDL_free(basePath);
      }
      else {
        std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
        return "";
      }
      std::cout << "Found base path: " << baseRes << std::endl;
      //We replace the last bin/ with res/ to get the the resource path
      // size_t pos = baseRes.rfind("bin");
      // baseRes = baseRes.substr(0, pos) + "data" + PATH_SEP;
      baseRes += "data";
      baseRes += PATH_SEP;
        
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
  };

  void readDaeFile(const String name)
  {
    Mesh mesh {getMesh(getResourcePath() + name)};

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
  };
}
