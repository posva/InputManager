//
//  InputManager.h
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#pragma once

#include "Keyboard.h"
#include "Action.h"
#include <vector>
#include <map>

class InputManager {
    std::vector<Input*> m_inputs;
    std::map<std::string, Action*> m_actions;
    
public:
    InputManager();
    ~InputManager();
    
    Action* addAction(const std::string& name);
    
    // if the name already exists the return value differs from action
    Action* addAction(Action* action, const std::string& name);
    
    void addKeyToAction(Action* action, KeyboardKey key, ActivationMethod method);
    
    void update(const sf::Event& event);
};