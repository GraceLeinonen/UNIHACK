#pragma once

#include <stack>
#include <memory> //to use unique pointers

#include <State.hpp>

namespace Engine 
{
    class StateMan
    {
    
    private:
        std::stack< std::unique_ptr<State> > m_stateStack; // a stack of unique pointers pointingn to States, called "m_stateStack" -> "managing state stack"
        std::unique_ptr<State> m_newState;//na unique pointer to store the new state that we want to add to the stack.
        
        bool m_add; //true: give an order to add a new state
        bool m_replace;//true: give an order to replace the current state 
        bool m_remove;// true: give an order to remove the current state
        bool m_removeAll; //true: given an order to remove all states in m_stateStack
    
    public:
        StateMan();
        ~StateMan();

        //*1-add a new state to the stack of states.
        void Add(std::unique_ptr<State> toAdd, bool replace = false);//take two parameteres, pointer to state object being added, the second is a boolean to control whether we want to simply add a new state or do we want to replace the current one with the new one. default; false, since most of the time we just push a new state to the stack
        
        //*2-remove the current state from the state stack
        void PopCurrent();

        //*3-Pop all the states in the stack
        void PopAll();

        //*4-actual modification in the class only happens in ProcessStateChange.
        void ProcessStateChange();
        
        //*5-a method returns a unique pointer to current state object by reference 
        std::unique_ptr<State> &GetCurrent();
        
        //*6-a method to check whether the state stack is empty
        bool IsEmpty() const;

    
    };
}