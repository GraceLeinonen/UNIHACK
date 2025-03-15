#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "Clock.hpp"

/// @brief Handles the animation for a gien sprite
class Animator
{
public:
  Animator() = default;

  /// @brief Constructs animation handler, expects spritesheet to 
  /// consist of a row for each animation, and a column for each frame,
  /// where each frame is of size `spriteDim`
  /// @param sprite - The pointer to the sprite(sheet) that is being managed
  /// @param frameDim - The dimensions of a frame of animation, the will be the dimensions of the final sprite on screen
  /// @param initialAnimation - The initial animation index, corresponds to which row on the sprite sheet to use for animation
  /// @param frameDuration - The amount of time (in millisecond) each frame is held before advancing to the next
  Animator(sf::Sprite* sprite, sf::Vector2i frameDim, int initialAnimation, int frameDuration);

  /// @brief Updates the handler, advancing the frame if required
  void update();

  /// @brief Replaces the current animation with a new one
  /// @param animationIndex - The animation index, corresponds to the row of the animation in the spritesheet
  /// @param frameDuration  - The amount of time (in milliseconds) each frame is held before advancing to the next
  void setAnimation(int animationIndex, int frameDuration);

private:
  /// @brief Advances the animation to the next frame
  void advanceFrame();

  /// @brief Updated the sprites underlying texture rectangle to properly render the new frame
  void setFrameRegion();

private:
  /// @brief A pointer to the sprite that is being managed
  sf::Sprite* sprite = nullptr;
  /// @brief The dimensions of a frame of animation
  sf::Vector2i frameDim = sf::Vector2i(0, 0);

  /// @brief The current animation being played
  int animIndex = 0;
  /// @brief The duration of a frame for the current animation
  int frameDur = 0;

  /// @brief The timer use to determine when to advane to the next frame
  int timer = 0;
  /// @brief The current frame of animation
  int curFrame = 0;
};

#endif