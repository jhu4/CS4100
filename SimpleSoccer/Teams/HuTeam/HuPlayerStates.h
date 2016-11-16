#ifndef HUPLAYERSTATES_H
#define HUPLAYERSTATES_H
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
class HuGlobalPlayerState : public State<FieldPlayer>
{
private:
  
  HuGlobalPlayerState(){}

public:

  //this is a singleton
  static HuGlobalPlayerState* Instance();

  void Enter(FieldPlayer* player){}

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player){}

  bool OnMessage(FieldPlayer*, const Telegram&);
};



//------------------------------------------------------------------------
class HuChaseBall : public State<FieldPlayer>
{
private:
  
  HuChaseBall(){}

public:

  //this is a singleton
  static HuChaseBall* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuDribble : public State<FieldPlayer>
{
private:
  
  HuDribble(){}

public:

  //this is a singleton
  static HuDribble* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player){}

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class HuReturnToHomeRegion: public State<FieldPlayer>
{
private:
  
  HuReturnToHomeRegion(){}

public:

  //this is a singleton
  static HuReturnToHomeRegion* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuWait: public State<FieldPlayer>
{
private:
  
  HuWait(){}

public:

  //this is a singleton
  static HuWait* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuKickBall: public State<FieldPlayer>
{
private:
  
  HuKickBall(){}

public:

  //this is a singleton
  static HuKickBall* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player){}

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class HuReceiveBall: public State<FieldPlayer>
{
private:
  
  HuReceiveBall(){}

public:

  //this is a singleton
  static HuReceiveBall* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class HuSupportAttacker: public State<FieldPlayer>
{
private:
  
  HuSupportAttacker(){}

public:

  //this is a singleton
  static HuSupportAttacker* Instance();

  void Enter(FieldPlayer* player);

  void Execute(FieldPlayer* player);

  void Exit(FieldPlayer* player);

  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//*****------------------------------------------------------------------------
class HuDefensiveAttacker : public State<FieldPlayer>
{
private:

	HuDefensiveAttacker() {}

public:

	//this is a singleton
	static HuDefensiveAttacker* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&) { return false; }
};

 
//*****------------------------------------------------------------------------
class HuGuarder : public State<FieldPlayer>
{
private:

	HuGuarder() {}

public:

	//this is a singleton
	static HuGuarder* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&) { return false; }
};


//*****------------------------------------------------------------------------
class HuDefender : public State<FieldPlayer>
{
private:

	HuDefender() {}

public:

	//this is a singleton
	static HuDefender* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&) { return false; }
};

#endif