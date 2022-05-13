#include <SDL2/SDL_render.h>
#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

int main() {
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("TTF Fonts", 0, 0, 640, 480, 0);

  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (TTF_Init() == -1) {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    exit(1);
  }

  SDL_Renderer *renderer = nullptr;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  TTF_Font *font = TTF_OpenFont("./enough.ttf", 64);

  SDL_Surface *surface = TTF_RenderText_Solid(font, "TEXT", {0xE4, 0x19, 0x51});
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  surface = TTF_RenderText_Solid(font, "TEXT", {0x1C, 0x15, 0x3D});
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  SDL_Rect rectangle1;
  int size = 450;
  rectangle1.x = (640 - size) / 2;
  rectangle1.y = (480 - size) / 2;
  rectangle1.w = size;
  rectangle1.h = size;

  int offset = 10;
  SDL_Rect rectangle2;
  rectangle2.x = (640 - size + offset) / 2;
  rectangle2.y = (480 - size + offset) / 2;
  rectangle2.w = size / 2;
  rectangle2.h = size / 2;

  // Setup animation
  Uint32 animationSpeed = 1000 / 60;
  Uint32 nextAnimationTick = 1000 / 60;
  bool isSizeGrowing = true;
  bool isOffsetGrowing = true;
  bool appIsRunning = true;
  bool flip = false; // Toggle rendering rectangle order
  while (appIsRunning) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Event queue
      switch (event.type) {
      case SDL_QUIT:
        appIsRunning = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE)
          flip = !flip;
        break;
      default:
        break;
      }
    }

    Uint32 now = SDL_GetTicks();
    if (nextAnimationTick <= now) {
      if (isSizeGrowing) {
        if (isOffsetGrowing)
          offset++;
        size++;
        // rect1
        rectangle1.h = size;
        rectangle1.w = size;
        rectangle1.x = (640 - size) / 2;
        rectangle1.y = (480 - size) / 2;

        // rect2
        rectangle2.h = size + offset;
        rectangle2.w = size + offset;
        rectangle2.x = (640 - size + offset) / 2;
        rectangle2.y = (480 - size + offset) / 2;
      } else {
        if (!isOffsetGrowing)
          offset--;
        size--;
        rectangle1.h = size;
        rectangle1.w = size;
        rectangle1.x = (640 - size) / 2;
        rectangle1.y = (480 - size) / 2;

        rectangle2.h = size + offset;
        rectangle2.w = size + offset;
        rectangle2.x = (640 - size + offset) / 2;
        rectangle2.y = (480 - size + offset) / 2;
      }
      if (rectangle1.w > 500)
        isSizeGrowing = false;
      if (rectangle1.w < 400)
        isSizeGrowing = true;
      if (offset > 5)
        isOffsetGrowing = false;
      if (offset < -5)
        isOffsetGrowing = true;
      nextAnimationTick += animationSpeed;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    if (flip) {
      SDL_RenderCopy(renderer, texture2, NULL, &rectangle2);
      SDL_RenderCopy(renderer, texture, NULL, &rectangle1);
    } else {
      SDL_RenderCopy(renderer, texture, NULL, &rectangle1);
      SDL_RenderCopy(renderer, texture2, NULL, &rectangle2);
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  SDL_Quit();
  return 0;
}
