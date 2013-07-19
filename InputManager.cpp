//
//  InputManager.cpp
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#include "InputManager.h"
#include <cassert>
#include <iostream>

static const unsigned int mouseIndex(sf::Keyboard::KeyCount);
static const unsigned int joystickIndex[sf::Joystick::Count] = {
    (mouseIndex+sf::Mouse::Button::ButtonCount),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)+1),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*2+1),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*3+1),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*4+1),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*5+1),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*6+1),
    (mouseIndex+sf::Mouse::Button::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*7+1)
};

InputManager::InputManager() : m_inputs(sf::Keyboard::Key::KeyCount + sf::Mouse::Button::ButtonCount + (sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*sf::Joystick::Count - 2)
{
    for (int i = 0; i < m_inputs.size(); ++i)
    {
        m_inputs[i] = NULL;
        
        if (i < sf::Keyboard::Key::KeyCount)
        {
            m_inputs[i] = new Keyboard(static_cast<KeyboardKey>(i));
            assert(m_inputs[i]);
        }
    }
    
}

InputManager::~InputManager()
{
    for (int i = 0; i < m_inputs.size(); ++i)
        if (m_inputs[i]) delete m_inputs[i];
    m_inputs.clear();
    
    for (std::map<std::string,Action*>::iterator it = m_actions.begin(); it != m_actions.end(); ++it)
        delete it->second;
    m_actions.clear();
}

void InputManager::update(const sf::Event &event)
{
    switch (event.type) {
        case sf::Event::KeyPressed:
            m_inputs[event.key.code-sf::Keyboard::Key::A]->setPressed();
            break;
        case sf::Event::KeyReleased:
            m_inputs[event.key.code-sf::Keyboard::Key::A]->setReleased();
            break;
            
        default:
            break;
    }
    
    //The continous checks
    for (unsigned int i(0); i < sf::Keyboard::KeyCount; ++i) // TODO change by size()
    {
        if (m_inputs[i]->isContinous())
            m_inputs[i]->update(sf::Keyboard::isKeyPressed(static_cast<Keyboard*>(m_inputs[i])->getKey()));
    }
}

Action* InputManager::addAction(const std::string &name)
{
    if (m_actions.find(name) == m_actions.end())
        m_actions[name] = new Action();
    return m_actions[name];
}

Action* InputManager::addAction(Action *action, const std::string &name)
{
    if (m_actions.find(name) == m_actions.end())
        m_actions[name] = action;
    return m_actions[name];
}

void InputManager::addKeyToAction(Action *action, KeyboardKey key, ActivationMethod method)
{
    // this fucntions verify everything which is needed
    action->addInput(m_inputs[key-sf::Keyboard::Key::A], method);
}
