/**
 * @file
 * Grahpics driver definition file.
 */

#include "opengl/driver.h"

namespace cuttlefish::opengl
{

  Driver::Driver(Window& window, Scene& scene) :
    window {window}, scene {scene}
  {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    context = SDL_GL_CreateContext(window.GetWindowPtr());
    if (context == nullptr) {
      std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError();
    }
    // @TODO Use SDL_GL_SetSwapInterval() to set vsync.

    // Context background color.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    #ifdef DEBUG
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    #endif

    model = glm::mat4(1.0f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    projection = glm::perspective(glm::radians(45.0f), 600.0f / 400.0f, 0.1f, 100.0f);
  };

  Driver::~Driver()
  {
    std::cout << "Shuttind down OpenGL." << std::endl;
    SDL_GL_DeleteContext(context);
  };

  void Driver::Render() {
    // Draw to backbuffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // Use the main shader program.
    glUseProgram(shaderProgram);

    // TODO Use the scene to render stuff.
    
    // Present the backbuffer, removing the previous one from screen.
    SDL_GL_SwapWindow(window.GetWindowPtr());
    // Clear backbuffer.
    // SDL_RenderClear(renderer);
  };

  // void Driver::DrawExample()
  // {
  //   model = glm::rotate(model, glm::radians(0.2f), glm::vec3(0.0f, 1.0f, 0.0f));
    
  //   GLint uniformLoc = glGetUniformLocation(shaderProgram, "model");
  //   glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));
  //   CheckForErrors("setting model uniform");

  //   uniformLoc = glGetUniformLocation(shaderProgram, "view");
  //   glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(view));
  //   CheckForErrors("setting view uniform");

  //   uniformLoc = glGetUniformLocation(shaderProgram, "projection");
  //   glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(projection));
  //   CheckForErrors("setting projection uniform");
    
  //   glBindVertexArray(vao);
  //   glDrawElements(GL_TRIANGLES, mesh.vertIndices.size(), GL_UNSIGNED_SHORT, 0);
  //   glBindVertexArray(0);

  //   CheckForErrors("rendering a frame before flushing");
  // };
  
  // void Renderer::LoadShaders()
  // {
  //   // Create shader program.
  //   shaderProgram = glCreateProgram();
    
  //   // Load simple vertext shader.
  //   shaders.push_back(asset::Shader {"simple.vert", GL_VERTEX_SHADER, shaderProgram});
  //   CheckForErrors("loading vertex shaders");

  //   // Load white pixel shader.
  //   shaders.push_back(asset::Shader {"white.frag", GL_FRAGMENT_SHADER, shaderProgram});
  //   CheckForErrors("loading fragment shaders");

  //   glLinkProgram(shaderProgram);

  //   // Vefiry shader program was linked.
  //   int success;
  //   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  //   if (!success) {
  //     std::array<char, 1024> error_msg {};
  //     glGetProgramInfoLog(shaderProgram, error_msg.size(), NULL, &error_msg[0]);
  //     std::cerr << "Failed to linking shader program: " << std::endl;
  //     std::cerr << "\tError: " << &error_msg[0] << std::endl;
  //   }
  //   CheckForErrors("linking shader program");
  // }
  
  // void Renderer::LoadMesh()
  // {
  //   // Prepare the mesh to be displayed.
  //   mesh = asset::collada::getMeshFromResource("cube.dae");
    
  //   #ifdef DEBUG
  //   debugPrintMesh(mesh);
  //   #endif

  //   // Generate a vertex array.
  //   glGenVertexArrays(1, &vao);
  //   glBindVertexArray(vao);

  //   // Create vertex buffer.
  //   glGenBuffers(1, &vbuffer);
  //   glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
  //   glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices[0]) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

  //   // Create index buffer.
  //   glGenBuffers(1, &ibuffer);
  //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
  //   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.vertIndices[0]) * mesh.vertIndices.size(), mesh.vertIndices.data(), GL_STATIC_DRAW);

  //   // Set vertex attributes
  //   glEnableVertexAttribArray(0);
  //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(mesh.vertices[0]), 0);
    
  //   glBindVertexArray(0);

  //   CheckForErrors("loading cube mesh into video memory");
  // }

  /**
   *  Created on: 2014/10/19
   *      Author: Dimitri Kourkoulis
   *     License: BSD 3-Clause License (see LICENSE file)
   */
  void Driver::CheckForErrors(const String when) const {
    GLenum errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
      std::cerr << "OpenGL error while " << when << std::endl;
      do {
        std::cerr << ErrorToString(errorCode) << std::endl;
        errorCode = glGetError();
      }
      while (errorCode != GL_NO_ERROR);
    }
  }

  /**
   * Convert error enum returned from OpenGL to a readable string error message.
   * @param error The error code returned from OpenGL
   *
   *  Created on: 2014/10/19
   *      Author: Dimitri Kourkoulis
   *     License: BSD 3-Clause License (see LICENSE file)
   */
  String Driver::ErrorToString(GLenum error) const {
    String errorString;
    
    switch (error) {
    case GL_NO_ERROR:
      errorString = "GL_NO_ERROR: No error has been recorded. "
	"The value of this symbolic constant is guaranteed to be 0.";
      break;
    case GL_INVALID_ENUM:
      errorString = "GL_INVALID_ENUM: An unacceptable value is specified for "
	"an enumerated argument. The offending command is ignored and has no "
	"other side effect than to set the error flag.";
      break;
    case GL_INVALID_VALUE:
      errorString = "GL_INVALID_VALUE: A numeric argument is out of range. "
	"The offending command is ignored and has no other side effect than "
	"to set the error flag.";
      break;
    case GL_INVALID_OPERATION:
      errorString = "GL_INVALID_OPERATION: The specified operation is not "
	"allowed in the current state. The offending command is ignored "
	"and has no other side effect than to set the error flag.";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      errorString = "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer "
	"object is not complete. The offending command is ignored and has "
	"no other side effect than to set the error flag.";
      break;
    case GL_OUT_OF_MEMORY:
      errorString = "GL_OUT_OF_MEMORY: There is not enough memory left to "
	"execute the command. The state of the GL is undefined, except for "
	"the state of the error flags, after this error is recorded.";
      break;
    case GL_STACK_UNDERFLOW:
      errorString = "GL_STACK_UNDERFLOW: An attempt has been made to perform "
	"an operation that would cause an internal stack to underflow.";
      break;
    case GL_STACK_OVERFLOW:
      errorString = "GL_STACK_OVERFLOW: An attempt has been made to perform "
	"an operation that would cause an internal stack to overflow.";
      break;
    default:
      errorString = "Unknown error";
      break;
    }
    return errorString;
  }
  
}
