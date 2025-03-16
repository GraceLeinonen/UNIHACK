#include "StateMan.hpp"
#include <iostream>

Engine::StateMan::StateMan() 
{
    m_add=false;
    m_replace=false;
    m_removeAll=false;
    m_remove=false;

}

Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace) 
//*parameter: a unique pointer to the State that we want to add to the Stack
//*replace: true: give an order to replace the current state 
{
    m_add = true;
    m_newState = std::move(toAdd); //store the state being added to m_newState (use std::momve to transfer ownership)
    m_replace = replace;
}

void Engine::StateMan::PopCurrent()
{
    m_remove = true;
}

void Engine::StateMan::PopAll()
{
    m_removeAll = true;
    m_remove = false;
}

void Engine::StateMan::ProcessStateChange()
{
    //*1- Process remove all and remove state change 
    if (m_removeAll)
    {
        while (!m_stateStack.empty()) //if m_stateStack is not empty, just pop
        {
            m_stateStack.pop();
        }
        m_removeAll = false;
    }
    else if (m_remove && (!m_stateStack.empty()))//to remove a state from the stack, but need to make sure the stateStack has a state to remove
    {
        m_stateStack.pop(); //popping out the top state

        if (!m_stateStack.empty())
        {
            m_stateStack.top()->Start();//call resume method on the top state
        }

        m_remove = false;//change to false, no longer have the order to remove state. if not it will keep removing all states from the stack
    }
    //*2-process add a new state
    if (m_add)
    {
        if (m_replace && (!m_stateStack.empty()))
        {   //(!m_stateStack.empty()) to make sure there is something to pop
            //if m_replace is true, have to pop the current state before adding a new one
            m_stateStack.pop();
            m_replace = false;//set to false after their respective operations have been done
        }
        
        //after processing replace and before calling the new state, pause the current state
        if (!m_stateStack.empty()) //make sure the state is not empty after the last pop
        {
            m_stateStack.top()->Pause();
        }
        //after pausing the current state, can finally push a new state onto the stack
        m_stateStack.push(std::move(m_newState));//add new state
        m_stateStack.top()->Init();//initialise new state
        m_stateStack.top()->Start();//start the new stage
        m_add = false;//set to false after their respective operations have been done
    }
}

std::unique_ptr<Engine::State> &Engine::StateMan::GetCurrent()
{
    return m_stateStack.top();//return state at the top of stack
}

bool Engine::StateMan::IsEmpty() const
{
    return m_stateStack.empty();
}