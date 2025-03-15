#include "Clock.hpp"

Clock* Clock::instance = nullptr;

Clock::Clock()
{
  prevCycle = getElapsedTime();
}

Clock *Clock::getInstance()
{
  if (instance == nullptr)
    instance = new Clock();
  return instance;
}

void Clock::update()
{
  delta = getElapsedTime() - prevCycle;
  prevCycle = getElapsedTime();
}

int Clock::getDeltaTime()
{
  return delta;
}

sf::Int32 Clock::getElapsedTime()
{
  return clock.getElapsedTime().asMilliseconds();
}
