/**
 * @file
 * Renderer declaration file.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "std.h"
#include "mesh.h"

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

      std::uint32_t shaderProgram;
      std::uint32_t simpleVertexShader;
      std::uint32_t whiteFragmentShader;

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
