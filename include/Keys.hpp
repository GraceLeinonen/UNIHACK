#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <unordered_map>

#include "Clock.hpp"

#define CLICK_TIME 50

#define KEY_FRESH(key) Keys::getInstance()->isKeyFresh(key)
#define KEY_CLICK(key) Keys::getInstance()->isKeyClicked(key)
#define KEY_HELD(key) Keys::getInstance()->isKeyHeld(key)

/// @brief Handles the state of keys on the users keyboard
class Keys
{
private:
  /// @brief Stores and handles the state of an individual key
  struct Key
  {
  public:
    /// @brief The different states of a key
    enum class State
    {
      fresh,
      click,
      hold
    };

  public:
    Key() = default;

    /// @brief Updates the state of the key
    void update();

  public:
    /// @brief The click state of the key
    State state = State::fresh;

    /// @brief The time it takes for a click to be registered as a key is held
    int timer = 5 * CLICK_TIME;
  };

private:
  /// @brief The global Clock instance
  static Keys* instance;

public:
  /// @brief Gets (and creates, if not already made) the global Keys instance
  /// @return A pointer to the Keys instance
  static Keys* getInstance();

  /// @brief Updates the state of a currently active keys
  void update();

  /// @brief Adds a key to the set of active keys
  /// @param keyCode - The keycode of the key to be added
  void addKey(sf::Keyboard::Key keyCode);

  /// @brief Removes a key from the set of active keys
  /// @param keyCode - The keycode of the key to be removed
  void removeKey(sf::Keyboard::Key keyCode);

  /// @brief Returns whether the key press is fresh, i.e. was clicked within the last update cycle
  /// @param keyCode - The keycode of the key to lookup
  /// @return `true` if the key is fresh, `false` otherwise
  bool isKeyFresh(sf::Keyboard::Key keyCode);

  /// @brief Returns whether the key is clicked, which happens periodically at set intervals while held
  /// @param keyCode - The keycode of the key to lookup
  /// @return `true` if the key is clicked, `false` otherwise
  bool isKeyClicked(sf::Keyboard::Key keyCode);

  /// @brief Returns whether the key press is being held
  /// @param keyCode - The keycode of the key to lookup
  /// @return `true` if the key is held, `false` otherwise
  bool isKeyHeld(sf::Keyboard::Key keyCode);

private:
  /// @brief The map of currently active keys
  std::unordered_map<sf::Keyboard::Key, Key> activeKeys;
};

#endif