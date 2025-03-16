#include "Platform.hpp"

Platform::Platform(std::shared_ptr<Context> &context, std::string name)
  :
  m_context(context)
{
	view = WINDOW->getDefaultView();

	worldTex.loadFromFile("assets/texture/map.png");
  worldRect = sf::IntRect(sf::Vector2i(0, 0), 6 * (sf::Vector2i)worldTex.getSize());
  worldSprite = sf::Sprite(worldTex);
  worldSprite.setScale(sf::Vector2f(6.0f, 6.0f));
  
	charTex.loadFromFile("assets/texture/" + name + ".png");
  character = sf::Sprite(charTex);
  character.setOrigin(0.5f * (sf::Vector2f)charTex.getSize());
  character.setScale({6.0f, 6.0f});
  character.setPosition(0.5f * sf::Vector2f(worldRect.getSize()));
  // charAnim = Animator(&character, 0, 0, 250);
}

Platform::~Platform()
{
  WINDOW->setView(WINDOW->getDefaultView());
}

void Platform::Init()
{}

void Platform::ProcessInput()
{
	sf::Event e;
	
	while (WINDOW->pollEvent(e)) 
	{
		switch (e.type) 
		{
		case sf::Event::Closed: 
      m_context->m_states->PopAll();
      return;

      case sf::Event::KeyPressed:
        switch (e.key.code)
        {
          case sf::Keyboard::Escape:
          m_context->m_states->PopCurrent();
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

void Platform::Update(const sf::Time &deltaTime)
{

  sf::Vector2f move = sf::Vector2f(
    KEY_HELD(sf::Keyboard::D) - KEY_HELD(sf::Keyboard::A), 
    KEY_HELD(sf::Keyboard::S) - KEY_HELD(sf::Keyboard::W));

  character.move(0.5f * (float)deltaTime.asMilliseconds() * move);

  // if (move == sf::Vector2f(0.0f, 0.0f) && isCharMoving)
  // {
  //   charAnim.setAnimation(0, 250);
  //   isCharMoving = false;
  // }
  // else if (move != sf::Vector2f(0.0f, 0.0f) && !isCharMoving)
  // {
  //   charAnim.setAnimation(1, 100);
  //   isCharMoving = true;
  // }

  // charAnim.update(deltaTime);

  // Clip character within world bounds
  sf::Vector2f pos = character.getPosition();

  pos += clipWithinBounds(pos, 6.0f * 0.5f * (sf::Vector2f)charTex.getSize(), worldRect);
  character.setPosition(pos);

  // Clip camera within world bounds
  pos += clipWithinBounds(pos, 0.5f * view.getSize(), worldRect);

  view.setCenter(pos);
  WINDOW->setView(view);

  // Clock::getInstance()->update();
  Keys::getInstance()->update(deltaTime);
}

void Platform::Draw()
{
	WINDOW->clear({255, 255, 255});

  WINDOW->draw(worldSprite);

  WINDOW->draw(character);

  WINDOW->display();
}

sf::Vector2f Platform::clipWithinBounds(sf::Vector2f centre, sf::Vector2f padding, sf::IntRect bounds)
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
