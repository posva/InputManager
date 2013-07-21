//
//  Action.cpp
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#include "Action.hpp"
#include "Input.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include <iostream>


Action::Action() : m_entryPoint(NULL), m_check(false)
{
}

Action::~Action()
{
    if (m_entryPoint)
        delete m_entryPoint;
    
    clearInputs();
}

void Action::clearInputs()
{
    for (std::list<ActivatedInput*>::iterator it(m_inputs.begin()); it != m_inputs.end(); ++it)
    {
        // we remove the weak references
        (*it)->getInput()->removeAction(this);
        delete *it;
    }
    m_inputs.clear();
}

bool Action::needContinous() const
{
    for (std::list<ActivatedInput*>::const_iterator it(m_inputs.begin()); it != m_inputs.end(); ++it)
        if ((*it)->getActivationMethod() == act_keyDown || (*it)->getActivationMethod() == act_mouseDown)
            return true;
    return false;
}

void Action::addInput(Input *inp, ActivationMethod method)
{
    switch (inp->getType()) {
        case inp_keyboard:
            if (method <= act_keyBegin || method >= act_keyEnd)
            {
                std::cerr<<"Error adding input to Action, method conflits with Input type.\n";
                return;
            }
            break;
            
        case inp_mouse:
            if (method <= act_mouseBegin || method >= act_mouseEnd
                || (method == act_mouseWheel && static_cast<Mouse*>(inp)->getButton() != sf::Mouse::Middle)
                || (method == act_mouseMove && static_cast<Mouse*>(inp)->getButton() != sf::Mouse::Left))
            {
                std::cerr<<"Error adding input to Action, method conflits with Input type.\n";
                return;
            }
            break;
            
        default:
            std::cerr<<"Error adding Input to Action: input is invalid (no type).\n";
            return;
            break;
    }
    
    // allocate an ActivatedInpt
    m_inputs.push_back(new ActivatedInput(inp, method));
    inp->addAction(this);
    
}

void Action::inputCheck(Input *inp)
{
    for (std::list<ActivatedInput*>::iterator it(m_inputs.begin()); it != m_inputs.end(); ++it)
    {
        if ((*it)->getInput() == inp)
        {
            switch (inp->getType()) {
                case inp_keyboard:
                    if (((*it)->getActivationMethod() == act_keyDown && inp->isDown())
                        || ((*it)->getActivationMethod() == act_keyPress && inp->isPressed())
                        || ((*it)->getActivationMethod() == act_keyRelease && inp->isReleased()))
                        run();
                    break;
                    
                case inp_mouse:
                    if (((*it)->getActivationMethod() == act_mouseDown && inp->isDown())
                        || ((*it)->getActivationMethod() == act_mouseClick && inp->isPressed())
                        || ((*it)->getActivationMethod() == act_mouseRelease && inp->isReleased())
                        || ((*it)->getActivationMethod() == act_mouseWheel && static_cast<Mouse*>(inp)->checkWheel())
                        || ((*it)->getActivationMethod() == act_mouseMove && static_cast<Mouse*>(inp)->checkMoved()))
                        run();
                    break;
                    
                default:
                    break;
            }
            // we dont return cause we can have multiple times the same input but with different methods (ex:release, press)
            // return;
        }
    }
}
