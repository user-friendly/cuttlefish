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
    GLenum shaderType;
    
    Shader(const String &filepath, GLenum type, GLuint shaderProgram);

    Shader(Shader&& shader);
    Shader& operator=(Shader&& shader);

    void Use(GLuint shaderProgram);
    
  };

}

#endif // SHADER_OPENGL_H
