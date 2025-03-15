#include "Program.hpp"

Program::Program()
{
  sf::Vector2i windowDim = 60 * sf::Vector2i(16, 9);
	window.create(sf::VideoMode(windowDim.x, windowDim.y), "It Takes A Village", sf::Style::Close);

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));

	window.setKeyRepeatEnabled(false);

  window.setVerticalSyncEnabled(true);

	view = window.getDefaultView();

  worldRect = sf::IntRect(-1000, -1000, 2000, 2000);

	tileTex.loadFromFile("assets/testTile.png");
  tile = sf::Sprite(tileTex);
  
	charTex.loadFromFile("assets/testAnim.png");
  character = sf::Sprite(charTex);
  character.setOrigin(0.5f * 6.0f * sf::Vector2f(8.0f, 8.0f));
  charAnim = Animator(&character, 6 * sf::Vector2i(8, 8), 0, 250);


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
        switch (e.key.code)
        {
          case sf::Keyboard::Escape:
            state = State::terminated;
            break;
          default:
            Keys::getInstance()->addKey(e.key.code);
            break;
        }
        break;

      case sf::Event::KeyReleased:
        Keys::getInstance()->removeKey(e.key.code);
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

  sf::Vector2f move = sf::Vector2f(
    KEY_HELD(sf::Keyboard::D) - KEY_HELD(sf::Keyboard::A), 
    KEY_HELD(sf::Keyboard::S) - KEY_HELD(sf::Keyboard::W));

  character.move((float)DELTA * move);

  if (move == sf::Vector2f(0.0f, 0.0f) && isCharMoving)
  {
    charAnim.setAnimation(0, 250);
    isCharMoving = false;
  }
  else if (move != sf::Vector2f(0.0f, 0.0f) && !isCharMoving)
  {
    charAnim.setAnimation(1, 100);
    isCharMoving = true;
  }

  charAnim.update();

  // Clip character within world bounds
  sf::Vector2f pos = character.getPosition();

  pos += clipWithinBounds(pos, 0.5f * 6.0f * sf::Vector2f(8.0f, 8.0f), worldRect);
  character.setPosition(pos);

  // Clip camera within world bounds
  pos += clipWithinBounds(pos, 0.5f * view.getSize(), worldRect);

  view.setCenter(pos);
  window.setView(view);

  Clock::getInstance()->update();
  Keys::getInstance()->update();
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

sf::Vector2f Program::clipWithinBounds(sf::Vector2f centre, sf::Vector2f padding, sf::IntRect bounds)
{
  sf::Vector2f correction(0, 0);

  if (centre.y - padding.y < bounds.top)
    correction.y = bounds.top - (centre.y - padding.y);

  else if (centre.y + padding.y > bounds.top + bounds.height)
    correction.y = (bounds.top + bounds.height) - (centre.y + padding.y);

  if (centre.x - padding.x < bounds.left)
    correction.x = bounds.left - (centre.x - padding.x);

  else if (centre.x + padding.x > bounds.left + bounds.width)
    correction.x = (bounds.left + bounds.width) - (centre.x + padding.x);
  
  return correction;
}
