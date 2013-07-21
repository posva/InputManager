//
//  Input.cpp
//  InputManager
//
//  Created by Edu San Martin Morote on 17/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#include "Input.hpp"
#include "Action.hpp"
#include "Keyboard.hpp"
#include <iostream>

Input::Input(inputType type): m_type(type), m_pressed(false), m_released(false), m_down(false), m_continousCheck(false)
{
    
}

Input::~Input()
{
    m_actions.clear();
}

void Input::addAction(Action *action)
{
    if (std::find(m_actions.begin(), m_actions.end(), action) == m_actions.end()) // we don't want multiple same actions
    {
        m_actions.push_back(action);
        if (!m_continousCheck && action->needContinous())
            updateContinousCheck();
    }
}

void Input::updateContinousCheck()
{
    m_continousCheck = false;
    for (std::list<Action*>::iterator it(m_actions.begin()); it != m_actions.end(); ++it)
    {
        if ((*it)->needContinous())
        {
            m_continousCheck = true;
            return;
        }
        
    }
}

void Input::removeAction(Action *action)
{
    m_actions.remove(action);
    if (action->needContinous())
        updateContinousCheck();
}

void Input::update(bool isPressed)
{
    //m_pressed = !m_down && isPressed;
    //m_released = m_down && !isPressed;
    m_down = isPressed;
    for (std::list<Action*>::iterator it(m_actions.begin()); it != m_actions.end(); ++it)
        (*it)->inputCheck(this);
}

void Input::setPressed()
{
    m_pressed = true;
    m_down = true;
    m_released = false;
    for (std::list<Action*>::iterator it(m_actions.begin()); it != m_actions.end(); ++it)
        (*it)->inputCheck(this);
}

void Input::setReleased()
{
    m_pressed = false;
    m_down = false;
    m_released = true;
    for (std::list<Action*>::iterator it(m_actions.begin()); it != m_actions.end(); ++it)
        (*it)->inputCheck(this);
}
