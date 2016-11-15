#include "BarFly.h"

bool BarFly::HandleMessage(const Telegram& msg){
	return b_pStateMachine->HandleMessage(msg);
}

void BarFly::Update(){
  SetTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);

  b_pStateMachine->Update();
}

//------------------------------------------------------------------
//	Sal is drunk when his druness level is over the threshold
//------------------------------------------------------------------
bool BarFly::isDrunk()const{
	if(b_drunkness>=drunknessThreshold) 
		return true;

	return false;
}

//------------------------------------------------------------------
//	Sal is gonna cooling down only when he received enough punches
//------------------------------------------------------------------
bool BarFly::isPunchedEnough()const{
	if(b_beingHitted>=wakeUpPunchThreshold){
		return true;
	}
	return false;
}

//------------------------------------------------------------------
//	Sal is gonna drink again if he's purely sober
//------------------------------------------------------------------
bool BarFly::isSoberedUp()const{
	if(b_drunkness<=0)
		return true;

	return false;
}