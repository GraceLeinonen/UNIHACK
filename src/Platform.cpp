#include "Platform.hpp"

Platform::Platform(std::shared_ptr<Context> &context, std::string name)
  :
  m_context(context)
{
	view = WINDOW->getDefaultView();

	worldTex.loadFromFile("assets/texture/map/map.png");
  worldRect = sf::IntRect(sf::Vector2i(0, 0), (int)SCALE * (sf::Vector2i)worldTex.getSize());
  worldSprite = sf::Sprite(worldTex);
  worldSprite.setScale(SCALE_VEC);
  
	charTex.loadFromFile("assets/texture/characters/" + name + ".png");
  character = sf::Sprite(charTex);
  character.setOrigin(0.5f * (sf::Vector2f)charTex.getSize());
  character.setScale(SCALE_VEC);
  character.setPosition(0.5f * sf::Vector2f(worldRect.getSize()));
  // charAnim = Animator(&character, 0, 0, 250);

  shadowTex.loadFromFile("assets/texture/characters/shadow.png");
  shadow = sf::Sprite(shadowTex);
  shadow.setOrigin(0.5f * (sf::Vector2f)shadowTex.getSize());
  shadow.setScale(SCALE_VEC);

  std::vector<std::string> colours = {"blue", "purple", "red", "yellow"};
  std::vector<std::string> habitNames = {"brushTeeth", "exercise", "cookMeal", "journalling"};
  std::vector<sf::Vector2f> positions = 
  {
    {145.0f, 78.0f}, 
    {85.0f, 190.0f}, 
    {333.0f, 240.0f}, 
    {393.0f, 70.0f}
  };
  houses.reserve(colours.size());

  for (int i = 0; i < colours.size(); i++)
  {
    std::string houseState = i % 2 == 0 ? "bad" : "good";
    houses.push_back({});
    HouseSprite& house = houses.back();
    house.tex.loadFromFile("assets/texture/map/house_" + colours[i] + "_" + houseState + ".png");

    house.sprite.setTexture(house.tex);
    house.sprite.setScale(SCALE_VEC);
    house.sprite.setPosition(SCALE * positions[i]);
    house.sprite.setOrigin(sf::Vector2f(
      0.5f * house.tex.getSize().x,
      house.tex.getSize().y));

    house.habit = habitNames[i];
  }
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

  pos += clipWithinBounds(pos, SCALE * 0.5f * (sf::Vector2f)charTex.getSize(), worldRect);
  character.setPosition(pos);

  shadow.setPosition(pos + sf::Vector2f(0.0f, 0.5f * character.getGlobalBounds().height));

  // Clip camera within world bounds
  pos += clipWithinBounds(pos, 0.5f * view.getSize(), worldRect);

  view.setCenter(pos);
  WINDOW->setView(view);


  houseIndex = NONE;
  for (int i = 0; i < houses.size(); i++)
  {
    houses[i].sprite.setColor(sf::Color(255, 255, 255));
    if (houses[i].sprite.getGlobalBounds().intersects(character.getGlobalBounds()))
    {
      houseIndex = i;
      houses[i].sprite.setColor(sf::Color(200, 250, 200));
    }
  }

  if (houseIndex != NONE && KEY_FRESH(sf::Keyboard::Enter))
  {
    std::cout << "House " << houses[houseIndex].habit << " was interacted with!\n";
    m_context->m_states->Add(std::make_unique<House>(m_context, Habits(houses[houseIndex].habit)));
  }

  // Clock::getInstance()->update();
  Keys::getInstance()->update(deltaTime);
}

void Platform::Draw()
{
	WINDOW->clear({255, 255, 255});

  WINDOW->draw(worldSprite);

  for (auto& house : houses)
    WINDOW->draw(house.sprite);

  WINDOW->draw(shadow);

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
