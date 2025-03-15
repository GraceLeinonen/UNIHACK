#pragma once

#include <memory> //because we use unique pointers

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.hpp"
#include "StateMan.hpp"


enum AssetID 
{
    MAIN_FONT = 0, //we want the implicit converstion of AssetID to int

};

struct Context //pass the Context structure to each State so each state can handle asset_manager, state_manager and render_window
{
    //the structure will need unique pointers to store the objects
    std::unique_ptr<Engine::AssetMan> m_assets;
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context() 
    {
        //initialise all unique pointers
        m_assets = std::make_unique<Engine::AssetMan>(); 
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
public:
    Game();
    ~Game();

    void Run();

private:
    std::shared_ptr<Context> m_context; 
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); // the time that each frame takes. a constant time object called TIME_PER_FRAME; equal to 1/60 seconds per frame (the program has 60 frames per second)

};