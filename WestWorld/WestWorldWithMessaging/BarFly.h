#ifndef BARFLY_H
#define BARFLY_H
//------------------------------------------------------------------------
//
//  Name:   Sal.h
//
//  Desc:   A class defining a always drunk character
//
//  Author: Jinan Hu 2016 (jhu4@wpi.edu)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "BarFlyOwnedStates.h"
#include "fsm/StateMachine.h"

struct Telegram;

//above this value Sal is drunk
const int drunknessThreshold=10;
//the number Sal being hitted to wake him up
const int wakeUpPunchThreshold=1;


class BarFly: public BaseGameEntity{
private:
	//an instance of the state machine class
	StateMachine<BarFly>*		b_pStateMachine;

	location_type						b_Location;

	//the number of time the BarFly being pucnched
	int 										b_beingHitted;

	//the higher the value, the more toxinated the BarFly 
	int 										b_drunkness;

	//indicate if the miner is around
	bool										b_isMinerAround;

public:
	BarFly(int id):b_Location(saloon)
								,b_beingHitted(0)
								,b_drunkness(0)
								,b_isMinerAround(false)
								,BaseGameEntity(id)
	{
		b_pStateMachine=new StateMachine<BarFly>(this);

		b_pStateMachine->SetCurrentState(Carousing::Instance());

		b_pStateMachine->SetGlobalState(SalsGlobalState::Instance());
		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE BARFLY */
	}							

	~BarFly() { delete b_pStateMachine; };

	//this must be implemented
	void Update();

	//so must this
	virtual bool HandleMessage(const Telegram& msg);

	StateMachine<BarFly>* GetFSM()const{return b_pStateMachine;}

  //-------------------------------------------------------------accessors
  location_type Location()const{return b_Location;}
  void          ChangeLocation(location_type loc){b_Location=loc;}
    
  bool     			isDrunk()const;
  bool					isSoberedUp()const;
  int 					Drunkness(){return b_drunkness;}
  void 					increaseDrunkness(){b_drunkness++;}
  void 					decreaseDrunkness(){b_drunkness--;}

  bool					isPunchedEnough()const;
  void					receivePunch() { b_beingHitted++; };
  void					resetHitted() { b_beingHitted = 0; };

  bool					isMinerAround() { return b_isMinerAround; };
  void					sayHelloToBob() { b_isMinerAround = true; };
  void					sayByeToBob() { b_isMinerAround = false; };

};

#endif