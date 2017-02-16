/**
 * @file main.cpp
 * Program entry point.
 */

#include "config.h"
#include "std.hpp"
#include "resource.hpp"

void print_legal();

int main(int argc, char* argv[]) {
  print_legal();

  std::cout << "Running on platform: " << SDL_GetPlatform() << std::endl;

  uint32_t init_flags = SDL_INIT_VIDEO
    | SDL_INIT_AUDIO
    | SDL_INIT_EVENTS
    | SDL_INIT_TIMER
    ;
  if (SDL_Init(init_flags) != 0) {
	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return EXIT_FAILURE;
  }

  std::cout << "Resource path: " << getResourcePath() << std::endl;

  // @TODO Get current display, somehow.
  int displayIndex = 0; // SDL_GetWindowDisplayIndex(window);
  if (displayIndex < 0) {
    std::cerr << "SDL_GetWindowDisplayIndex Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(displayIndex, &dm) != 0) {
    std::cerr << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }
  
  uint32_t window_flags = SDL_WINDOW_OPENGL
    | SDL_WINDOW_BORDERLESS
    ;
  SDL_Window *window = SDL_CreateWindow("An SDL window!",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        dm.w,
                                        dm.h,
                                        window_flags);
  if (window == nullptr) {
	std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return EXIT_FAILURE;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetWindowSize(window, dm.w, dm.h);

  uint32_t renderer_flags = SDL_RENDERER_ACCELERATED
    | SDL_RENDERER_PRESENTVSYNC
    | SDL_RENDERER_TARGETTEXTURE
    ;
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, renderer_flags);
  if (renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
  }

  std::string imagePath = getResourcePath() + "screen-test.bmp";

  SDL_Surface *bitmapSurface = SDL_LoadBMP(imagePath.c_str());
  if (bitmapSurface == nullptr){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return EXIT_FAILURE;
  }

  SDL_Texture *bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
  SDL_FreeSurface(bitmapSurface);

  int tmpInputDelay = 0;
  
  int delay = 1000/25;
  bool run = true;
  while (run == true) {
    // @FIXME Calling this function leaves the screen blank.
    // Wait some amount of time.
    SDL_Delay(delay);

    if (tmpInputDelay > 50) {
      std::cout << "Game loop: poll events" << std::endl;
    // Event loop, for the current cycle.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      std::cout << "Game loop, event poll: got an event" << std::endl;
      if (event.type == SDL_MOUSEBUTTONUP) {
        std::cout << "Event loop: mouse button up" << std::endl;
        if (event.button.button == SDL_BUTTON_LEFT) {
          std::cout << "Event loop: left mouse button up" << std::endl;
          std::cout << "(X,Y): " << event.button.x << "," << event.button.y << std::endl;
          run = false;
        }
      }
      else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
        std::cout << "Event loop: key Escape released" << std::endl;
        run = false;
      }
      else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
        SDL_MinimizeWindow(window);
      }
      else if (event.type == SDL_QUIT) {
        std::cout << "Event loop: quit" << std::endl;
        run = false;
      }
    }
    }
    tmpInputDelay++;

    // Clear backbuffer.
    SDL_RenderClear(renderer);

    // Draw to backbuffer.
    SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);

    // Present the backbuffer, removing the previous one from screen.
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(bitmapTex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();  
  return EXIT_SUCCESS;
}

void print_legal() {
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
  std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
  std::cout << "Copyright (C) 2016 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
}
