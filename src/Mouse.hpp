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
    bool m_mouseWheel, m_mouseMoved;
    
public:
    Mouse(MouseButton but);
    Mouse(const std::string& but);
    
    inline MouseButton getButton() const { return m_but; }
    
    static MouseButton getButton(const std::string& but);
    static inline const std::string& getString(MouseButton but)
    {
        return mouseStringMapping[(but>=sf::Mouse::ButtonCount?sf::Mouse::Left:but)];
    }
    
    // manipulation of the wheel check
    inline bool checkWheel() const { return m_mouseWheel; }
    inline void mouseWheelEvent(bool c)
    {
        m_mouseWheel = c;
        if (c) checkActions();
    }
    
    // manipulation of teh moving event
    inline bool checkMoved() const { return m_mouseMoved; }
    inline void mouseMovedEvent(bool c)
    {
        m_mouseMoved = c;
        if (c) checkActions();
    }
    
};