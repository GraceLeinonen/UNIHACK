#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    
    // Create a texture object to hold PNG file
    sf::Texture texture;
    texture.loadFromFile("photo.jpg");

    // Create a sprite to display the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Desired size for all sprites
    const float desiredWidth = 600.0f;
    const float desiredHeight = 600.0f;
    
    float originalWidth = texture.getSize().x;
    float originalHeight = texture.getSize().y;

    // Calculate scale factors
    float scaleX = desiredWidth / texture.getSize().x;
    float scaleY = desiredHeight / texture.getSize().y;

    // Apply scale to sprite
    float scaleFactor = std::min(desiredWidth / originalWidth, desiredHeight / originalHeight);
    sprite.setScale(scaleFactor, scaleFactor);

    float newWidth = texture.getSize().x;
    float newHeight = texture.getSize().y;
    
    // Crop image
    sf::IntRect cropArea((newWidth/2)-350, (newHeight/2)-350, 700, 700);
    sprite.setTextureRect(cropArea); // Apply the cropping area to the sprite

    // Create a window with a title and a specified resolution
    sf::RenderWindow window(sf::VideoMode(960, 540), "ImageTest");

    // Create a rectangle that represents a selectable object
    sf::RectangleShape rectangle(sf::Vector2f(60.f, 60.f)); 
    rectangle.setFillColor(sf::Color::Blue);

    sprite.setPosition(330.f, 120.f); // Center of the window
    rectangle.setPosition(133.5f, 100.f); 

    // Main loop to keep the window open
    while (window.isOpen()) {
        sf::Event event;
        // Poll events (e.g., keyboard or mouse input)
        while (window.pollEvent(event)) {
            // Close window if "close event" is triggered
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // Clear the window
        window.clear(sf::Color::Black); // Fill with black color

        // Draw the content
        window.draw(rectangle);
        window.draw(sprite);

        // Display the content
        window.display();
        



    }

    return 0;
}