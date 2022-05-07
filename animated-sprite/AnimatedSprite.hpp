#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <SDL2/SDL.h>
#include <string>

#include "../sprite/Sprite.hpp"

class AnimatedSprite {
public:
  AnimatedSprite(Sprite *spriteSheet, int totalFrames, int firstFrameX, int firstFrameY, int width,
                 int height, int *sequence = nullptr, int sequenceLength = 0);
  ~AnimatedSprite();

  void setPosition(int x, int y);
  void setSize(int width, int height);
  void advanceFrame();
  int getWidth();
  int getHeight();
  int getTotalFrames();
  int getCurrentFrame();
  void render();

private:
  int mTotalFrames;
  int mCurrentFrame = 0;
  int mCount = 0;
  int mFirstFrameX;
  Sprite *mSpriteSheet;
  SDL_Texture *mDestinationTexture;
  SDL_Rect mDestinationRectangle;
  SDL_Renderer *mRenderer;
  int *mSequence = nullptr;
};

#endif
