#include "Instructions.hpp"
#include "MainMenu.hpp"
#include <SFML/Window/Event.hpp>
#include <iostream>

Instructions::Instructions(std::shared_ptr<Context> &context)
{
    m_context= context;

    mainMenuButtonStates.isPressed=false;
    mainMenuButtonStates.isSelected=false;

}

Instructions::~Instructions()
{
}

void Instructions::display_text(AssetID font_name_enum, sf::Text& text, std::string title, int fontSize, float x_pos, float y_pos)
{
    
    text.setFont(m_context->m_assets->GetFont(font_name_enum));
    text.setString(title);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getLocalBounds().width / 2,
                           text.getLocalBounds().height / 2);
    text.setPosition(x_pos,y_pos);
    text.setCharacterSize(fontSize);
}

void Instructions::Init()
{
    //add new font to assets (already in mainMenu)
    //m_context->m_assets->AddFont(FONT1, "assets/fonts/SuperShape-PV9qE.ttf"); 
    //m_context->m_assets->AddFont(FONT2, "assets/fonts/Lato-BoldItalic.ttf");

    //load texture to background
    background.loadFromFile("assets/texture/game_instructions_background.png");
    background_object=sf::Sprite(background);

    // Display mainmenuButton
    display_text(FONT2,
                        mainMenuButton,
                        "Go Back to Main Menu",
                        50,
                        m_context->m_window->getSize().x / 2 -50.0f,
                        m_context->m_window->getSize().y / 2- 40.0f);
}

bool Instructions::isMouseOverText(sf::Text text)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return text.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

bool Instructions::isMouseOverSprite(sf::Sprite sprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return sprite.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

void Instructions::ProcessInput() //handle the selection and highlighting of the buttons
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
            if (isMouseOverText(mainMenuButton))
            {
                mainMenuButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    mainMenuButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverText(mainMenuButton))
            {
                mainMenuButtonStates.isSelected=false;
            }
            
        }
    }
}

void Instructions::Update(const sf::Time &deltaTime)
{
    if (mainMenuButtonStates.isSelected) 
    {
       mainMenuButton.setFillColor(sf::Color::Yellow);
        if (mainMenuButtonStates.isPressed)
        {
            //go back to main menu
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
            //m_context->m_states->PopAll();
        }
    }
    else if (!mainMenuButtonStates.isSelected) 
    {
       mainMenuButton.setFillColor(sf::Color::White);
    }

}

void Instructions::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(mainMenuButton);
    m_context->m_window->display();
}
