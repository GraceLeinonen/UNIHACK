#ifndef Program_HPP
#define Program_HPP

#include <SFML/Graphics.hpp>

/// @brief Top level class responsible for handling the main program loop
class Program
{
public:
  enum class State
  {
    gameplay,
    terminated
  };

public:
  /// @brief Constructs the program and initialises a SFML window
  Program();

  /// @brief Handles SFML events
  void events();
  /// @brief Updates the program variables and classes
  void update();
  /// @brief Renders program components to the screen
  void render();

  /// @brief Returns whether the program has finished running
  /// @return `true` if the program is no longer running, `false` otherwise
  bool hasTerminated();

private:
  /// @brief The current status of the program
  State state = State::terminated;

  /// @brief The main SFML rendering window
  sf::RenderWindow window;

	/// @brief The view that represents the camera of the program
	sf::View view;

  sf::Texture tileTex;
  sf::Texture charTex;

  sf::IntRect worldRect;
  sf::Sprite tile;
  sf::Sprite character;
};


#endif