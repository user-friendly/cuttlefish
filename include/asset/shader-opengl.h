/**
 * @file
 * OpenGL shader.
 */

#ifndef SHADER_OPENGL_H
#define SHADER_OPENGL_H

#include "std.h"

namespace cuttlefish::asset {
  
  struct Shader
  {
    // This is also the resource file path.
    String id;
    std::uint32_t shaderPtr;
    GLenum shaderType;
    
    Shader(const String &filepath, GLenum type);

    Shader(Shader&& shader);
    Shader& operator=(Shader&& shader);
    
    ~Shader();
  };

}

#endif // SHADER_OPENGL_H
