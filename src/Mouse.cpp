//
//  Mouse.cpp
//  InputManager
//
//  Created by Edu San Martin Morote on 20/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#include "Mouse.hpp"

const std::string Mouse::mouseStringMapping[] = {
    "Left",
    "Right",
    "Middle",
    "X1",
    "X2",
    ""
};

Mouse::Mouse(MouseButton but): Input(inp_mouse), m_but(but), m_mouseWheel(false), m_mouseMoved(false)
{
}

Mouse::Mouse(const std::string& but): Input(inp_mouse), m_but(Mouse::getButton(but))
{
}

MouseButton Mouse::getButton(const std::string& but)
{
    if (but.size() <= 0 || but[0] == 'L' || but[0] == 'l')
        return sf::Mouse::Left;
    else if (but[0] == 'R' || but[0] == 'r')
        return sf::Mouse::Right;
    else if (but[0] == 'M' || but[0] == 'm')
        return sf::Mouse::Middle;
    else if (but[0] == 'X')
        return (but.size() > 1 && but[1] == '2')?sf::Mouse::XButton2:sf::Mouse::XButton1;
    else
        return sf::Mouse::Left;

}


