//
//  ActivatedInput.h
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#pragma once

class Input;

enum ActivationMethod {
    act_keyBegin,
    act_keyDown,
    act_keyPress,
    act_keyRelease,
    act_keyEnd,
    act_mouseBegin,
    act_mouseMouve,
    act_mouseClick,
    act_mouseDown,
    act_mouseRelease,
    act_mouseEnd
    };

class ActivatedInput {
    Input* m_inp;
    ActivationMethod m_actMethod;
    
public:
    ActivatedInput(Input* inp, ActivationMethod method) : m_inp(inp), m_actMethod(method)
    {
    }
    
    inline Input* getInput() { return m_inp; }
    inline ActivationMethod getActivationMethod() const { return m_actMethod; }
    inline void setActivationMethod(ActivationMethod method) { m_actMethod = method; }
};
