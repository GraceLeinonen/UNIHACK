#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class SignIn : public Engine::State
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
    sf::Texture texture1, texture2, texture3, texture4;
    sf::Sprite signin_grace;
    TextButtonStates signin_graceStates;
    sf::Sprite signin_michelle;
    TextButtonStates signin_michelleStates;
    sf::Sprite signin_kate;
    TextButtonStates signin_kateStates;
    sf::Sprite signin_noah;
    TextButtonStates signin_noahStates;

public:
    SignIn(std::shared_ptr<Context> &context);
    ~SignIn();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

    bool isMouseOverSprite(std::shared_ptr<Context> &m_context, sf::Sprite sprite);
    void setTexture_addPosition(sf::Sprite &sprite, sf::Texture &texture, std::string file_path,float x_pos, float y_pos);


};