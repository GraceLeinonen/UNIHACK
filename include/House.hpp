#pragma once

#include <memory>
#include <vector>
#include <filesystem>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Image.hpp"
#include "ImageStore.hpp"
#include "Habits.hpp"

class House : public Engine::State {

    private:

    // habit
    Habits habit;

    std::shared_ptr<Context> m_context;

    // buttons
    sf::Texture previousImage;
    sf::Sprite previousImage_object;

    sf::Texture nextImage;
    sf::Sprite nextImage_object;

    sf::Texture toVillage;
    sf::Sprite toVillage_object;

    //add background image
    sf::Texture background;
    sf::Sprite background_object;

    //create images
    Image image1;
    Image image2;   
    
    int imageIndex1;
    int imageIndex2;

    // buttons selected and pressed
    int m_isButtonSelected;
    int m_isButtonPressed;

    // vector for photos
    ImageStore imageStore;
    std::vector<std::string> imageFiles;

    public:
    House(std::shared_ptr<Context> &context);
    ~House();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

    void populateImagesForHouse(ImageStore imageStore, std::string habitName);
};