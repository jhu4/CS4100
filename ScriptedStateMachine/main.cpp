//include the libraries
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "luabind-0.9.lib")

extern "C"
{
  #include <lualib.h>
  #include <lauxlib.h>
}

#include <string>
#include <iostream>
using namespace std;

//include the luabind headers. Make sure you have the paths set correctly
//to the lua, luabind and Boost files.
#include <luabind/luabind.hpp>
using namespace luabind;

#include "Entity.h"
#include "Miner.h"
#include "script/LuaHelperFunctions.h"
#include "ScriptedStateMachine.h"
#include "misc/ConsoleUtils.h"

void RegisterScriptedStateMachineWithLua(lua_State* pLua)
{
  module(pLua)
    [
      class_<ScriptedStateMachine<Miner> >("ScriptedStateMachine")
    
        .def("ChangeState", &ScriptedStateMachine<Miner>::ChangeState)
        .def("CurrentState", &ScriptedStateMachine<Miner>::CurrentState)
        .def("SetCurrentState", &ScriptedStateMachine<Miner>::SetCurrentState)
        //*new methods
        .def("SetPreviousState", &ScriptedStateMachine<Miner>::SetPreviousState)
        .def("SetGlobalState", &ScriptedStateMachine<Miner>::SetGlobalState)
        .def("RevertToPreviousState", &ScriptedStateMachine<Miner>::RevertToPreviousState)
    ];  
}


void RegisterEntityWithLua(lua_State* pLua)
{
  module(pLua)
    [
      class_<Entity>("Entity")

        .def("Name", &Entity::Name)
        .def("ID", &Entity::ID)   
    ];  
}


void RegisterMinerWithLua(lua_State* pLua)
{
  module(pLua)
    [   
      class_<Miner, bases<Entity> >("Miner")

        .def("GoldCarried", &Miner::GoldCarried)
        .def("SetGoldCarried", &Miner::SetGoldCarried)
        .def("AddToGoldCarried", &Miner::AddToGoldCarried)
        .def("Fatigued", &Miner::Fatigued)
        .def("DecreaseFatigue", &Miner::DecreaseFatigue)
        .def("IncreaseFatigue", &Miner::IncreaseFatigue) 
        .def("GetFSM", &Miner::GetFSM)
        //*new methods
        .def("IsPeein", &Miner::IsPeein)
        .def("IsBladderFull", &Miner::IsBladderFull)
        .def("FillBladder", &Miner::FillBladder)
        .def("EmptyBladder", &Miner::EmptyBladder)
        .def("getBladderVal", &Miner::getBladderVal)
    ];  
}



int main()
{
  //create a lua state
  lua_State* pLua = luaL_newstate();

  LuaExceptionGuard guard(pLua);

  //open the lua libaries - new in 5.1
  luaL_openlibs(pLua);
  
  //open luabind
  open(pLua);
  
  //bind the relevant classes to Lua
  RegisterEntityWithLua(pLua);
  RegisterMinerWithLua(pLua);
  RegisterScriptedStateMachineWithLua(pLua);
  
 
  //load and run the script
  RunLuaScript(pLua, "StateMachineScript.lua");
  
  //create a miner
  Miner bob("bob");

  //grab the global table from the lua state. This will inlclude
  //all the functions and variables defined in the scripts run so far
  //(StateMachineScript.lua in this example)
  object states = globals(pLua);

  //ensure states is a table
  if (type(states) == LUA_TTABLE)
  {
    //make sure Bob's CurrentState object is set to a valid state.
    bob.GetFSM()->SetCurrentState(states["State_GoHome"]);
    //*make sure Bob's PreviousState and GlobalState object is set to a valid state
    bob.GetFSM()->SetCurrentState(states["State_GoHome"]);
    bob.GetFSM()->SetGlobalState(states["State_Global"]);
    //run him through a few update cycles
    //*changed to 20 cycles
    for (int i=0; i<20; ++i)
    {
      bob.Update();
      Sleep(800);
    }
  }

  //wait for a keypress before exiting
  PressAnyKeyToContinue();

  return 0;
}


