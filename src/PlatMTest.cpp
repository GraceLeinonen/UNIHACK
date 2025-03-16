#include "SignIn.hpp"
#include "MainMenu.hpp"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>

SignIn::SignIn(std::shared_ptr<Context> &context)
{
    m_context= context;

    mainMenuButtonStates.isSelected=false;
    mainMenuButtonStates.isPressed=false;

    signin_graceStates.isPressed=false;
    signin_graceStates.isSelected=false;

    signin_michelleStates.isPressed=false;
    signin_michelleStates.isSelected=false;

    signin_kateStates.isSelected=false;
    signin_kateStates.isPressed=false;

    signin_noahStates.isSelected=false;
    signin_noahStates.isPressed=false;

}

SignIn::~SignIn()
{
}

void SignIn::display_text(AssetID font_name_enum, sf::Text& text, std::string title, int fontSize, float x_pos, float y_pos)
{
    
    text.setFont(m_context->m_assets->GetFont(font_name_enum));
    text.setString(title);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getLocalBounds().width / 2,
                           text.getLocalBounds().height / 2);
    text.setPosition(x_pos,y_pos);
    text.setCharacterSize(fontSize);
}

void SignIn::setTexture_addPosition( sf::Sprite &sprite, sf::Texture &texture, std::string file_path,float x_pos, float y_pos)
{
    std::cout<<"We are setting texture and add position to sprite of file: "<<file_path<<std::endl;
    texture.loadFromFile(file_path); 
    sprite.setTexture(texture); //or background_object=sf::Sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                           sprite.getLocalBounds().height / 2);
    sprite.setPosition(x_pos,y_pos);
}

void SignIn::Init()
{
    std::cout<<"void SignIn::Init()"<<std::endl;
    //add new font to assets (already in mainMenu)
    //m_context->m_assets->AddFont(FONT1, "assets/fonts/SuperShape-PV9qE.ttf"); 
    //m_context->m_assets->AddFont(FONT2, "assets/fonts/Lato-BoldItalic.ttf");

    //load texture to background
    background.loadFromFile("assets/texture/signin_background.png");
    background_object=sf::Sprite(background);
    
    float horizontal_position = m_context->m_window->getSize().x / 2;
    float vertical_position = m_context->m_window->getSize().y / 2;

    setTexture_addPosition(signin_grace,texture1, "assets/texture/signin_grace.png",horizontal_position-400.0f,vertical_position);
    setTexture_addPosition(signin_michelle,texture2,"assets/texture/signin_michelle.png",horizontal_position-150.0f,vertical_position);
    setTexture_addPosition(signin_kate,texture3,"assets/texture/signin_kate.png",horizontal_position+150.0f,vertical_position);
    setTexture_addPosition(signin_noah,texture4,"assets/texture/signin_noah.png",horizontal_position+400.0f,vertical_position); 

    // Display mainmenuButton
    display_text(FONT2,
                        mainMenuButton,
                        "Go Back to Main Menu",
                        50,
                        m_context->m_window->getSize().x / 2 -100.0f,
                        m_context->m_window->getSize().y - 40.0f);
}

bool SignIn::isMouseOverText(sf::Text text)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return text.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

bool SignIn::isMouseOverSprite(sf::Sprite sprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window));
    return sprite.getGlobalBounds().contains(mousePos.x,mousePos.y);
}

void SignIn::ProcessInput() //handle the selection and highlighting of the buttons
{
    std::cout<<"void SignIn::ProcessInput()"<<std::endl;
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

            //grace
            if (isMouseOverSprite(signin_grace))
            {
                signin_graceStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    signin_graceStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(signin_grace))
            {
                signin_graceStates.isSelected=false;
            }

            //michelle
            if (isMouseOverSprite(signin_michelle))
            {
                signin_michelleStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    signin_michelleStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(signin_michelle))
            {
                signin_michelleStates.isSelected=false;
            }
            
            //noah
            if (isMouseOverSprite(signin_noah))
            {
                signin_noahStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    signin_noahStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(signin_noah))
            {
                signin_noahStates.isSelected=false;
            }
            //kate
            if (isMouseOverSprite(signin_kate))
            {
                signin_kateStates.isSelected=true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    signin_kateStates.isPressed=true;
                }
            }
            else if (!isMouseOverSprite(signin_kate))
            {
                signin_kateStates.isSelected=false;
            }
        }
    }
}

void SignIn::Update(const sf::Time &deltaTime)
{
    std::cout<<"void SignIn::Update()"<<std::endl;

    //main button
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

    float ratio_toScale=1.2;
    //grace
    if (signin_graceStates.isSelected) 
    {
       //enlarge the image
       signin_grace.setScale(ratio_toScale,ratio_toScale);
        if (signin_graceStates.isPressed)
        {
            //go to platform under this user
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        }
    }
    else if (!signin_graceStates.isSelected) 
    {
       //going back to the original size of the image
       signin_grace.setScale(1.0,1.0);
    }
    //michelle
    if (signin_michelleStates.isSelected) 
    {
       //enlarge the image
       signin_michelle.setScale(ratio_toScale,ratio_toScale);
        if (signin_michelleStates.isPressed)
        {
            //go to platform under this user
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        }
    }
    else if (!signin_michelleStates.isSelected) 
    {
       //going back to the original size of the image
       signin_michelle.setScale(1.0,1.0);
    }
    //noah
    if (signin_noahStates.isSelected) 
    {
       //enlarge the image
       signin_noah.setScale(ratio_toScale,ratio_toScale);
        if (signin_noahStates.isPressed)
        {
            //go to platform under this user
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        }
    }
    else if (!signin_noahStates.isSelected) 
    {
       //going back to the original size of the image
       signin_noah.setScale(1.0,1.0);
    }
    //kate
    if (signin_kateStates.isSelected) 
    {
       //enlarge the image
       signin_kate.setScale(ratio_toScale,ratio_toScale);
        if (signin_kateStates.isPressed)
        {
            //go to platform under this user
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        }
    }
    else if (!signin_kateStates.isSelected) 
    {
       //going back to the original size of the image
       signin_kate.setScale(1.0,1.0);
    }
}

void SignIn::Draw()
{
    std::cout<<"void SignIn::Draw()"<<std::endl;
    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(signin_grace);
    std::cout<<"void SignIn::Draw():signin_grace "<<std::endl;
    m_context->m_window->draw(signin_michelle);
    std::cout<<"void SignIn::Draw():signin_michelle "<<std::endl;
    m_context->m_window->draw(signin_kate);
    m_context->m_window->draw(signin_noah);
    m_context->m_window->draw(mainMenuButton);
    m_context->m_window->display();
}
