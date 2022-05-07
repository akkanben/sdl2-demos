#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "../sprite/Sprite.cpp"
#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(Sprite *spriteSheet, int totalFrames, int firstFrameX,
                               int firstFrameY, int width, int height, int *sequence,
                               int sequenceLength) {
  mRenderer = spriteSheet->getRenderer();
  mSpriteSheet = spriteSheet;
  mFirstFrameX = firstFrameX;
  mTotalFrames = totalFrames;

  if (sequence != nullptr && sequenceLength > 0) {
    mSequence = sequence;
    mTotalFrames = sequenceLength;
  }

  mDestinationRectangle.x = firstFrameX;
  mDestinationRectangle.y = firstFrameY;
  mDestinationRectangle.w = width;
  mDestinationRectangle.h = height;
}

AnimatedSprite::~AnimatedSprite() { SDL_DestroyTexture(mDestinationTexture); }

void AnimatedSprite::setPosition(int x, int y) {
  mDestinationRectangle.x = x;
  mDestinationRectangle.y = y;
}

void AnimatedSprite::setSize(int width, int height) {
  mDestinationRectangle.w = width;
  mDestinationRectangle.h = height;
  if (mDestinationRectangle.w < 1)
    mDestinationRectangle.w = 1;
  if (mDestinationRectangle.h < 1)
    mDestinationRectangle.h = 1;
}

void AnimatedSprite::advanceFrame() {
  mSpriteSheet->setX(mCurrentFrame * mSpriteSheet->getWidth());
  if (mSequence) {
    mCount++;
    mCount %= mTotalFrames;
    mCurrentFrame = mSequence[mCount];
  } else {
    mCurrentFrame = ++mCurrentFrame % mTotalFrames;
  }
}

int AnimatedSprite::getWidth() { return mDestinationRectangle.w; }

int AnimatedSprite::getHeight() { return mDestinationRectangle.h; }

int AnimatedSprite::getTotalFrames() { return mTotalFrames; }

int AnimatedSprite::getCurrentFrame() { return mCurrentFrame; }

void AnimatedSprite::render() {
  SDL_RenderCopy(mRenderer, mSpriteSheet->getTexture(), mSpriteSheet->getRectangle(),
                 &mDestinationRectangle);
}
