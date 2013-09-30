//
//  InputManager.h
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Action.hpp"
#include <vector>
#include <map>

class InputManager {
    std::vector<Input*> m_inputs;
    std::map<std::string, Action*> m_actions;
    
    int m_mouseWheelDelta;
    sf::Vector2i m_mousePosition;
    
public:
    InputManager();
    ~InputManager();
    
    void addKeyToAction(Action* action, KeyboardKey key, ActivationMethod method);
    void addKeyToAction(const std::string& action, KeyboardKey key, ActivationMethod method);
    void addMouseToAction(Action* action, MouseButton but, ActivationMethod method);
    void addMouseToAction(const std::string& action, MouseButton but, ActivationMethod method);
    
    void update(const sf::Event& event);
    //when there are no events this must be called aswell!
    void updateDowns();
    
    //Access to variables
    inline int getMouseWheelDelta() const { return m_mouseWheelDelta; }
    inline const sf::Vector2i& getMousePosition() const { return m_mousePosition; }
    
    // if the action doesn't exists yet, it's created
    Action* getAction(const std::string& action);
};