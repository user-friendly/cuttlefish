/**
 * @file
 * Game definition file.
 */

#include "std.h"
#include "game.h"

namespace cuttlefish {
  // @FIXME Handle inputs in a separate class.
  void handleInputs(Game& game, Renderer& graphics);
  
  void Game::start()
  {
    int delay = 1000 / 25;
    while (this->run) {
      // @FIXME Use STD/Boost equivalent.
      SDL_Delay(delay);

      handleInputs(*this, this->graphics);

      this->graphics.DrawExample();
      this->graphics.Render();
    }
  }

  void Game::stop()
  {
    this->run = false;
  }

  Game::~Game()
  {
    std::cout << "Game: free resources and shutdown." << std::endl;
  }

  void handleInputs(Game& game, Renderer& graphics)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_MOUSEBUTTONUP) {
        std::cout << "Event loop: mouse button up" << std::endl;
        if (event.button.button == SDL_BUTTON_LEFT) {
          std::cout << "Event loop: left mouse button up" << std::endl;
          std::cout << "(X,Y): " << event.button.x << "," << event.button.y << std::endl;
          game.stop();
        }
      }
      else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          std::cout << "Event loop: quit key pressed" << std::endl;
          game.stop();
          break;
        case SDLK_f:
          graphics.WindowFullscreen();
          break;
        case SDLK_m:
          graphics.WindowMinimize();
          break;
        case SDLK_e:
          std::cerr << "SDL_GetDesktopDisplayMode Error: nope, it's a fake exception." << std::endl;
          break;
        // case SDLK_r:
        //   render = !render;
        //   std::cout << "Render turned " << (render ? "on" : "off") << std::endl;
        //   break;
        }
      }
      else if (event.type == SDL_QUIT) {
        std::cout << "Event loop: quit" << std::endl;
        game.stop();
      }
    }
  }  
}
