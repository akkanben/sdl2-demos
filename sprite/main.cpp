#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "Sprite.hpp"

int main() {
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_ShowCursor(0); // hide mouse
  window = SDL_CreateWindow("Simple Event Polling", 0, 0, 640, 480, 0);

  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *renderer = nullptr;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  Sprite hero = Sprite(renderer, "./res/hero.bmp", 32, 400, 32, 64);
  hero.setColorKey("./res/hero.bmp", 146, 144, 255);
  Sprite background = Sprite(renderer, "./res/bg.bmp", 0, 0, 640, 480);

  bool appIsRunning = true;
  while (appIsRunning) { // Application Loop

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    background.render();
    hero.render();

    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Event queue
      switch (event.type) {
      case SDL_QUIT:
        appIsRunning = false;
        break;
      case SDL_MOUSEMOTION:
        hero.setPosition(event.motion.x, event.motion.y);
        break;
      case SDL_MOUSEWHEEL:
        if (event.wheel.y > 0)
          hero.setSize(hero.getWidth() + 16, hero.getHeight() + 32);
        else if (event.wheel.y < 0)
          hero.setSize(hero.getWidth() - 16, hero.getHeight() - 32);
        break;
      default:
        break;
      }
    }
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  return 0;
}
