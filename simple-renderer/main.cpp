#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "SDL2/SDL.h"

int main() {
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Simple Event Polling", 0, 0, 640, 480, 0);
  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *renderer = nullptr;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int midX = 640 / 2;
  int midY = 480 / 2;

  SDL_Rect rectangle01;
  rectangle01.w = 100;
  rectangle01.h = 400;
  rectangle01.x = midX - 50;
  rectangle01.y = midY - 200;

  SDL_Rect rectangle02;
  rectangle02.w = 100;
  rectangle02.h = 400;
  rectangle02.x = midX - 250;
  rectangle02.y = 480 / 2 - 200;

  SDL_Rect rectangle03;
  rectangle03.w = 100;
  rectangle03.h = 400;
  rectangle03.x = midX + 150;
  rectangle03.y = 480 / 2 - 200;

  bool appIsRunning = true;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &rectangle01);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &rectangle02);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &rectangle03);

  while (appIsRunning) { // Application Loop

    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Event queue
      switch (event.type) {
      case SDL_QUIT:
        appIsRunning = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE) {
          SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255,
                                 SDL_ALPHA_OPAQUE);
          SDL_RenderDrawLine(renderer, rand() % 640, rand() % 480, rand() % 640, rand() % 480);
        }
        if (event.key.keysym.sym == SDLK_DELETE)
          SDL_RenderClear(renderer);
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
