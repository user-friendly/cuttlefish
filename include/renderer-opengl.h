/**
 * @file
 * Renderer declaration file.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "std.h"
#include "mesh.h"
#include "asset/shader-opengl.h"

namespace cuttlefish
{
	class Renderer
	{
    protected:
      SDL_Window* window;
      SDL_GLContext glcontext;

      Mesh mesh;
      GLuint vao;
      GLuint vbuffer;
      GLuint ibuffer;

      GLuint shaderProgram;
      std::vector<asset::Shader> shaders;

      glm::mat4 model; // TODO Move to Mesh/Entity?
      glm::mat4 view;
      glm::mat4 projection;

      void LoadShaders();
      void LoadMesh();

      void CheckForErrors(const String when) const;
      String ErrorToString(GLenum error) const;
      
    public:
      Renderer();
      ~Renderer();
      
      /**
       * Draws and example texture.
       *
       * Note that this function uses SDL renderer.
       */
      void DrawExample();
      
      /**
       * Render the backbuffer and then clear it.
       *
       * Note that this function uses SDL renderer.
       */
      void Render();
      
      /**
       * Minimize window.
       */
      void WindowMinimize();
      
      /**
       * Make window fullscreen.
       */
      void WindowFullscreen();
	};
}

#endif // RENDERER_H
