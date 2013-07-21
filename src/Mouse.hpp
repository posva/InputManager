//
//  Mouse.h
//  InputManager
//
//  Created by Edu San Martin Morote on 20/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#pragma once

#include "Input.hpp"

typedef sf::Mouse::Button MouseButton;

class Mouse: public Input {
private:
    static const std::string mouseStringMapping[];
protected:
    MouseButton m_but;
    
public:
    Mouse(MouseButton but);
    Mouse(const std::string& but);
    
    inline MouseButton getButton() const { return m_but; }
    
    static MouseButton getButton(const std::string& but);
    static inline const std::string& getString(MouseButton but)
    {
        return mouseStringMapping[(but>=sf::Mouse::ButtonCount?sf::Mouse::Left:but)];
    }
    
};