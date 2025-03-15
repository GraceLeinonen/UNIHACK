#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"

class House : public Engine::State {

    private:
    std::shared_ptr<Context> m_context;

    public:

    House(std::shared_ptr<Context> &context);
    ~House();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    
};
