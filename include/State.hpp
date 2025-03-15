#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Engine
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};

        virtual void Init() = 0;
        virtual void ProcessInput() = 0;
        virtual void Update(const sf::Time& deltaTime) = 0; 
        virtual void Draw() = 0;
    };
}

