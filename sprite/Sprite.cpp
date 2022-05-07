#include <string>

#include <SDL2/SDL.h>

#include "Sprite.hpp"

Sprite::Sprite(SDL_Renderer *renderer, std::string texturePath, int x, int y, int width,
               int height) {
  mRenderer = renderer;
  SDL_Surface *surface = SDL_LoadBMP(texturePath.c_str());
  mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
  mRectangle.x = x;
  mRectangle.y = y;
  mRectangle.h = height;
  mRectangle.w = width;
}

Sprite::~Sprite() { SDL_DestroyTexture(mTexture); }

void Sprite::setPosition(int x, int y) {
  mRectangle.x = x;
  mRectangle.y = y;
}

void Sprite::setX(int x) { mRectangle.x = x; }

void Sprite::setY(int y) { mRectangle.y = y; }

void Sprite::setSize(int width, int height) {
  mRectangle.w = width;
  mRectangle.h = height;
  if (mRectangle.w < 1)
    mRectangle.w = 1;
  if (mRectangle.h < 1)
    mRectangle.h = 1;
}

void Sprite::setColorKey(std::string texturePath, Uint8 redKey, Uint8 greenKey, Uint8 blueKey) {
  SDL_Surface *surface = SDL_LoadBMP(texturePath.c_str());
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, redKey, greenKey, blueKey));
  mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
}

SDL_Texture *Sprite::getTexture() { return mTexture; }

SDL_Rect *Sprite::getRectangle() { return &mRectangle; }

int Sprite::getWidth() { return mRectangle.w; }

int Sprite::getHeight() { return mRectangle.h; }

SDL_Renderer *Sprite::getRenderer() { return mRenderer; }

void Sprite::render() { SDL_RenderCopy(mRenderer, mTexture, NULL, &mRectangle); }
