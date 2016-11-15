 #ifndef HUPLAYERSTATES_H
#define HUPLAYERSTATES_H
//------------------------------------------------------------------------
//
//  Name: HuFieldPlayerStates.h
//
//  Desc: States for the field players of Simple Soccer. See my book
//        for detailed descriptions
//
//  Author: Jinan Hu 2016 (jhu4@wpi.edu)
//
//------------------------------------------------------------------------

#include <string>

#include "FSM/State.h"
#include "Messaging/Telegram.h"
#include "../../constants.h"


class HuFieldPlayer;
class SoccerPitch;



//------------------------------------------------------------------------
class HuGlobalPlayerState : public State<HuFieldPlayer>
{
private:
  
  HuGlobalPlayerState(){}

public:

  //this is a singleton
  static HuGlobalPlayerState* Instance();

  void Enter(HuFieldPlayer* player){}

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player){}

  bool OnMessage(HuFieldPlayer*, const Telegram&);
};



//------------------------------------------------------------------------
class HuChaseBall : public State<HuFieldPlayer>
{
private:
  
  HuChaseBall(){}

public:

  //this is a singleton
  static HuChaseBall* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player);

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuDribble : public State<HuFieldPlayer>
{
private:
  
  HuDribble(){}

public:

  //this is a singleton
  static HuDribble* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player){}

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class HuReturnToHomeRegion: public State<HuFieldPlayer>
{
private:
  
  HuReturnToHomeRegion(){}

public:

  //this is a singleton
  static HuReturnToHomeRegion* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player);

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuWait: public State<HuFieldPlayer>
{
private:
  
  HuWait(){}

public:

  //this is a singleton
  static HuWait* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player);

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuKickBall: public State<HuFieldPlayer>
{
private:
  
  HuKickBall(){}

public:

  //this is a singleton
  static HuKickBall* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player){}

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuReceiveBall: public State<HuFieldPlayer>
{
private:
  
  HuReceiveBall(){}

public:

  //this is a singleton
  static HuReceiveBall* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player);

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class HuSupportAttacker: public State<HuFieldPlayer>
{
private:
  
  HuSupportAttacker(){}

public:

  //this is a singleton
  static HuSupportAttacker* Instance();

  void Enter(HuFieldPlayer* player);

  void Execute(HuFieldPlayer* player);

  void Exit(HuFieldPlayer* player);

  bool OnMessage(HuFieldPlayer*, const Telegram&){return false;}
};




  
#endif