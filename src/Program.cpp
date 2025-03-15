#include "Program.hpp"

Program::Program()
{
  sf::Vector2i windowDim = 6 * sf::Vector2i(160, 90);
	window.create(sf::VideoMode(windowDim.x, windowDim.y), "It Takes A Village", sf::Style::Close);

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));

	window.setKeyRepeatEnabled(false);

	view = window.getDefaultView();

  worldRect = sf::IntRect(-1000, -1000, 2000, 2000);

	tileTex.loadFromFile("assets/testTile.png");
  tile = sf::Sprite(tileTex);
  

	charTex.loadFromFile("assets/testChar.png");
  character = sf::Sprite(charTex);
  character.setOrigin(0.5f * (sf::Vector2f)charTex.getSize());

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

  for (int y = worldRect.top; y < worldRect.top + worldRect.height; y += tileTex.getSize().y)
  {
    for (int x = worldRect.left; x < worldRect.left + worldRect.width; x += tileTex.getSize().x)
    {
      tile.setPosition(sf::Vector2f(x, y));
      window.draw(tile);
    }
  }

  window.draw(character);

  window.display();
}

bool Program::hasTerminated()
{
  return state == State::terminated;
}