//include the hpp files of all states

#include "House.hpp"
#include <SFML/Window/Event.hpp>

#include <iostream>

House::House(std::shared_ptr<Context> &context)
{
    m_context = context;

    m_isButtonSelected = 0;
    m_isButtonPressed = 0;

}

House::~House() {

}

void House::Init() {

    //*1 load texture to background
    background.loadFromFile("assets/textures/houseBackground.png");
    background_object = sf::Sprite(background);

    //*2 set up buttons and their location
    addImageButton1.loadFromFile("assets/textures/addImageButton.png");
    addImageButton1_object = sf::Sprite(addImageButton1);

    addImageButton2.loadFromFile("assets/textures/addImageButton.png");
    addImageButton2_object = sf::Sprite(addImageButton2);

    addImageButton1_object.setPosition(240.f, 390.f);
    addImageButton1_object.setScale(4.286, 4.286);
    addImageButton2_object.setPosition(480.f, 390.f);
    addImageButton2_object.setScale(4.286, 4.286);

    //*3 load and position images
    image1.loadFromFile("assets/textures/image1.jpg");
    image1.cropToSquare();
    image1.resizeTo(240.0f);
    image1.setPosition(240.0f, 150.0f);

    image2.loadFromFile("assets/textures/image2.jpg");
    image2.cropToSquare();
    image2.resizeTo(240.0f);
    image2.setPosition(480.0f, 150.0f);

    // Iterate through the directory
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        // Check if the entry is a file
        if (std::filesystem::is_regular_file(entry.status())) {
            // Extract the file name
            std::string fileName = entry.path().filename().string();

            // Check if the file matches the target name
            if (fileName == targetFileName) {
                matchingFiles.push_back(entry.path());
            }
        }
    }

}

void House::ProcessInput() {

    sf::Event event;

    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            m_context->m_states->PopAll();
        }
        else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*(m_context->m_window)); // get position of mouse relative to window

            // check if mouse is on add image buttons
            if (addImageButton1_object.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isButtonSelected = 1;
            }

            else if (addImageButton2_object.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isButtonSelected = 2;
            }

            else {
                m_isButtonSelected = 0;
            }
        }

        else if (event.type == sf::Event::MouseButtonPressed) {

            // on button and mouse pressed
            if (m_isButtonSelected == 1) {
                m_isButtonPressed = 1;
            }

            if (m_isButtonSelected == 2) {
                m_isButtonPressed = 2;
            }

            break;

        }
    }
}

void House::Update(const sf::Time& deltaTime) {

    if (m_isButtonPressed == 1) {
        
    }

    if (m_isButtonPressed == 2) {
    
    }

}

void House::Draw() {

    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(addImageButton1_object);
    m_context->m_window->draw(addImageButton2_object);
    image1.draw(m_context->m_window);
    image2.draw(m_context->m_window);
    m_context->m_window->display();

}