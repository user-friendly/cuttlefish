/**
 * @file
 * Grahpics driver declaration file.
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "std.h"
#include "scene.h"
#include "window.h"

namespace cuttlefish::opengl {
  
  class Driver
  {
  protected:
    Window& window;
    Scene& scene;
    
    SDL_GLContext context;
    
    GLuint shaderProgram;

    glm::mat4 model; // TODO Move to Mesh/Entity?
    glm::mat4 view;
    glm::mat4 projection;

    void CheckForErrors(const String when) const;
    String ErrorToString(GLenum error) const;
    
  public:
    Driver(Window& window, Scene& scene);
    ~Driver();

    // Swap buffers, basically.
    void Render();
  };
  
}

#endif // DRIVER_H
