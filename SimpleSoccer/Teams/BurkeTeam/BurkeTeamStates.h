#ifndef BURKETEAMSTATES_H
#define BURKETEAMSTATES_H
//------------------------------------------------------------------------
//
//  Name: BurkeTeamStates.h
//
//  Desc: Subclass that only changes the home regions for a more aggressive
//        style of play
//
//  Author: Robin Burke 2005 (rburke@cs.depaul.edu)
//
//------------------------------------------------------------------------
#include <string>

#include "FSM/State.h"
#include "Messaging/Telegram.h"
#include "../../constants.h"


class AbstSoccerTeam;





//------------------------------------------------------------------------
class BurkeAttacking : public State<AbstSoccerTeam>
{ 
private:
  
  BurkeAttacking(){}

public:

  //this is a singleton
  static BurkeAttacking* Instance();

  void Enter(AbstSoccerTeam* team);

  void Execute(AbstSoccerTeam* team);

  void Exit(AbstSoccerTeam* team);

  bool OnMessage(AbstSoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class BurkeDefending : public State<AbstSoccerTeam>
{ 
private:
  
  BurkeDefending(){}

public:

    //this is a singleton
  static BurkeDefending* Instance();

  void Enter(AbstSoccerTeam* team);

  void Execute(AbstSoccerTeam* team);

  void Exit(AbstSoccerTeam* team);

  bool OnMessage(AbstSoccerTeam*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class BurkePrepareForKickOff : public State<AbstSoccerTeam>
{ 
private:
  
  BurkePrepareForKickOff(){}

public:

    //this is a singleton
  static BurkePrepareForKickOff* Instance();
  
  void Enter(AbstSoccerTeam* team);

  void Execute(AbstSoccerTeam* team);

  void Exit(AbstSoccerTeam* team);

  bool OnMessage(AbstSoccerTeam*, const Telegram&){return false;}
};


#endif