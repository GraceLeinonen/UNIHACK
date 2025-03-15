//include the hpp files of all states
#include "MainMenu.hpp"
#include <iostream>
#include <string>

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
{
    m_context= context;

    signInButtonStates.isSelected=false;
    signInButtonStates.isPressed=false;

    signInButtonStates.isSelected=false;
    signInButtonStates.isPressed=false;

    signInButtonStates.isSelected=false;
    signInButtonStates.isPressed=false;

}

MainMenu::~MainMenu()
{
}

void MainMenu::display_instructions(AssetID font_name_enum, sf::Text& text, std::string title, int fontSize, float x_pos, float y_pos)
{
    
    text.setFont(m_context->m_assets->GetFont(font_name_enum));
    text.setString(title);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getLocalBounds().width / 2,
                           text.getLocalBounds().height / 2);
    text.setPosition(x_pos,y_pos);
    text.setCharacterSize(fontSize);
}

void MainMenu::Init()
{
    //add font to assets
    m_context->m_assets->AddFont(FONT1, "assets/fonts/SuperShape-PV9qE.ttf"); 
    m_context->m_assets->AddFont(FONT2, "assets/fonts/Lato-BoldItalic.ttf");

    //load texture to background
    background.loadFromFile("assets/texture/main_menu_background.png");
    background_object=sf::Sprite(background);

    // Display Title
    display_instructions(FONT1,
                        gameTitle,
                        "It Takes A Village",
                        70,
                        m_context->m_window->getSize().x / 2 -100.0f,
                        m_context->m_window->getSize().y / 2-100.0f);


    float under_border= m_context->m_window->getSize().y-70.0f;
    //Display Sign in
    display_instructions(FONT2,
                        signInButton,
                        "Sign in",
                        30,
                        m_context->m_window->getSize().x / 2,
                        under_border);
    
    //Display Instruction
    display_instructions(FONT2,
                        instructionsButton,
                        "Instructions",
                        30,
                        100.f,
                        under_border);
    
    //Display Instruction
    display_instructions(FONT2,
                        exitButton,
                        "Exit",
                        30,
                        m_context->m_window->getSize().x-100.0f,
                        under_border);


}

/*
Tutorial: dealing with Mouse events
- Using sf::Mouse::getPosition().x returns the position relative to the desktop, you if you want it relative to your renderWindow you need to do: sf::Mouse::getPosition(renderWindow).x
- bool Match (float x, float y)
{
   return m_rect.Contains (x,y);
}
- 
*/

bool MainMenu::isMouseOverText(sf::Text text)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return text.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

bool MainMenu::isMouseOverSprite(sf::Sprite sprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return sprite.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

void MainMenu::ProcessInput() //handle the selection and highlighting of the buttons
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
            if (isMouseOverText(signInButton))
            {
                signInButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    signInButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverText(signInButton))
            {
                signInButtonStates.isSelected=false;
            }
            
            if (isMouseOverText(instructionsButton))
            {
                instructionsButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    instructionsButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverText(instructionsButton))
            {
                instructionsButtonStates.isSelected=false;
            }  

            if (isMouseOverText(exitButton))
            {
                exitButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    exitButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverText(exitButton))
            {
                exitButtonStates.isSelected=false;
            } 
            
        }
    }
}

void MainMenu::Update(const sf::Time &deltaTime)
{
    if (signInButtonStates.isSelected) 
    {
       signInButton.setFillColor(sf::Color::Yellow);
    }
    else if (!signInButtonStates.isSelected) 
    {
       signInButton.setFillColor(sf::Color::White);
    }

    if (instructionsButtonStates.isSelected)
    {
        instructionsButton.setFillColor(sf::Color::Yellow);
    }
    else if (!instructionsButtonStates.isSelected)
    {
        instructionsButton.setFillColor(sf::Color::White);
    }
    if (exitButtonStates.isSelected)
    {
        exitButton.setFillColor(sf::Color::Yellow);
    }
    else if (exitButtonStates.isSelected)
    {
        exitButton.setFillColor(sf::Color::White);
    }

    if (signInButtonStates.isPressed)
    {
        //The game starts. Go to Play State
        //m_context->m_states->Add(std::make_unique<Stage1>(m_context), true);

        // Hijacking signin button because there is no play button
        m_context->m_states->Add(std::make_unique<Gameplay>(m_context));
        signInButtonStates.isPressed = false;
    }
    else if (instructionsButtonStates.isPressed)
    {
        //Go to Settings State
        //m_context->m_states->Add(std::make_unique<Instructions>(m_context), true);

        // m_context->m_states->PopAll();
    }
    else if (exitButtonStates.isPressed) //if exit button is pressed, have to close the window
    {
        m_context->m_states->PopAll();
    }
}

void MainMenu::Draw()
{
    
    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(gameTitle);
    m_context->m_window->draw(signInButton);
    m_context->m_window->draw(instructionsButton);
    m_context->m_window->draw(exitButton);
    m_context->m_window->display();
}
