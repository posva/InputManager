//
//  Keyboard.h
//  InputManager
//
//  Created by Edu San Martin Morote on 17/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#pragma once

#include "Input.hpp"
#include <string>

typedef sf::Keyboard::Key KeyboardKey;

class Keyboard: public Input {
private:
    static const std::string keyStringMapping[];
protected:
    KeyboardKey m_key;

public:

    Keyboard(KeyboardKey key);
    Keyboard(const std::string& key);
    
    inline KeyboardKey getKey() const { return m_key; }

    static KeyboardKey getKey(const std::string& key);
    static inline const std::string& getString(KeyboardKey key)
    {
        return keyStringMapping[(key>=sf::Keyboard::Key::KeyCount?sf::Keyboard::Key::Unknown:key)-sf::Keyboard::Key::A];
    }

};
