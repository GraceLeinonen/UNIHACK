#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class Image {

    public:
    Image();
    void loadFromFile(const std::string& filePath);
    void cropToSquare();
    void resizeTo(float desiredSize);
    void setPosition(float x, float y);
    void draw(std::unique_ptr<sf::RenderWindow> &window);

    private:
    sf::Texture texture;
    sf::Sprite sprite;

};