#include "YellowHouse.hpp"
#include "MainMenu.hpp"
#include <SFML/Window/Event.hpp>
#include <iostream>

YellowHouse::YellowHouse(std::shared_ptr<Context> &context)
{
    m_context= context;

    mainMenuButtonStates.isPressed=false;
    mainMenuButtonStates.isSelected=false;

}

YellowHouse::~YellowHouse()
{
}

bool YellowHouse::isMouseOverSprite(std::shared_ptr<Context> &m_context, sf::Sprite sprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return sprite.getGlobalBounds().contains(mousePos.x,mousePos.y);
};
void YellowHouse::setTexture_addPosition(sf::Sprite &sprite, sf::Texture &texture, std::string file_path,float x_pos, float y_pos)
{
    texture.loadFromFile(file_path); 
    sprite.setTexture(texture); //or background_object=sf::Sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                        sprite.getLocalBounds().height / 2);
    sprite.setPosition(x_pos,y_pos);
};

void YellowHouse::Init()
{
    //add new font to assets (already in mainMenu)
    //m_context->m_assets->AddFont(FONT1, "assets/fonts/SuperShape-PV9qE.ttf"); 
    //m_context->m_assets->AddFont(FONT2, "assets/fonts/Lato-BoldItalic.ttf");

    //load texture to background
    background.loadFromFile("assets/texture/yellow_house_bg.png");
    background_object=sf::Sprite(background);

    // Display mainmenuButton
    float horizontal_position = m_context->m_window->getSize().x / 2;
    setTexture_addPosition(mainMenuButton,mainMenuTexture,"assets/texture/yellow_house_toVillage.png",horizontal_position,m_context->m_window->getSize().y-50.0f); 
}

void YellowHouse::ProcessInput() //handle the selection and highlighting of the buttons
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_states->PopAll();
        }
        else 
        {
            if (isMouseOverSprite(m_context,mainMenuButton))
            {
                mainMenuButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    mainMenuButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(m_context,mainMenuButton))
            {
                mainMenuButtonStates.isSelected=false;
            }
            
        }
    }
}

void YellowHouse::Update(const sf::Time &deltaTime)
{
    if (mainMenuButtonStates.isSelected) 
    {
       mainMenuButton.setScale(1.2,1.2);
        if (mainMenuButtonStates.isPressed)
        {
            //go back to main menu
            //m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
            m_context->m_states->PopCurrent();
        }
    }
    else if (!mainMenuButtonStates.isSelected) 
    {
       mainMenuButton.setScale(1.0,1.0);
    }

}

void YellowHouse::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(mainMenuButton);
    m_context->m_window->display();
}
