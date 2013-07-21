//
//  Keyboard.cpp
//  InputManager
//
//  Created by Edu San Martin Morote on 17/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#include "Keyboard.hpp"

const std::string Keyboard::keyStringMapping[] = {
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "Num0",
    "Num1",
    "Num2",
    "Num3",
    "Num4",
    "Num5",
    "Num6",
    "Num7",
    "Num8",
    "Num9",
    "Escape",
    "LControl",
    "LShift",
    "LAlt",
    "LSystem",
    "RControl",
    "RShift",
    "RAlt",
    "RSystem",
    "Menu",
    "LBracket",
    "RBracket",
    "SemiColon",
    "Comma",
    "Period",
    "Quote",
    "Slash",
    "BackSlash",
    "Tilde",
    "Equal",
    "Dash",
    "Space",
    "Return",
    "BackSpace",
    "Tab",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Insert",
    "Delete",
    "Add",
    "Subtract",
    "Multiply",
    "Divide",
    "Left",
    "Right",
    "Up",
    "Down",
    "Numpad0",
    "Numpad1",
    "Numpad2",
    "Numpad3",
    "Numpad4",
    "Numpad5",
    "Numpad6",
    "Numpad7",
    "Numpad8",
    "Numpad9",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "Pause",
    ""
};



Keyboard::Keyboard(KeyboardKey key) : Input(inp_keyboard), m_key(key)
{

}


Keyboard::Keyboard(const std::string& key) : Keyboard(sf::Keyboard::Key::Unknown)
{
    m_key = Keyboard::getKey(key);
}

KeyboardKey Keyboard::getKey(const std::string& key)
{
    if (key.size() == 1) // A - Z
    {
        if (key[0] >= 'A' && key[0] <= 'Z')
            return static_cast<KeyboardKey>(key[0]-'A'+static_cast<int>(sf::Keyboard::Key::A));
        else if (key[0] >= 'a' && key[0] <= 'z')
            return static_cast<KeyboardKey>(key[0]-'a'+static_cast<int>(sf::Keyboard::Key::A));
    }
    else
    {
        if (key.compare("Num0") == 0)
            return sf::Keyboard::Key::Num0;
        else if(key.compare("Num1") == 0)
            return sf::Keyboard::Key::Num1;
        else if(key.compare("Num2") == 0)
            return sf::Keyboard::Key::Num2;
        else if(key.compare("Num3") == 0)
            return sf::Keyboard::Key::Num3;
        else if(key.compare("Num4") == 0)
            return sf::Keyboard::Key::Num4;
        else if(key.compare("Num5") == 0)
            return sf::Keyboard::Key::Num5;
        else if(key.compare("Num6") == 0)
            return sf::Keyboard::Key::Num6;
        else if(key.compare("Num7") == 0)
            return sf::Keyboard::Key::Num7;
        else if(key.compare("Num8") == 0)
            return sf::Keyboard::Key::Num8;
        else if(key.compare("Num9") == 0)
            return sf::Keyboard::Key::Num9;
        else if(key.compare("Escape") == 0)
            return sf::Keyboard::Key::Escape;
        else if(key.compare("LControl") == 0)
            return sf::Keyboard::Key::LControl;
        else if(key.compare("LShift") == 0)
            return sf::Keyboard::Key::LShift;
        else if(key.compare("LAlt") == 0)
            return sf::Keyboard::Key::LAlt;
        else if(key.compare("LSystem") == 0)
            return sf::Keyboard::Key::LSystem;
        else if(key.compare("RControl") == 0)
            return sf::Keyboard::Key::RControl;
        else if(key.compare("RShift") == 0)
            return sf::Keyboard::Key::RShift;
        else if(key.compare("RAlt") == 0)
            return sf::Keyboard::Key::RAlt;
        else if(key.compare("RSystem") == 0)
            return sf::Keyboard::Key::RSystem;
        else if(key.compare("Menu") == 0)
            return sf::Keyboard::Key::Menu;
        else if(key.compare("LBracket") == 0)
            return sf::Keyboard::Key::LBracket;
        else if(key.compare("RBracket") == 0)
            return sf::Keyboard::Key::RBracket;
        else if(key.compare("SemiColon") == 0)
            return sf::Keyboard::Key::SemiColon;
        else if(key.compare("Comma") == 0)
            return sf::Keyboard::Key::Comma;
        else if(key.compare("Period") == 0)
            return sf::Keyboard::Key::Period;
        else if(key.compare("Quote") == 0)
            return sf::Keyboard::Key::Quote;
        else if(key.compare("Slash") == 0)
            return sf::Keyboard::Key::Slash;
        else if(key.compare("BackSlash") == 0)
            return sf::Keyboard::Key::BackSlash;
        else if(key.compare("Tilde") == 0)
            return sf::Keyboard::Key::Tilde;
        else if(key.compare("Equal") == 0)
            return sf::Keyboard::Key::Equal;
        else if(key.compare("Dash") == 0)
            return sf::Keyboard::Key::Dash;
        else if(key.compare("Space") == 0)
            return sf::Keyboard::Key::Space;
        else if(key.compare("Return") == 0)
            return sf::Keyboard::Key::Return;
        else if(key.compare("BackSpace") == 0)
            return sf::Keyboard::Key::BackSpace;
        else if(key.compare("Tab") == 0)
            return sf::Keyboard::Key::Tab;
        else if(key.compare("PageUp") == 0)
            return sf::Keyboard::Key::PageUp;
        else if(key.compare("PageDown") == 0)
            return sf::Keyboard::Key::PageDown;
        else if(key.compare("End") == 0)
            return sf::Keyboard::Key::End;
        else if(key.compare("Home") == 0)
            return sf::Keyboard::Key::Home;
        else if(key.compare("Insert") == 0)
            return sf::Keyboard::Key::Insert;
        else if(key.compare("Delete") == 0)
            return sf::Keyboard::Key::Delete;
        else if(key.compare("Add") == 0)
            return sf::Keyboard::Key::Add;
        else if(key.compare("Subtract") == 0)
            return sf::Keyboard::Key::Subtract;
        else if(key.compare("Multiply") == 0)
            return sf::Keyboard::Key::Multiply;
        else if(key.compare("Divide") == 0)
            return sf::Keyboard::Key::Divide;
        else if(key.compare("Left") == 0)
            return sf::Keyboard::Key::Left;
        else if(key.compare("Right") == 0)
            return sf::Keyboard::Key::Right;
        else if(key.compare("Up") == 0)
            return sf::Keyboard::Key::Up;
        else if(key.compare("Down") == 0)
            return sf::Keyboard::Key::Down;
        else if(key.compare("Numpad0") == 0)
            return sf::Keyboard::Key::Numpad0;
        else if(key.compare("Numpad1") == 0)
            return sf::Keyboard::Key::Numpad1;
        else if(key.compare("Numpad2") == 0)
            return sf::Keyboard::Key::Numpad2;
        else if(key.compare("Numpad3") == 0)
            return sf::Keyboard::Key::Numpad3;
        else if(key.compare("Numpad4") == 0)
            return sf::Keyboard::Key::Numpad4;
        else if(key.compare("Numpad5") == 0)
            return sf::Keyboard::Key::Numpad5;
        else if(key.compare("Numpad6") == 0)
            return sf::Keyboard::Key::Numpad6;
        else if(key.compare("Numpad7") == 0)
            return sf::Keyboard::Key::Numpad7;
        else if(key.compare("Numpad8") == 0)
            return sf::Keyboard::Key::Numpad8;
        else if(key.compare("Numpad9") == 0)
            return sf::Keyboard::Key::Numpad9;
        else if(key.compare("F1") == 0)
            return sf::Keyboard::Key::F1;
        else if(key.compare("F2") == 0)
            return sf::Keyboard::Key::F2;
        else if(key.compare("F3") == 0)
            return sf::Keyboard::Key::F3;
        else if(key.compare("F4") == 0)
            return sf::Keyboard::Key::F4;
        else if(key.compare("F5") == 0)
            return sf::Keyboard::Key::F5;
        else if(key.compare("F6") == 0)
            return sf::Keyboard::Key::F6;
        else if(key.compare("F7") == 0)
            return sf::Keyboard::Key::F7;
        else if(key.compare("F8") == 0)
            return sf::Keyboard::Key::F8;
        else if(key.compare("F9") == 0)
            return sf::Keyboard::Key::F9;
        else if(key.compare("F10") == 0)
            return sf::Keyboard::Key::F10;
        else if(key.compare("F11") == 0)
            return sf::Keyboard::Key::F11;
        else if(key.compare("F12") == 0)
            return sf::Keyboard::Key::F12;
        else if(key.compare("F13") == 0)
            return sf::Keyboard::Key::F13;
        else if(key.compare("F14") == 0)
            return sf::Keyboard::Key::F14;
        else if(key.compare("F15") == 0)
            return sf::Keyboard::Key::F15;
        else if(key.compare("Pause") == 0)
            return sf::Keyboard::Key::Pause;
        // TODO optimise common begining strings?
    }

    return sf::Keyboard::Key::Unknown;
}

