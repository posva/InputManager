//
//  InputManager.cpp
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#include "InputManager.hpp"
#include <cassert>
#include <iostream>

static const unsigned int mouseIndex(sf::Keyboard::KeyCount);
static const unsigned int joystickIndex[sf::Joystick::Count] = {
    (mouseIndex+sf::Mouse::ButtonCount),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)+1),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*2+1),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*3+1),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*4+1),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*5+1),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*6+1),
    (mouseIndex+sf::Mouse::ButtonCount+(sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*7+1)
};

InputManager::InputManager() : m_inputs(sf::Keyboard::KeyCount + sf::Mouse::ButtonCount + (sf::Joystick::ButtonCount+sf::Joystick::AxisCount)*sf::Joystick::Count - 2), m_mouseWheelDelta(0)
{
    for (unsigned int i = 0; i < m_inputs.size(); ++i)
    {
        m_inputs[i] = NULL;

        if (i < sf::Keyboard::KeyCount)
        {
            m_inputs[i] = new Keyboard(static_cast<KeyboardKey>(i));
            assert(m_inputs[i]);
        }
        else if (i < mouseIndex+sf::Mouse::ButtonCount)
        {
            m_inputs[i] = new Mouse(static_cast<MouseButton>(i-mouseIndex));
            assert(m_inputs[i]);
        }
    }


}

InputManager::~InputManager()
{
    for (unsigned int i = 0; i < m_inputs.size(); ++i)
        if (m_inputs[i]) delete m_inputs[i];
    m_inputs.clear();

    for (std::map<std::string,Action*>::iterator it = m_actions.begin(); it != m_actions.end(); ++it)
        delete it->second;
    m_actions.clear();
}

void InputManager::update(const sf::Event &event)
{
    // Check the events
    switch (event.type) {
        case sf::Event::KeyPressed:
            m_inputs[event.key.code-sf::Keyboard::A]->setPressed();
            break;
        case sf::Event::KeyReleased:
            m_inputs[event.key.code-sf::Keyboard::A]->setReleased();
            break;

        case sf::Event::MouseButtonPressed:
            m_inputs[mouseIndex+event.mouseButton.button]->setPressed();
            break;

        case sf::Event::MouseButtonReleased:
            m_inputs[mouseIndex+event.mouseButton.button]->setReleased();
            break;
        case sf::Event::MouseWheelMoved:
            m_mouseWheelDelta = event.mouseWheel.delta;
            // we simulate
            static_cast<Mouse*>(m_inputs[mouseIndex+sf::Mouse::Middle])->mouseWheelEvent(true);
            static_cast<Mouse*>(m_inputs[mouseIndex+sf::Mouse::Middle])->mouseWheelEvent(false);
            break;
        case sf::Event::MouseMoved:
            m_mousePosition.x = event.mouseMove.x;
            m_mousePosition.y = event.mouseMove.y;
            static_cast<Mouse*>(m_inputs[mouseIndex+sf::Mouse::Left])->mouseMovedEvent(true);
            static_cast<Mouse*>(m_inputs[mouseIndex+sf::Mouse::Left])->mouseMovedEvent(false);
            break;

        default:
            break;
    }


}

void InputManager::updateDowns()
{
    m_mouseWheelDelta = 0;
    
    // Reset the check for every Action
    for (std::map<std::string,Action*>::iterator it = m_actions.begin(); it != m_actions.end(); ++it)
        it->second->resetCheck();

    //The continous checks
    for (unsigned int i(0); i < mouseIndex+sf::Mouse::ButtonCount; ++i) // TODO change by size()
    {
        if (m_inputs[i]->isContinous())
        {
            if (i<mouseIndex) //keyboard
                m_inputs[i]->update(sf::Keyboard::isKeyPressed(static_cast<Keyboard*>(m_inputs[i])->getKey()));
            else if (i<joystickIndex[0]) // it's a mouse
                m_inputs[i]->update(sf::Mouse::isButtonPressed(static_cast<Mouse*>(m_inputs[i])->getButton()));

        }
    }
}

Action* InputManager::getAction(const std::string &name)
{
    if (m_actions.find(name) == m_actions.end())
        m_actions[name] = new Action();

    return m_actions[name];
}

void InputManager::addKeyToAction(Action *action, KeyboardKey key, ActivationMethod method)
{
    // this fucntions verify everything which is needed
    action->addInput(m_inputs[key-sf::Keyboard::A], method);
}

void InputManager::addKeyToAction(const std::string& action, KeyboardKey key, ActivationMethod method)
{
    getAction(action)->addInput(m_inputs[key-sf::Keyboard::A], method);
}

void InputManager::addMouseToAction(Action *action, MouseButton but, ActivationMethod method)
{
    action->addInput(m_inputs[mouseIndex+but], method);
}

void InputManager::addMouseToAction(const std::string& action, MouseButton but, ActivationMethod method)
{
    getAction(action)->addInput(m_inputs[mouseIndex+but], method);
}
