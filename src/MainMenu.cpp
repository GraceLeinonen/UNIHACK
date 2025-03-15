//include the hpp files of all states
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
{
    m_context=context;

    m_isPlayButtonSelected=true;
    m_isPlayButtonPressed=false;

    m_isInstructionsButtonSelected=false;
    m_isInstructionsButtonPressed=false;

    m_isExitButtonSelected=false;
    m_isExitButtonPressed=false;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    //add font to assets
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/BraveEightyoneRegular-ZVGvm.ttf"); 

    //load texture to background
    background.loadFromFile("assets/textures/mainMenuBackground.png");
    background_object=sf::Sprite(background);

    // Display Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
                           m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 );
    m_playButton.setCharacterSize(35);

    //Display Instructions 
    m_instructionsButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_instructionsButton.setString("Instructions");
    m_instructionsButton.setOrigin(m_playButton.getLocalBounds().width / 2,
                           m_playButton.getLocalBounds().height / 2);
    m_instructionsButton.setPosition(m_context->m_window->getSize().x / 2-35.f,
                             m_context->m_window->getSize().y / 2 + 55.f);
    m_instructionsButton.setCharacterSize(35);

    // Display Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                           m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 + 100.f);
    m_exitButton.setCharacterSize(35);
}

void MainMenu::ProcessInput() //handle the selection and highlighting of the buttons
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_states->PopAll();
            ;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                //Handle each of the 3 cases, (1) if the Exit button is currently selected,(2) if the Instructions button is currently selected and (3)if the Play button is selected, then you don't have do to anything because it's already the highest button
                if (m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isInstructionsButtonSelected=true;
                    m_isExitButtonSelected = false;

                }
                else if (m_isInstructionsButtonSelected)
                {
                    m_isPlayButtonSelected = true;
                    m_isInstructionsButtonSelected=false;
                    m_isExitButtonSelected = false;
                }
                else if (m_isPlayButtonSelected) //first check if play button is selected. If it already is, we don't have to do anything.
                { 
                    m_isPlayButtonSelected = true;
                    m_isInstructionsButtonSelected=false;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (m_isPlayButtonSelected) //second check if the exit button is selected. it's already the downer-most button, so if it is and still press down arrow, no need to do anything
                {
                    m_isPlayButtonSelected = false;
                    m_isInstructionsButtonSelected=true;
                    m_isExitButtonSelected = false;
                }
                else if (m_isInstructionsButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isInstructionsButtonSelected=false;
                    m_isExitButtonSelected = true;
                }
                else if (m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isInstructionsButtonSelected=false;
                    m_isExitButtonSelected = true;                  
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isPlayButtonPressed = false;
                m_isInstructionsButtonPressed=false;
                m_isExitButtonPressed = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else if(m_isInstructionsButtonSelected)
                {
                    m_isInstructionsButtonPressed=true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void MainMenu::Update(const sf::Time &deltaTime)
{
    if (m_isPlayButtonSelected) //check if PlayButton is selected. if it is, change the colour of the text to highlight
    {
        //when a key is selected and not yet pressed, highlight the key that is selected and de-highlight the remaining key
        m_playButton.setFillColor(sf::Color::White);
        m_instructionsButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::Black);

    }
    if (m_isInstructionsButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Black);
        m_instructionsButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Black);
    }
    else if (m_isExitButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Black);
        m_instructionsButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
    }

    if (m_isExitButtonPressed) //if exit button is pressed, have to close the window
    {
        m_context->m_states->PopAll();
    }
}

void MainMenu::Draw()
{
    
    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_instructionsButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}