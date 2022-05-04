#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

int main() {
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Simple Event Polling", 0, 0, 640, 480, 0);

  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  bool appIsRunning = true;
  while (appIsRunning) { // Application Loop
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Event queue
      switch (event.type) {
      case SDL_QUIT:
        appIsRunning = false;
        break;
      case SDL_KEYDOWN:
        std::cout << SDL_GetKeyName(event.key.keysym.sym) << " was pressed." << std::endl;
        break;
      case SDL_MOUSEMOTION:
        std::cout << event.motion.x << ":" << event.motion.y << std::endl;
      default:
        break;
      }
    }
  }

  SDL_DestroyWindow(window);
  return 0;
}
