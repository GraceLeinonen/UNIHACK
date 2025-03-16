#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class Instructions : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    sf::Text mainMenuButton;
    TextButtonStates mainMenuButtonStates;

    //add background image
    sf::Texture background;
    sf::Sprite background_object;

    //add 4 sprites for 4 players


public:
    Instructions(std::shared_ptr<Context> &context);
    ~Instructions();

    
    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

    //other functions
    void display_text(AssetID font_name_enum, sf::Text& text, std::string title, int fontSize, float x_pos, float y_pos);
    bool isMouseOverText(sf::Text text);
    bool isMouseOverSprite(sf::Sprite sprite);

};