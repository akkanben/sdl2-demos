#include <iostream>
#include <stdio.h>
#include <string>

#include "SDL2/SDL.h"

int main() {
  SDL_Surface *screen;
  SDL_Surface *image;
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Simple Event Polling", 0, 0, 640, 480, 0);
  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Setup surfaces
  screen = SDL_GetWindowSurface(window);
  image = SDL_LoadBMP("./res/maze_00.bmp");
  SDL_BlitSurface(image, NULL, screen, NULL);
  SDL_FreeSurface(image);
  SDL_UpdateWindowSurface(window);

  bool appIsRunning = true;
  int currentImage = 1;
  while (appIsRunning) { // Application Loop
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Event queue
      switch (event.type) {
      case SDL_QUIT:
        appIsRunning = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE) {
          std::string fileName;

          // Hacky renaming for next image to blit
          fileName = "./res/maze_0" + std::to_string(currentImage) + ".bmp";
          image = SDL_LoadBMP(fileName.c_str());
          SDL_BlitSurface(image, NULL, screen, NULL);
          SDL_FreeSurface(image);
          SDL_UpdateWindowSurface(window);

          // Loop through maze images 0-5
          currentImage = ++currentImage % 5;
        }
        break;
      default:
        break;
      }
    }
  }

  SDL_DestroyWindow(window);
  return 0;
}
