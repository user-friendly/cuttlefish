/**
 * @file
 * Renderer definition file.
 */

#include "renderer.h"
#include "exception.h"
#include "resource.h"

namespace cuttlefish
{
  Renderer::Renderer()
  {
    {
      std::cout << "SDL running on platform: " << SDL_GetPlatform() << std::endl;

      SDL_version compiled;
      SDL_version linked;
      
      SDL_VERSION(&compiled);
      SDL_GetVersion(&linked);
      
      std::cout << (boost::format("Compiled against SDL version %1%.%2%.%3%.")
                    // All structure members are of Uint8 type.
                    % static_cast<std::uint16_t>(compiled.major)
                    % static_cast<std::uint16_t>(compiled.minor)
                    % static_cast<std::uint16_t>(compiled.patch)) << std::endl;
      std::cout << (boost::format("Linking against SDL version %1%.%2%.%3%.")
                    % static_cast<std::uint16_t>(linked.major)
                    % static_cast<std::uint16_t>(linked.minor)
                    % static_cast<std::uint16_t>(linked.patch)) << std::endl;
    }

    uint32_t init_flags = SDL_INIT_VIDEO
      | SDL_INIT_AUDIO
      | SDL_INIT_EVENTS
      | SDL_INIT_TIMER;
    if (SDL_Init(init_flags) != 0) {
      Exception e {"SDL Init Error: "};
      e << SDL_GetError();
      throw e;
    }

    // @TODO Get current display, somehow.
    int displayIndex = 0; // SDL_GetWindowDisplayIndex(window);
    if (displayIndex < 0) {
      Exception e {"SDL_GetWindowDisplayIndex Error: "};
      e << SDL_GetError();
      SDL_Quit();
      throw e;
    }

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(displayIndex, &dm) != 0) {
      Exception e {"SDL_GetDesktopDisplayMode Error: "};
      e << SDL_GetError();
      SDL_Quit();
      throw e;
    }

    uint32_t window_flags = SDL_WINDOW_OPENGL
      | SDL_WINDOW_BORDERLESS
      | SDL_WINDOW_FULLSCREEN_DESKTOP;
    window = SDL_CreateWindow("An SDL window!",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    dm.w,
                                    dm.h,
                                    window_flags);
    if (window == nullptr) {
      Exception e {"SDL_CreateWindow Error: "};
      e << SDL_GetError();
      SDL_Quit();
      throw e;
    }

    glcontext = SDL_GL_CreateContext(window);
    if (glcontext == nullptr) {
      Exception e {"SDL_GL_CreateContext Error: "};
      e << SDL_GetError();
      SDL_DestroyWindow(window);
      SDL_Quit();
      throw e;
    }
    // @TODO Use SDL_GL_SetSwapInterval() to set vsync.

    // Set clear color.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // String imagePath = getResourcePath() + "screen-test.bmp";
  };

  void Renderer::DrawExample()
  {
    // Draw to backbuffer.
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a Red 1x1 Square centered at origin
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.5f, -0.5f);    // x, y
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    glEnd();

    glFlush();
  };
  
  void Renderer::Render() {
    DrawExample();
    // Present the backbuffer, removing the previous one from screen.
    SDL_GL_SwapWindow(window);
    // Clear backbuffer.
    // SDL_RenderClear(renderer);
  };
  
  void Renderer::WindowMinimize()
  {
    SDL_MinimizeWindow(window);
  };

  void Renderer::WindowFullscreen()
  {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  };
  
  Renderer::~Renderer()
  {
    std::cout << "Renderer: shutdown SDL." << std::endl;
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
  };
}
