#ifndef BARFLYOWNEDSTATES_H
#define BARFLYOWNEDSTATES_H
//------------------------------------------------------------------------
//
//  Name:   SalOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Sal class.
//          Note that a global state has not been implemented.
//
//  Author: Jinan Hu 2016 (jhu4@wpi.edu)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class BarFly;
struct Telegram;

//------------------------------------------------------------------------
//	Sal does nothing in this state, he only receives msg in this state
//------------------------------------------------------------------------
class SalsGlobalState : public State<BarFly>{
private:
	SalsGlobalState(){}

	//copy ctor and assignment should be private
	SalsGlobalState(const SalsGlobalState&);
	SalsGlobalState& operator=(const SalsGlobalState&);

public:

	//this is a singleton
	static SalsGlobalState* Instance();

	virtual void Enter(BarFly* sal) {}

	virtual void Execute(BarFly* sal) {}

	virtual void Exit(BarFly* sal) {}

	virtual bool OnMessage(BarFly* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  In this state, Sal will raise his intoxication level by one at
//	each update. When the level passes 10, he'll change the state to
//	FightinDrunk 
//------------------------------------------------------------------------
class Carousing: public State<BarFly>{
private:
	Carousing(){}

	//copy ctor and assignment should be private
	Carousing(const Carousing&);
	Carousing& operator=(const Carousing&);

public:

	//this is a singleton
	static Carousing* Instance();

	virtual void Enter(BarFly* sal);

	virtual void Execute(BarFly* sal);

	virtual void Exit(BarFly* sal);

	virtual bool OnMessage(BarFly* agent, const Telegram& msg);

};


//------------------------------------------------------------------------
//	In this state, Sal stops drinking and if the Miner is in the Saloon, 
//	he will insult the Miner and begin Fightin
//	otherwise he waits until the Miner arrives to insult him and begin Fightin
//	and changes his state to Fightin
// 	Sal's intoxination level doesn't change in this state
//------------------------------------------------------------------------
class FightinDrunk: public State<BarFly>{
private:
	FightinDrunk(){}

	//copy ctor and assignment should be private
	FightinDrunk(const FightinDrunk&);
	FightinDrunk& operator=(const FightinDrunk&);

public:

	//this is a singleton
	static FightinDrunk* Instance();

	virtual void Enter(BarFly* sal);

	virtual void Execute(BarFly* sal);

	virtual void Exit(BarFly* sal);

	virtual bool OnMessage(BarFly* agent, const Telegram& msg);

};



//------------------------------------------------------------------------
//	In this state, Sal begin to fight with the Miner, but he never
//	hits the Miner and one puch from the Miner knocks him out cold.
//	Then he'll change the state to OutCold
//------------------------------------------------------------------------
class Fightin: public State<BarFly>{
private:
	Fightin(){}

	//copy ctor and assignment should be private
	Fightin(const Fightin&);
	Fightin& operator=(const Fightin&);

public:

	//this is a singleton
	static Fightin* Instance();

	virtual void Enter(BarFly* sal);

	virtual void Execute(BarFly* sal);

	virtual void Exit(BarFly* sal);

	virtual bool OnMessage(BarFly* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//	Sal regains sobriety while while knocked out, one level per update
//	When he is sober(zero intoxication), he wakes up is ready to drink some
//	more and changes he's state to Carousing
//------------------------------------------------------------------------
class OutCold: public State<BarFly>{
private:
	OutCold(){}

	//copy ctor and assignment should be private
	OutCold(const OutCold&);
	OutCold& operator=(const OutCold&);

public:

	//this is a singleton
	static OutCold* Instance();

	virtual void Enter(BarFly* sal);

	virtual void Execute(BarFly* sal);

	virtual void Exit(BarFly* sal);

	virtual bool OnMessage(BarFly* agent, const Telegram& msg);

};

#endif