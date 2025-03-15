#include "Animation.hpp"

Animator::Animator(sf::Sprite *sprite, sf::Vector2i frameDim, int initialAnimation, int frameDuration)
  :
  sprite(sprite),
  frameDim(frameDim),
  animIndex(initialAnimation),
  frameDur(frameDuration)
{
  setFrameRegion();
}

void Animator::update()
{
  timer -= DELTA;
  while (timer <= 0)
    advanceFrame();
}

void Animator::setAnimation(int animationIndex, int frameDuration)
{
  animIndex = animationIndex;
  frameDur = frameDuration;

  curFrame = 0;
  timer = frameDur;

  setFrameRegion();
}

void Animator::advanceFrame()
{
  curFrame++;
  if (curFrame * frameDim.x >= sprite->getTexture()->getSize().x)
    curFrame = 0;
  
  timer += frameDur;
  setFrameRegion();
}

void Animator::setFrameRegion()
{
  sf::IntRect texRect;

  texRect.left = curFrame * frameDim.x;
  texRect.top = animIndex * frameDim.y;

  texRect.width = frameDim.x;
  texRect.height = frameDim.y;

  sprite->setTextureRect(texRect);
}
