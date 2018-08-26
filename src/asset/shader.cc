/**
 * @file
 * OpenGL Shader definition.
 */

#include "asset/shader.h"
#include "asset/resource.h"

namespace cuttlefish::asset {
  
  Shader::Shader(const String &filepath, GLenum type, GLuint shaderProgram):
    id {filepath}, shaderType {type}
  {
    String path {}, source {};
    std::uint32_t shaderPtr;
    int status;

    path = asset::getResourcePath("shaders") + id;

    std::cerr << "loading shader: " << id << std::endl;
    
    std::ifstream file {path};
    file.seekg(0, std::ios::end);   
    source.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    source.assign((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
    
    shaderPtr = glCreateShader(shaderType); 
    if (shaderPtr != 0) {
      const char* cp {source.c_str()};
      glShaderSource(shaderPtr, 1, &cp, NULL);
      glCompileShader(shaderPtr);
      
      glGetShaderiv(shaderPtr, GL_COMPILE_STATUS, &status);
      if (status == GL_FALSE) {
        std::array<char, 1024> error_msg {};
        glGetShaderInfoLog(shaderPtr, error_msg.size(), NULL, &error_msg[0]);
        std::cerr << "Failed to compile shader: " << path << std::endl;
        std::cerr << "\tError: " << &error_msg[0] << std::endl;
      }

      // Attach shader.
      glAttachShader(shaderProgram, shaderPtr);
      
      // Deletes the shaders. Advisable to do after they're linked with
      // the shader program, since they're no longer needed.
      glDeleteShader(shaderPtr);
    }
    else {
      std::cerr << "Failed to create shader object for: " << path << std::endl;
    }
  }

  Shader::Shader(Shader&& shader):
    id {shader.id}, shaderType {shader.shaderType}
  { 
    shader.id = "";
    shader.shaderType = 0;
  }

  Shader& Shader::operator=(Shader&& shader)
  {
    id = shader.id;
    shaderType = shader.shaderType;
    
    shader.id = "";
    shader.shaderType = 0;
    
    return *this;
  }

}
