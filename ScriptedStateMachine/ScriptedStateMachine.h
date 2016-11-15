#ifndef SCRIPTEDScriptedStateMachine_H
#define SCRIPTEDScriptedStateMachine_H
#pragma warning (disable : 4786)
//------------------------------------------------------------------------
//
//  Name:   ScriptedStateMachine.h
//
//  Desc:   A simple scripted state machine class. Inherit from this class and 
//          create some states in Lua to give your agents FSM functionality
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

extern "C"
{
  #include <lua.h>
}

#include <luabind/luabind.hpp>
#include <cassert>


template <class entity_type>
class ScriptedStateMachine
{

private:

  //pointer to the agent that owns this instance
  entity_type*      m_pOwner;

  //the current state is a lua table of lua functions. A table may be
  //represented in C++ using a luabind::object
  luabind::object   m_CurrentState;

  //*The previous state is a lua table of lua functions.
  luabind::object m_PreviousState;

  //*The global state
  luabind::object m_GlobalState;
  
public:

  ScriptedStateMachine(entity_type* owner):m_pOwner(owner){}

  //use these methods to initialize the FSM
  void SetCurrentState(const luabind::object& s){m_CurrentState = s;}

  //*use this method to set globalstate
  void SetGlobalState(const luabind::object& s){m_GlobalState=s;} 

  //*use this method to set globalstate
  void SetPreviousState(const luabind::object& s){m_PreviousState=s;}

  //call this to update the FSM
  void  Update()
  {
    //*if a global state exist, update it
    if(m_GlobalState.is_valid()){
      m_GlobalState["Execute"](m_pOwner);
    }

    //make sure the state is valid before calling its Execute 'method'
    if (m_CurrentState.is_valid())  //this could also be written as 'if(m_CurrentState)'
    { 
      m_CurrentState["Execute"](m_pOwner);
    }

  }

  //change to a new state
  void  ChangeState(const luabind::object& new_state)
  {
    assert(new_state && "<StateMachine::ChangeState>:trying to assign null state to current");

    //*Keep a record of the previous state
    m_PreviousState=m_CurrentState;

    //call the exit method of the existing state
    m_PreviousState["Exit"](m_pOwner);

    //change state to the new state
    m_CurrentState = new_state;

    //call the entry method of the new state
    new_state["Enter"](m_pOwner);
  }

  //*change to the previous state
  void  RevertToPreviousState(){
    m_CurrentState["Exit"](m_pOwner);
    m_PreviousState["Enter"](m_pOwner);
    luabind::object a=m_CurrentState;
    luabind::object b=m_PreviousState;
    m_CurrentState=b;
    m_PreviousState=a;
  }

  //retrieve the current state
  const luabind::object&  CurrentState()const{return m_CurrentState;}
};

#endif


