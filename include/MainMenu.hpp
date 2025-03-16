#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Platform.hpp"

//Define other useful simple structures for each state
struct TextButtonStates
{
    bool isSelected;
    bool isPressed;
};

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    sf::Text gameTitle;
    sf::Text signInButton;
    sf::Text instructionsButton;
    sf::Text exitButton;
    TextButtonStates signInButtonStates;
    TextButtonStates instructionsButtonStates;
    TextButtonStates exitButtonStates;

    //add background image
    sf::Texture background;
    sf::Sprite background_object;


public:
    MainMenu(std::shared_ptr<Context> &context);
    ~MainMenu();

    
    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

    //other functions
    void display_instructions(AssetID font_name_enum, sf::Text& text, std::string title, int fontSize, float x_pos, float y_pos);
    bool isMouseOverText(sf::Text text);
    bool isMouseOverSprite(sf::Sprite sprite);

};