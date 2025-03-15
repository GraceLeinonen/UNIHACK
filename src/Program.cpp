#include "Program.hpp"

Program::Program()
{
  sf::Vector2i windowDim = 6 * sf::Vector2i(160, 90);
	window.create(sf::VideoMode(windowDim.x, windowDim.y), "It Takes A Village", sf::Style::Close);

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));

	window.setKeyRepeatEnabled(false);

	view = window.getDefaultView();

  state = State::gameplay;
}

void Program::events()
{
	sf::Event e;
	
	while (window.pollEvent(e)) 
	{
		switch (e.type) 
		{
		case sf::Event::Closed: 
      state = State::terminated;
      return;

		case sf::Event::KeyPressed:
      if (e.key.code == sf::Keyboard::Escape)
        state = State::terminated;
      break;

		default:
			break;
		}
	}
}

void Program::update()
{
  if (hasTerminated())
    return;
}

void Program::render()
{
  if (hasTerminated())
    return;

	window.clear({255, 255, 255});

  window.display();
}

bool Program::hasTerminated()
{
  return state == State::terminated;
}