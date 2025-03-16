//include the hpp files of all states
#include "MainMenu.hpp"
#include "SignIn.hpp"
#include "Instructions.hpp"
#include <iostream>
#include <string>

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
{
    m_context= context;

    signInButtonStates.isSelected=false;
    signInButtonStates.isPressed=false;

    instructionsButtonStates.isSelected=false;
    instructionsButtonStates.isPressed=false;

    exitButtonStates.isSelected=false;
    exitButtonStates.isPressed=false;

}

MainMenu::~MainMenu()
{
}

bool MainMenu::isMouseOverSprite(std::shared_ptr<Context> &m_context, sf::Sprite sprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return sprite.getGlobalBounds().contains(mousePos.x,mousePos.y);
};
void MainMenu::setTexture_addPosition(sf::Sprite &sprite, sf::Texture &texture, std::string file_path,float x_pos, float y_pos)
{
    texture.loadFromFile(file_path); 
    sprite.setTexture(texture); //or background_object=sf::Sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                        sprite.getLocalBounds().height / 2);
    sprite.setPosition(x_pos,y_pos);
};


void MainMenu::Init()
{
    //add font to assets
    m_context->m_assets->AddFont(FONT1, "assets/fonts/SuperShape-PV9qE.ttf"); 
    m_context->m_assets->AddFont(FONT2, "assets/fonts/Lato-BoldItalic.ttf");

    //load texture to background
    background.loadFromFile("assets/texture/main_menu_background.png");
    background_object=sf::Sprite(background);


    float under_border= m_context->m_window->getSize().y-70.0f;
    //Display buttons
   
    setTexture_addPosition(instructionsButton, texture2, "assets/texture/mainmenuButton_instruction.png",160.0f, under_border);
    setTexture_addPosition(signInButton, texture1, "assets/texture/mainmenuButton_login.png",480.0f, under_border);
    setTexture_addPosition(exitButton, texture3, "assets/texture/mainmenuButton_exit.png",800.0f, under_border);

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
            if (isMouseOverSprite(m_context,signInButton))
            {
                signInButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    signInButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(m_context, signInButton))
            {
                signInButtonStates.isSelected=false;
            }
            
            if (isMouseOverSprite(m_context, instructionsButton))
            {
                instructionsButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    instructionsButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(m_context, instructionsButton))
            {
                instructionsButtonStates.isSelected=false;
            }  

            if (isMouseOverSprite(m_context, exitButton))
            {
                exitButtonStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    exitButtonStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(m_context, exitButton))
            {
                exitButtonStates.isSelected=false;
            } 
        }
    }
}

void MainMenu::Update(const sf::Time &deltaTime)
{
  float ratio_toScale=1.2;
    if (signInButtonStates.isSelected) 
    {
       signInButton.setScale(ratio_toScale,ratio_toScale);
    }
    else if (!signInButtonStates.isSelected) 
    {
       signInButton.setScale(1.0,1.0);
    }

    if (instructionsButtonStates.isSelected)
    {
        instructionsButton.setScale(ratio_toScale,ratio_toScale);
    }
    else if (!instructionsButtonStates.isSelected)
    {
        instructionsButton.setScale(1.0,1.0);
    }
    if (exitButtonStates.isSelected)
    {
        exitButton.setScale(ratio_toScale,ratio_toScale);
    }
    else if (!exitButtonStates.isSelected)
    {
        exitButton.setScale(1.0,1.0);
    }

    if (signInButtonStates.isPressed)
    {
        //GoTo SignIn
        m_context->m_states->Add(std::make_unique<SignIn>(m_context), true);
    }
    else if (instructionsButtonStates.isPressed)
    {
        //Go to Instructions
        m_context->m_states->Add(std::make_unique<Instructions>(m_context), true);
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
    m_context->m_window->draw(signInButton);
    m_context->m_window->draw(instructionsButton);
    m_context->m_window->draw(exitButton);
    m_context->m_window->display();
}
