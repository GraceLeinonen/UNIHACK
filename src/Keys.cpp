#include "Keys.hpp"

Keys* Keys::instance = nullptr;

void Keys::Key::update(const sf::Time &deltaTime)
{
  state = State::hold;

  timer -= deltaTime.asMilliseconds();
  if (timer < 0)
  {
    state = State::click;
    timer = CLICK_TIME;
  }
}

Keys *Keys::getInstance()
{
  if (instance == nullptr)
    instance = new Keys();
  return instance;
}

void Keys::update(const sf::Time &deltaTime)
{
  for (auto& key : activeKeys)
    key.second.update(deltaTime);
}

void Keys::addKey(sf::Keyboard::Key keyCode)
{
  activeKeys.insert({keyCode, Key()});
}

void Keys::removeKey(sf::Keyboard::Key keyCode)
{
  activeKeys.erase(keyCode);
}

bool Keys::isKeyFresh(sf::Keyboard::Key keyCode)
{
  auto it = activeKeys.find(keyCode);
  if (it == activeKeys.end())
    return false;
  return it->second.state == Key::State::fresh;
}

bool Keys::isKeyClicked(sf::Keyboard::Key keyCode)
{
  auto it = activeKeys.find(keyCode);
  if (it == activeKeys.end())
    return false;
  return it->second.state != Key::State::hold;
}

bool Keys::isKeyHeld(sf::Keyboard::Key keyCode)
{
  auto it = activeKeys.find(keyCode);
  if (it == activeKeys.end())
    return false;
  return true;
}
