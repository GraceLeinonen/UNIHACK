#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SFML/Graphics.hpp>

#define DELTA (Clock::getInstance()->getDeltaTime())

/// @brief The program clock, keeps track of the amount of time elapsed between program cycles
class Clock
{
private:
  /// @brief Initialises Clock to be in sync with the sfml clock
  Clock();

  /// @brief The global Clock instance
  static Clock* instance;

public:
  /// @brief Gets (and creates, if not already made) the global Clock instance
  /// @return A pointer to the Clock instance
  static Clock* getInstance();

  /// @brief Updates delta time given the timestamp of the previous update() call
  void update();

  /// @brief Gets the amount of time between update() calls
  /// @return The time, in milliseconds, between update() calls
  int getDeltaTime();

  /// @brief Gets the amount of time elapsed since initialisation
  /// @return The time, in milliseconds, since initialisation
  sf::Int32 getElapsedTime();

private:
  /// @brief The underlying sfml clock used for time updates
  sf::Clock clock;

  /// @brief Stores the timestamp of last time update() was called
  sf::Int32 prevCycle;

  /// @brief Stores the difference in time between the last two update() calls
  int delta;
};

#endif