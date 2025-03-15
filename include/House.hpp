#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class House : public Engine::State {

    private:
    std::shared_ptr<Context> m_context;

    // add image buttons
    sf::Texture addImageButton1;
    sf::Sprite addImageButton1_object;

    sf::Texture addImageButton2;
    sf::Sprite addImageButton2_object;

    //add background image
    sf::Texture background;
    sf::Sprite background_object;

    // buttons selected and pressed
    int m_isButtonSelected = 0;
    int m_isButtonPressed = 0;

    public:
    House(std::shared_ptr<Context> &context);
    ~House();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    
};