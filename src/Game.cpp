#include <SFML/Graphics/CircleShape.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "SignIn.hpp"
#include <iostream>

Game::Game()
{
    m_context=std::make_shared<Context>();

    sf::Vector2i windowDim = 60 * sf::Vector2i(16, 9);
    m_context->m_window->create(sf::VideoMode(windowDim.x, windowDim.y), "It Takes A Village", sf::Style::Close);
    
    //Push the first state (which is Main Menu) to the state manager
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run()
{

    sf::Clock clock; //the clock immediately after being constructed
    sf::Time timeSinceLastFrame = sf::Time::Zero; //initialise the timeSinceLastFrame first with Time::Zero
    
    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart(); //timeSinceLastFrame is our deltatime
        //clock.restart(): rest the clock back to zero and return the time elapsed since the clock started
        while (timeSinceLastFrame > TIME_PER_FRAME) //Use TIME_PER_FRAME, a constant data member of class Game
        {
            timeSinceLastFrame -= TIME_PER_FRAME;//gets back to zero if a frame has elapsed
            m_context->m_states->ProcessStateChange();
            //the process state change happens before the update cycle begins
            if (!m_context->m_states->IsEmpty())
            {
                m_context->m_states->GetCurrent()->ProcessInput();//allow the current state to handle all events like key pressed and mouse clicks
                m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);//let the current state do calculations and update itself. Update() function means: given the event in Input() function, what will happen? inputting parameter as time_per_frame
                m_context->m_states->GetCurrent()->Draw();//all the sprites and texts are drawn on the window in the current state
            }
            else
            {
                m_context->m_window->close(); //when the stack of state is empty already we just close the window
            }
        }
    }
}
