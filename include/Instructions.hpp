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

    sf::Texture mainMenuTexture;
    sf::Sprite mainMenuButton;
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

    bool isMouseOverSprite(std::shared_ptr<Context> &m_context, sf::Sprite sprite);
    void setTexture_addPosition(sf::Sprite &sprite, sf::Texture &texture, std::string file_path,float x_pos, float y_pos);

};