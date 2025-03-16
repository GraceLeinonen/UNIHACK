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
    std::cout<< "Stateman.cpp: Add function is called."<<std::endl;
    m_add = true;
    std::cout<< "Stateman.cpp: m_add=true"<<std::endl;
    m_newState = std::move(toAdd); //store the state being added to m_newState (use std::momve to transfer ownership)
    std::cout<< "Stateman.cpp: m_newState = std::move(toAdd);"<<std::endl;
    m_replace = replace;
    std::cout<< "Stateman.cpp: m_replace = replace;"<<std::endl;
}

void Engine::StateMan::PopCurrent()
{
    std::cout<< "Stateman.cpp: PopCurrent() function is called."<<std::endl;
    m_remove = true;
    std::cout<< "Stateman.cpp: m_remove = true"<<std::endl;
}

void Engine::StateMan::PopAll()
{
    std::cout<< "Stateman.cpp: StateMan::PopAll() function is called."<<std::endl;
    m_removeAll = true;
    std::cout<< "Stateman.cpp: m_removeAll = true;"<<std::endl;
    m_remove = false;
    std::cout<< "Stateman.cpp: m_remove = false;"<<std::endl;
}

void Engine::StateMan::ProcessStateChange()
{
    //*1- Process remove all and remove state change 
    std::cout<<"Stateman.cpp: ProcessStateChange(): m_removeAll"<<m_removeAll<<std::endl;
    std::cout<<"Stateman.cpp: ProcessStateChange(): m_remove"<<m_remove<<std::endl;
    std::cout<<"Stateman.cpp: ProcessStateChange(): m_add"<<m_add<<std::endl;
    std::cout<<"Stateman.cpp: ProcessStateChange(): m_replace"<<m_replace<<std::endl;
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
            std::cout << "ProcessStateChange(): m_add and m_replace is true."<<std::endl;
            m_stateStack.pop();
            std::cout << "m_stateStack.pop();"<<std::endl;
            m_replace = false;//set to false after their respective operations have been done
            std::cout << "m_replace = false"<<std::endl;
        }
        
        //after processing replace and before calling the new state, pause the current state
        if (!m_stateStack.empty()) //make sure the state is not empty after the last pop
        {
            std::cout << "ProcessStateChange(): if (!m_stateStack.empty())"<<std::endl;
            m_stateStack.top()->Pause();
            std::cout << "m_stateStack.top()->Pause();"<<std::endl;
        }
        //after pausing the current state, can finally push a new state onto the stack
        m_stateStack.push(std::move(m_newState));//add new state
        std::cout << "previous: m_stateStack.push(std::move(m_newState));"<<std::endl;
        m_stateStack.top()->Init();//initialise new state
        std::cout << "Stateman.cpp: previous: m_stateStack.top()->Init();"<<std::endl;
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
