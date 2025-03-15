#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    
    sf::Text m_playButton;
    sf::Text m_instructionsButton;
    sf::Text m_exitButton;

    //add background image
    sf::Texture background;
    sf::Sprite background_object;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isInstructionsButtonSelected;
    bool m_isInstructionsButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    MainMenu(std::shared_ptr<Context> &context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};