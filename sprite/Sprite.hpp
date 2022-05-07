#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <string>

class Sprite {
public:
  Sprite(SDL_Renderer *renderer, std::string texturePath, int x = 0, int y = 0, int width = 64,
         int height = 64);
  ~Sprite();

  void setPosition(int x, int y);
  void setX(int x);
  void setY(int y);
  void setSize(int width, int height);
  void setColorKey(std::string texturePath, Uint8 redKey, Uint8 greenKey, Uint8 blueKey);
  SDL_Texture *getTexture();
  SDL_Rect *getRectangle();
  int getWidth();
  int getHeight();
  SDL_Renderer *getRenderer();
  void render();

private:
  SDL_Texture *mTexture;
  SDL_Rect mRectangle;
  SDL_Renderer *mRenderer;
};

#endif
