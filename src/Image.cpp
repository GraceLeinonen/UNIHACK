#include "Image.hpp"

Image::Image() {}

void Image::loadFromFile(const std::string& filePath) {
    
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);

}

void Image::cropToSquare() {
     // Get original image dimensions
     float originalWidth = texture.getSize().x;
     float originalHeight = texture.getSize().y;
 
     // Determine the size of the square (smallest dimension of the image)
     float squareSize = std::min(originalWidth, originalHeight);
 
     // Calculate the top-left corner of the square crop area to center it
     float cropX = (originalWidth - squareSize) / 2.0f;
     float cropY = (originalHeight - squareSize) / 2.0f;
 
     // Define the cropping rectangle (a perfect square)
     sf::IntRect cropArea(cropX, cropY, squareSize, squareSize);
     sprite.setTextureRect(cropArea);
}

void Image::resizeTo(float desiredSize) {

    sf::IntRect cropArea = sprite.getTextureRect(); 
    float squareSize = cropArea.width;
    float scaleFactor = desiredSize / squareSize;
    sprite.setScale(scaleFactor, scaleFactor);
}

void Image::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Image::draw(std::unique_ptr<sf::RenderWindow> &window) {
    window->draw(sprite);
}