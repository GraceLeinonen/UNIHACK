//include the hpp files of all states

#include "House.hpp"
#include <SFML/Window/Event.hpp>

House::House(std::shared_ptr<Context> &context)
{
    m_context = context;
    m_isButtonSelected = 0;
    m_isButtonPressed = 0;

    // indexes 0, 1, 2, 3 are for background and buttons
    imageIndex1 = 4;
    imageIndex2 = 5;
}

House::~House() {

}

void House::populateImagesForHouse(ImageStore imageStore, std::string habitName) {
    
    // create habit map
    imageStore.readImageDirectory("assets/textures");
    auto habitMap = imageStore.getHabitMap();

    for (const auto& [habit, paths] : habitMap) {
        if (habit.getName() == habitName) { // Check for specific habit name
            for (const auto& path : paths) {
                imageFiles.push_back(path.string()); // Extract and store file names
            }
        }
    }

    // Sort imageFiles in alphabetical order
    std::sort(imageFiles.begin(), imageFiles.end());
}

void House::Init() {

    //! NEED TO FIX THIS!!!!!!!!!!
    populateImagesForHouse(imageStore, "brushTeeth"); //! NOTE BRUSHTEETH HARDCODED IN - WILL CHANGE HOUSES CLASS TO IT CONTAINS HABITS MEMBER OR DO A SUBCLASS

    // first four files in imageFiles are background and buttons
    //*1 load texture to background
    background.loadFromFile(imageFiles[0]);
    background_object = sf::Sprite(background);

    //*2 set up buttons and their location 
    previousImage.loadFromFile(imageFiles[1]);
    previousImage_object = sf::Sprite(previousImage);
    previousImage_object.setPosition((480.f - previousImage.getSize().x) - 20.f, 400.f);

    nextImage.loadFromFile(imageFiles[2]);
    nextImage_object = sf::Sprite(nextImage);
    nextImage_object.setPosition(500.f, 400.f);

    toVillage.loadFromFile(imageFiles[3]);
    toVillage_object = sf::Sprite(toVillage);
    toVillage_object.setPosition(480.f - (previousImage.getSize().x)/2, 460.f);

    //*3 load and position images
    image1.loadFromFile(imageFiles[4]);
    image1.cropToSquare();
    image1.resizeTo(240.0f);
    image1.setPosition(230.0f, 150.0f);

    image2.loadFromFile(imageFiles[5]);
    image2.cropToSquare();
    image2.resizeTo(240.0f);
    image2.setPosition(490.0f, 150.0f);

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
            if (previousImage_object.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isButtonSelected = 1;
            }

            else if (nextImage_object.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isButtonSelected = 2;
            }

            else if (toVillage_object.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_isButtonSelected = 3;
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

            if (m_isButtonSelected == 3) {
                m_isButtonPressed = 3;
            }

            break;

        }
    }
}

void House::Update(const sf::Time& deltaTime) {

    //! THIS NEEDS FIXING
    /*
    if (m_isButtonPressed == 1) {

        if (imageIndex2 < imageFiles.size())
        {
            imageIndex1++;
            imageIndex2++;

            image1.loadFromFile(imageFiles[imageIndex1]);
            image1.cropToSquare();
            image1.resizeTo(240.0f);
            image1.setPosition(230.0f, 150.0f);

            image2.loadFromFile(imageFiles[imageIndex2]);
            image2.cropToSquare();
            image2.resizeTo(240.0f);
            image2.setPosition(490.0f, 150.0f);

        }
        
    }

    if (m_isButtonPressed == 2) {

        if (imageIndex2 > 4)
        {
            imageIndex1--;
            imageIndex2--;

            image1.loadFromFile(imageFiles[imageIndex1]);
            image1.cropToSquare();
            image1.resizeTo(240.0f);
            image1.setPosition(230.0f, 150.0f);

            image2.loadFromFile(imageFiles[imageIndex2]);
            image2.cropToSquare();
            image2.resizeTo(240.0f);
            image2.setPosition(490.0f, 150.0f);
        }   
    }
    */
    if (m_isButtonPressed == 3) {

        //! GO TO VILLAGE
    }

}

void House::Draw() {

    m_context->m_window->clear();
    m_context->m_window->draw(background_object);
    m_context->m_window->draw(previousImage_object);
    m_context->m_window->draw(nextImage_object);
    m_context->m_window->draw(toVillage_object);
    image1.draw(m_context->m_window);
    image2.draw(m_context->m_window);
    m_context->m_window->display();

}