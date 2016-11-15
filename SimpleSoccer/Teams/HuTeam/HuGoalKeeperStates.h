#ifndef HUKEEPERSTATES_H
#define HUKEEPERSTATES_H
//------------------------------------------------------------------------
//
//  Name: GoalKeeperStates.h
//
//  Desc:   Declarations of all the states used by a Simple Soccer
//          goalkeeper
//
//  Author: Jinan Hu
//
//------------------------------------------------------------------------
#include <string>
#include "FSM/State.h"
#include "Messaging/Telegram.h"
#include "../../constants.h"


class GoalKeeper;
class SoccerPitch;


class HuGlobalKeeperState: public State<GoalKeeper>
{
private:
  
  HuGlobalKeeperState(){}

public:

  //this is a singleton
  static HuGlobalKeeperState* Instance();

  void Enter(GoalKeeper* keeper){}

  void Execute(GoalKeeper* keeper){}

  void Exit(GoalKeeper* keeper){}

  bool OnMessage(GoalKeeper*, const Telegram&);
};

//-----------------------------------------------------------------------------

class HuTendGoal: public State<GoalKeeper>
{
private:
  
  HuTendGoal(){}

public:

  //this is a singleton
  static HuTendGoal* Instance();

  void Enter(GoalKeeper* keeper);

  void Execute(GoalKeeper* keeper);

  void Exit(GoalKeeper* keeper);

  bool OnMessage(GoalKeeper*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuInterceptBall: public State<GoalKeeper>
{
private:
  
  HuInterceptBall(){}

public:

  //this is a singleton
  static HuInterceptBall* Instance();

  void Enter(GoalKeeper* keeper);

  void Execute(GoalKeeper* keeper);

  void Exit(GoalKeeper* keeper);

  bool OnMessage(GoalKeeper*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuReturnHome: public State<GoalKeeper>
{
private:
  
  HuReturnHome(){}

public:

  //this is a singleton
  static HuReturnHome* Instance();

  void Enter(GoalKeeper* keeper);

  void Execute(GoalKeeper* keeper);

  void Exit(GoalKeeper* keeper);

  bool OnMessage(GoalKeeper*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuPutBallBackInPlay: public State<GoalKeeper>
{
private:
  
  HuPutBallBackInPlay(){}

public:

  //this is a singleton
  static HuPutBallBackInPlay* Instance();

  void Enter(GoalKeeper* keeper);

  void Execute(GoalKeeper* keeper);

  void Exit(GoalKeeper* keeper){}

  bool OnMessage(GoalKeeper*, const Telegram&){return false;}
};





#endif