#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "AnimatedSprite.hpp"

int main() {
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_ShowCursor(0); // hide mouse
  window = SDL_CreateWindow("Animated Sprites", 0, 0, 640, 480, 0);

  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *renderer = nullptr;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Setup walking hero sprite
  Sprite heroSpriteSheet = Sprite(renderer, "./res/spritesheet.bmp", 0, 0, 16, 32);
  heroSpriteSheet.setColorKey("./res/spritesheet.bmp", 146, 144, 255);
  AnimatedSprite hero = AnimatedSprite(&heroSpriteSheet, 3, 0, 0, 37, 74);

  // Setup flashing block with custom sequence
  Sprite blockSpriteSheet = Sprite(renderer, "./res/spritesheet.bmp", 0, 32, 16, 16);
  blockSpriteSheet.setColorKey("./res/spritesheet.bmp", 146, 144, 255);
  int seq[] = {0, 0, 0, 0, 0, 0, 0, 1, 2};
  AnimatedSprite block = AnimatedSprite(&blockSpriteSheet, 3, 309, 150, 37, 37, seq, 9);

  // Setup background sprite
  Sprite background = Sprite(renderer, "./res/bg.bmp", 0, 0, 640, 480);

  // Setup independant animation speed and game logic speed
  Uint32 animationSpeed = 1000 / 8;
  Uint32 gameSpeed = 1000 / 60;
  Uint32 nextGameTick = SDL_GetTicks();
  Uint32 nextAnimationTick = 1000 / 8;
  bool appIsRunning = true;
  while (appIsRunning) {
    Uint32 now = SDL_GetTicks();

    if (nextGameTick <= now) {
      // Do Game Tick
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);
      background.render();
      hero.render();
      block.render();
    }

    if (nextAnimationTick <= now) {
      // Do Animation Tick
      hero.advanceFrame();
      block.advanceFrame();
      nextAnimationTick += animationSpeed;
    }

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
    SDL_Delay(16);
  }

  SDL_DestroyWindow(window);
  return 0;
}
