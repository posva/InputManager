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
    
    int m_mouseWhellDelta;
    
public:
    InputManager();
    ~InputManager();
    
    Action* addAction(const std::string& name);
    
    // if the name already exists the return value differs from action
    Action* addAction(Action* action, const std::string& name);
    
    void addKeyToAction(Action* action, KeyboardKey key, ActivationMethod method);
    void addMouseToAction(Action* action, MouseButton but, ActivationMethod method);
    
    void update(const sf::Event& event);
    //when there are no events this must be called aswell!
    void updateDowns();
};