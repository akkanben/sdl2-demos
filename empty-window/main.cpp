#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

int main() {
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Create Window", 0, 0, 640, 480, 0);
  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Delay(5000);
  SDL_DestroyWindow(window);
  return 0;
}
