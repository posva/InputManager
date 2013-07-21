#pragma once

#include <SFML/Window.hpp>
#include <list>

enum inputType {
    inp_keyboard,
    inp_mouse,
    inp_joystick
};

class Action;

class Input {
protected:
    inputType m_type;
    bool m_pressed, m_released, m_down;
    std::list<Action*> m_actions;
    bool m_continousCheck; // this is set to true when this is linked to an action that have a "Down" method
    
    void updateContinousCheck();
    
public:
    
    Input(inputType type);
    
    virtual ~Input();
    
    virtual void update(bool isPressed);
    virtual void setPressed();
    virtual void setReleased();
    
    inline bool isDown() const { return m_down; }
    inline bool isPressed() const { return m_pressed; }
    inline bool isReleased() const { return m_released; }
    
    void addAction(Action* action);
    void removeAction(Action* action);
    
    inline inputType getType() const { return m_type; }
    inline bool isContinous() const { return m_continousCheck; }
    
    void checkActions();
    
};