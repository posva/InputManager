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

Mouse::Mouse(MouseButton but): Input(inp_mouse), m_but(but)
{
}

Mouse::Mouse(const std::string& but): Input(inp_mouse), m_but(Mouse::getButton(but))
{
}

MouseButton Mouse::getButton(const std::string& but)
{
    if (but.size() <= 0 || but[0] == 'L' || but[0] == 'l')
        return MouseButton::Left;
    else if (but[0] == 'R' || but[0] == 'r')
        return MouseButton::Right;
    else if (but[0] == 'M' || but[0] == 'm')
        return MouseButton::Middle;
    else if (but[0] == 'X')
        return (but.size() > 1 && but[1] == '2')?MouseButton::XButton2:MouseButton::XButton1;
    else
        return MouseButton::Left;
        
}


