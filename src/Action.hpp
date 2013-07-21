//
//  Action.h
//  InputManager
//
//  Created by Edu San Martin Morote on 19/07/13.
//  Copyright (c) 2013 Posva Games. All rights reserved.
//

#pragma once

#include <string>
#include <list>
#include "ActivatedInput.hpp"

struct ActionFunc;

class Action {
    // weak references
    std::list<ActivatedInput*> m_inputs;
    ActionFunc* m_entryPoint; ///< Abstraction of the function to run
    bool m_check; // The run function was called
public:
    
    Action();
    
    // FUNCTIONS BINDING
    // no args function
    template <typename F>
    Action(F function);
    
    // 1 arg function
    template <typename F, typename A>
    Action(F function, A argument);
    
    // 1 instance function
    template <typename C>
    Action(void(C::*function)(), C* object);
    
    inline void run();
    
    // no args function
    template <typename F>
    void bind(F function);
    
    // 1 arg function
    template <typename F, typename A>
    void bind(F function, A argument);
    
    // 1 instance function
    template <typename C>
    void bind(void(C::*function)(), C* object);
    
    // ACTIVATION METHODS
    
    void addInput(Input* inp, ActivationMethod method);
    
    void clearInputs();
    
    bool needContinous() const;
    
    // this function is called by an Input when the action may be activated. Is up to the Action itself to call the run() method if it's necessary
    void inputCheck(Input* inp);
    
    inline bool check() const { return m_check; }
    inline void resetCheck() { m_check = false; }

    
    ~Action();

};



// Base class for abstract Action functions
struct ActionFunc
{
    virtual ~ActionFunc() {}
    virtual void run() = 0;
};

// Specialization using a functor (including free functions) with no argument
template <typename T>
struct ActionFunctor : ActionFunc
{
    ActionFunctor(T functor) : m_functor(functor) {}
    virtual void run() {m_functor();}
    T m_functor;
};

// Specialization using a functor (including free functions) with one argument
template <typename F, typename A>
struct ActionFunctorWithArg : ActionFunc
{
    ActionFunctorWithArg(F function, A arg) : m_function(function), m_arg(arg) {}
    virtual void run() {m_function(m_arg);}
    F m_function;
    A m_arg;
};

// Specialization using a member function
template <typename C>
struct ActionMemberFunc : ActionFunc
{
    ActionMemberFunc(void(C::*function)(), C* object) : m_function(function), m_object(object) {}
    virtual void run() {(m_object->*m_function)();}
    void(C::*m_function)();
    C* m_object;
};

template <typename F>
Action::Action(F functor) :
m_entryPoint(new ActionFunctor<F>(functor)), m_check(false)
{
}


template <typename F, typename A>
Action::Action(F function, A argument) :
m_entryPoint(new ActionFunctorWithArg<F, A>(function, argument)), m_check(false)
{
}


template <typename C>
void Action::bind(void(C::*function)(), C* object)
{
    if (m_entryPoint)
        delete m_entryPoint;
    m_entryPoint = new ActionMemberFunc<C>(function, object);
}

template <typename F>
void Action::bind(F functor)
{
    if (m_entryPoint)
        delete m_entryPoint;
    m_entryPoint = new ActionFunctor<F>(functor);
}


template <typename F, typename A>
void Action::bind(F function, A argument)
{
    if (m_entryPoint)
        delete m_entryPoint;
    m_entryPoint = new ActionFunctorWithArg<F, A>(function, argument);
}


template <typename C>
Action::Action(void(C::*function)(), C* object) :
m_entryPoint(new ActionMemberFunc<C>(function, object)), m_check(false)
{
}

inline void Action::run()
{
    m_check = true;
    if (m_entryPoint)
        m_entryPoint->run();
}
