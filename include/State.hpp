#pragma once
#include <SFML/System/Time.hpp>

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

        //these two functions are only needed for the GamePlay state. They are to be defined in the future when the Pause and Resume features in Game states are done.
        virtual void Pause(){};
        virtual void Start(){};
    };
}

//Define other useful simple structures for each state
struct TextButtonStates
{
    bool isSelected;
    bool isPressed;
};