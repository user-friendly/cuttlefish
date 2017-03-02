/**
 * @file
 * OSGraphics definition file.
 */

#include "OSGraphics.hpp"
#include "Exception.hpp"
#include "Resource.hpp"

namespace Cuttlefish
{
  OSGraphics::OSGraphics()
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
    this->window = SDL_CreateWindow("An SDL window!",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    dm.w,
                                    dm.h,
                                    window_flags);
    if (this->window == nullptr) {
      Exception e {"SDL_CreateWindow Error: "};
      e << SDL_GetError();
      SDL_Quit();
      throw e;
    }

    uint32_t renderer_flags = SDL_RENDERER_ACCELERATED
      | SDL_RENDERER_PRESENTVSYNC
      | SDL_RENDERER_TARGETTEXTURE
      ;
    this->renderer = SDL_CreateRenderer(this->window, -1, renderer_flags);
    if (this->renderer == nullptr) {
      Exception e {"SDL_CreateRenderer Error: "};
      e << SDL_GetError();
      SDL_DestroyWindow(this->window);
      SDL_Quit();
      throw e;
    }

    std::string imagePath = getResourcePath() + "screen-test.bmp";

    gsl::owner<SDL_Surface> *bitmapSurface = SDL_LoadBMP(imagePath.c_str());
    if (bitmapSurface == nullptr) {
      Exception e {"SDL_LoadBMP Error: "};
      e << SDL_GetError();
      SDL_DestroyRenderer(this->renderer);
      SDL_DestroyWindow(this->window);
      SDL_Quit();
      throw e;
    }

    this->bitmapTex = SDL_CreateTextureFromSurface(this->renderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);
  };

  void OSGraphics::drawExample()
  {
    // Draw to backbuffer.
    SDL_RenderCopy(this->renderer, this->bitmapTex, NULL, NULL);
  };
  
  void OSGraphics::render() {
    // Present the backbuffer, removing the previous one from screen.
    SDL_RenderPresent(this->renderer);
    // Clear backbuffer.
    SDL_RenderClear(this->renderer);
  };
  
  void OSGraphics::windowMinimize()
  {
    SDL_MinimizeWindow(this->window);
  };

  void OSGraphics::windowFullscreen()
  {
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  };
  
  void OSGraphics::freeResources()
  {
    SDL_DestroyTexture(this->bitmapTex);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
  };
  
  OSGraphics::~OSGraphics()
  {
    std::cout << "OSGraphics: free resources and shutdown SDL." << std::endl;
    this->freeResources();
    SDL_Quit();
  };
}
