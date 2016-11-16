#ifndef HuTEAMSTATES_H
#define HuTEAMSTATES_H
//------------------------------------------------------------------------
//
//  Name: HuTeamStates.h
//
//  Desc: Subclass that only changes the home regions for a more aggressive
//        style of play
//
//  Author: Robin Hu 2005 (rHu@cs.depaul.edu)
//
//------------------------------------------------------------------------
#include <string>

#include "FSM/State.h"
#include "Messaging/Telegram.h"
#include "../../constants.h"


class AbstSoccerTeam;





//------------------------------------------------------------------------
class HuAttacking : public State<AbstSoccerTeam>
{ 
private:
  
  HuAttacking(){}

public:

  //this is a singleton
  static HuAttacking* Instance();

  void Enter(AbstSoccerTeam* team);

  void Execute(AbstSoccerTeam* team);

  void Exit(AbstSoccerTeam* team);

  bool OnMessage(AbstSoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuDefending : public State<AbstSoccerTeam>
{ 
private:
  
  HuDefending(){}

public:

    //this is a singleton
  static HuDefending* Instance();

  void Enter(AbstSoccerTeam* team);

  void Execute(AbstSoccerTeam* team);

  void Exit(AbstSoccerTeam* team);

  bool OnMessage(AbstSoccerTeam*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class HuPrepareForKickOff : public State<AbstSoccerTeam>
{ 
private:
  
  HuPrepareForKickOff(){}

public:

    //this is a singleton
  static HuPrepareForKickOff* Instance();
  
  void Enter(AbstSoccerTeam* team);

  void Execute(AbstSoccerTeam* team);

  void Exit(AbstSoccerTeam* team);

  bool OnMessage(AbstSoccerTeam*, const Telegram&){return false;}
};


//***************************************************************
class HuDefensiveAttack : public State<AbstSoccerTeam>
{
private:

	HuDefensiveAttack() {}

public:

	//this is a singleton
	static HuDefensiveAttack* Instance();

	void Enter(AbstSoccerTeam* team);

	void Execute(AbstSoccerTeam* team);

	void Exit(AbstSoccerTeam* team);

	bool OnMessage(AbstSoccerTeam*, const Telegram&) { return false; }
};



#endif