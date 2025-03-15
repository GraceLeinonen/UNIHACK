#include <SFML/Graphics.hpp>
#include <iostream>
#include "ImageProcessor.hpp"

int main() {
    
    
    sf::RenderWindow window(sf::VideoMode(960, 540), "ImageTest");

    ImageProcessor processor("photo.jpg");
    processor.cropToSquare(); // Crop image to square
    processor.resizeTo(240.0f); // Resize to a square of 240x240
    processor.setPosition(240.0f, 150.0f); // Set position of the image

    // Create a rectangle that represents a selectable object
    sf::RectangleShape rectangle(sf::Vector2f(240.f, 60.f)); 
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(240.f, 390.f);

    

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
        processor.draw(window);

        // Display the content
        window.display();
        
    }

    return 0;
}