#pragma once
#include <SFML/Graphics.hpp>

class ImageProcessor {

    public:
    ImageProcessor(const std::string& filePath);
    void cropToSquare();
    void resizeTo(float desiredSize);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);

    private:
    sf::Texture texture;
    sf::Sprite sprite;

};
