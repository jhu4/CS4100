#ifndef BURKEPLAYERSTATES_H
#define BURKEPLAYERSTATES_H
//------------------------------------------------------------------------
//
//  Name: FieldPlayerStates.h
//
//  Desc: States for the field players of Simple Soccer. See my book
//        for detailed descriptions
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//  9/15/2006 RB Customized for my team
//
//------------------------------------------------------------------------

#include <string>

#include "FSM/State.h"
#include "Messaging/Telegram.h"
#include "../../constants.h"


class FieldPlayer;
class SoccerPitch;



//------------------------------------------------------------------------
class BurkeGlobalPlayerState : public State<FieldPlayer>
{
private:
  
  BurkeGlobalPlayerState(){}

public:

  //this is a singleton
  static BurkeGlobalPlayerState* Instance();

  void Enter(FieldPlayer* player){}

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player){}

  bool OnMessage(FieldPlayer*, const Telegram&);
};



//------------------------------------------------------------------------
class BurkeChaseBall : public State<FieldPlayer>
{
private:
  
  BurkeChaseBall(){}

public:

  //this is a singleton
  static BurkeChaseBall* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class BurkeDribble : public State<FieldPlayer>
{
private:
  
  BurkeDribble(){}

public:

  //this is a singleton
  static BurkeDribble* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player){}

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class BurkeReturnToHomeRegion: public State<FieldPlayer>
{
private:
  
  BurkeReturnToHomeRegion(){}

public:

  //this is a singleton
  static BurkeReturnToHomeRegion* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class BurkeWait: public State<FieldPlayer>
{
private:
  
  BurkeWait(){}

public:

  //this is a singleton
  static BurkeWait* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class BurkeKickBall: public State<FieldPlayer>
{
private:
  
  BurkeKickBall(){}

public:

  //this is a singleton
  static BurkeKickBall* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player){}

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class BurkeReceiveBall: public State<FieldPlayer>
{
private:
  
  BurkeReceiveBall(){}

public:

  //this is a singleton
  static BurkeReceiveBall* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class BurkeSupportAttacker: public State<FieldPlayer>
{
private:
  
  BurkeSupportAttacker(){}

public:

  //this is a singleton
  static BurkeSupportAttacker* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};




  
#endif