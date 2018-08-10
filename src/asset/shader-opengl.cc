/**
 * @file
 * OpenGL Shader definition.
 */

#include "asset/shader-opengl.h"
#include "asset/resource.h"

namespace cuttlefish::asset {
  
  Shader::Shader(const String &filepath, GLenum type):
    id {filepath}, shaderType {type}
  {
    String path {}, source {};
    int status;

    path = asset::getResourcePath("shaders") + id;
    std::ifstream file {path};
    file.seekg(0, std::ios::end);   
    source.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    source.assign((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
    
    shaderPtr = glCreateShader(shaderType); 
    if (shaderPtr == 0) {
      std::cerr << "Failed to create shader object for: " << path << std::endl;
    }
    else {
      const char* cp {source.c_str()};
      glShaderSource(shaderPtr, 1, &cp, NULL);
      glCompileShader(shaderPtr);
    
      glGetShaderiv(shaderPtr, GL_COMPILE_STATUS, &status);
      if (status == GL_FALSE) {
        std::array<char, 1024> error_msg {};
        glGetShaderInfoLog(shaderPtr, error_msg.size(), NULL, &error_msg[0]);
        std::cerr << "Failed to compile shader: " << path << std::endl;
        std::cerr << "\tError: " << &error_msg[0] << std::endl;
        glDeleteShader(shaderPtr);
        shaderPtr = 0;
      }
    }
  }

  Shader::~Shader()
  {
    // A value of 0 should be silently ignored.
    glDeleteShader(shaderPtr);
  }
}
