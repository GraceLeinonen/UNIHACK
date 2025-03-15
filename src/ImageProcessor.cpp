#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(const std::string& filePath) {

    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
}

void ImageProcessor::cropToSquare() {
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

void ImageProcessor::resizeTo(float desiredSize) {

    sf::IntRect cropArea = sprite.getTextureRect(); 
    float squareSize = cropArea.width;
    float scaleFactor = desiredSize / squareSize;
    sprite.setScale(scaleFactor, scaleFactor);
}

void ImageProcessor::setPosition(float x, float y) {
    sprite.setPosition(240.f, 150.f);
}

void ImageProcessor::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}