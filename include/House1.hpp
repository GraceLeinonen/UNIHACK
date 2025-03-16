#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Platform.hpp"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    sf::Texture texture1, texture2, texture3;
    sf::Sprite signInButton;
    sf::Sprite instructionsButton;
    sf::Sprite exitButton;

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

    bool isMouseOverSprite(std::shared_ptr<Context> &m_context, sf::Sprite sprite);
    void setTexture_addPosition(sf::Sprite &sprite, sf::Texture &texture, std::string file_path,float x_pos, float y_pos);

};