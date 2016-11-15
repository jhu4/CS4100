#include "BarFlyOwnedStates.h"
#include "MinerOwnedStates.h"
#include "fsm/State.h"
#include "BarFly.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//---------------------------------------------------------------Global state
SalsGlobalState* SalsGlobalState::Instance(){
	static SalsGlobalState instance;
	return &instance;
}

//Only recieves message in the global state
bool SalsGlobalState::OnMessage(BarFly* pBarFly, const Telegram& msg){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch(msg.Msg){
		case Msg_BobsEnteringSaloon:

			cout<<"\nMessage handled by "<<GetNameOfEntity(pBarFly->ID())
			<<" at time:"<<Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

			//record that the Miner Bob is around the bar fly
			pBarFly->sayHelloToBob();

			return true;

		case Msg_BobsLeavingSaloon:

			cout<<"\nMessage handled by "<<GetNameOfEntity(pBarFly->ID())
			<<" at time:"<<Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

			//record that the Miner Bob is NOT around the bar fly
			pBarFly->sayByeToBob();

			return true;
	}

	return false;
}


//--------------------------------------------------------------Carousing
Carousing* Carousing::Instance(){
	static Carousing instance;
	return &instance;
}


void Carousing::Enter(BarFly* pBarFly){
	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"<<"Gonna get some drinks";
}

void Carousing::Execute(BarFly* pBarFly){
	//increase drunkness level every update
	pBarFly->increaseDrunkness();

	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"<<"Drinking..."
	<<"Drunkness level:"<<pBarFly->Drunkness();	

	//if Sal is drunk, chage state to FightinDrunk
	if(pBarFly->isDrunk()){
		pBarFly->GetFSM()->ChangeState(FightinDrunk::Instance());
	}

}

void Carousing::Exit(BarFly* pBarFly){
	//nothing
}

bool Carousing::OnMessage(BarFly* pBarFly,const Telegram& msg){
	//send message to global message handler
	return false;
}

//--------------------------------------------------------------FightinDrunk
FightinDrunk* FightinDrunk::Instance(){
	static FightinDrunk instance;
	return &instance;
}

void FightinDrunk::Enter(BarFly* pBarFly){
	//special event: when the bar fly just enters FightinDrunk state
	//and figure out the Miner Bob was there, he'll say something 
	//special and then enters Fightin state
	if(pBarFly->isMinerAround()){
		cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
		<<"What a coincident! When I think about finding someone to fight"
		<<" and you just walked in!";	

		pBarFly->GetFSM()->ChangeState(Fightin::Instance());
		return;
	}

	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"I am the strongest fighter in the world!";	
}

void FightinDrunk::Execute(BarFly* pBarFly){
	//if Miner Bob is in the saloon, change state to Fightin
	if(pBarFly->isMinerAround()){
		pBarFly->GetFSM()->ChangeState(Fightin::Instance());
		return;
	}
	
	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"Wanna fight someone!";	
}

void FightinDrunk::Exit(BarFly* pBarFly){
	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"I just found someone to fight";	
}

bool FightinDrunk::OnMessage(BarFly* pBarFly, const Telegram& msg){
	//send message to global message handler
	return false;
}


//--------------------------------------------------------------Fightin
Fightin* Fightin::Instance(){
	static Fightin instance;
	return &instance;
}

void Fightin::Enter(BarFly* pBarFly){
	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"You son of bitch!";

	//send Miner Bob a msg telling him that he's insulted
  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                            pBarFly->ID(),        //ID of sender
                            ent_Miner_Bob,        //ID of recipient
                            Msg_Insult,           //the message
                            NO_ADDITIONAL_INFO);
}

void Fightin::Execute(BarFly* pBarFly){
	//the bar fly can only be hitted during this state LOL

	//if the bar fly is being punched enough(in this case, one punch)
	if(pBarFly->isPunchedEnough()){
		//change the state to OutCold
		pBarFly->GetFSM()->ChangeState(OutCold::Instance());

		return;
	}

	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"(Try to punch Miner Bob. Missed)";
}

void Fightin::Exit(BarFly* pBarFly){
	//reset the hitted num
	pBarFly->resetHitted();
}

bool Fightin::OnMessage(BarFly* pBarFly, const Telegram& msg){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch(msg.Msg){
		//receive punch msg by Miner Bob(maybe other people in the future)
		case Msg_Punch:
			cout<<"\nMessage handled by "<<GetNameOfEntity(pBarFly->ID())
			<<" at time:"<<Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

			cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
			<<"Ouch!!(being punched)";						
			//being punched, update some inner data in the bar fly
			pBarFly->receivePunch();

			return true;	
	}

	return false;
}

//---------------------------------------------------------------OutCold
OutCold* OutCold::Instance(){
	static OutCold instance;
	return &instance;
}

void OutCold::Enter(BarFly* pBarFly){
	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"What happened?!";	
}

void OutCold::Execute(BarFly* pBarFly){
	pBarFly->decreaseDrunkness();

	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"<<"(Being more sobered up...)";	
	//Enter Carousing when drunkness level decreasing to 0
	if(pBarFly->isSoberedUp()){
		pBarFly->GetFSM()->ChangeState(Carousing::Instance());
	}
}

void OutCold::Exit(BarFly* pBarFly){
	cout<<"\n"<<GetNameOfEntity(pBarFly->ID())<<":"
	<<"I am entirely sober right now!";
}

bool OutCold::OnMessage(BarFly* pBarFly, const Telegram& msg){
	//send message to global message handler
	return false;
}