#include "HuTeamStates.h"
#include "HuSoccerTeam.h"
#include "HuSoccerMessages.h"

#include "../../AbstSoccerTeam.h"
#include "../../PlayerBase.h"
#include "Messaging/MessageDispatcher.h"
#include "../../constants.h"
#include "../../SoccerPitch.h"
#include "Debug/DebugConsole.h"

#define DEBUG_HUTEAM_STATES

//************************************************************************ ATTACKING

HuAttacking* HuAttacking::Instance()
{
  static HuAttacking instance;

  return &instance;
}


void HuAttacking::Enter(AbstSoccerTeam* team)
{
//#ifdef DEBUG_HUTEAM_STATES
  debug_con << team->Name() << " entering HuAttacking state" << "";
//#endif

  //these define the home regions for this state of each of the players
  const int BlueRegions[TeamSize] = { 1,14,12,13,10 };
  const int RedRegions[TeamSize] = { 16,5,3,4,7 };

  //set up the player's home regions
  if (team->Color() == AbstSoccerTeam::blue)
  {
    team->ChangePlayerHomeRegions(BlueRegions);
  }
  else
  {
    team->ChangePlayerHomeRegions(RedRegions);
  }

  //if a player is in either the Wait or ReturnToHomeRegion states, its
  //steering target must be updated to that of its new home region to enable
  //it to move into the correct position.
  team->UpdateTargetsOfWaitingPlayers();
}


void HuAttacking::Execute(AbstSoccerTeam* team)
{
  
	if (((HuSoccerTeam*)team)->isBallInOurHalf()) {
		team->GetFSM()->ChangeState(HuDefending::Instance()); return;
	}
	else {
		if (!team->InControl()) {
			team->GetFSM()->ChangeState(HuDefensiveAttack::Instance()); return;
		}
	}

  //calculate the best position for any supporting attacker to move to
  team->DetermineBestSupportingPosition();
}

void HuAttacking::Exit(AbstSoccerTeam* team)
{
  //there is no supporting player for defense
  team->SetSupportingPlayer(NULL);
}



//************************************************************************ DEFENDING

HuDefending* HuDefending::Instance()
{
  static HuDefending instance;

  return &instance;
}

void HuDefending::Enter(AbstSoccerTeam* team)
{
#ifdef DEBUG_HUTEAM_STATES
  debug_con << team->Name() << " entering HuDefending state" << "";
#endif

  //these define the home regions for this state of each of the players
  const int BlueRegions[TeamSize] = { 1,3,7,5,1 };
  const int RedRegions[TeamSize] = { 16,12,10,14,16 };

  //set up the player's home regions
  if (team->Color() == AbstSoccerTeam::blue)
  {
    team->ChangePlayerHomeRegions(BlueRegions);
  }
  else
  {
    team->ChangePlayerHomeRegions(RedRegions);
  }
  
  //**
  PlayerBase* defender = ((HuSoccerTeam*)team)->DetermineBestDefender();
  PlayerBase* guarder = ((HuSoccerTeam*)team)->DetermineBestGuarder();
  if (defender != NULL) {
	  Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
		  defender->ID(),
		  defender->ID(),
		  Msg_Defender,
		  NULL);
  }
  if (guarder != NULL) {
	  Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
		  guarder->ID(),
		  guarder->ID(),
		  Msg_Defender,
		  NULL);
  }
  ((HuSoccerTeam*)team)->SetDefender(defender);
  ((HuSoccerTeam*)team)->SetGuarder(guarder);

  //if a player is in either the Wait or ReturnToHomeRegion states, its
  //steering target must be updated to that of its new home region
  team->UpdateTargetsOfWaitingPlayers();
}

void HuDefending::Execute(AbstSoccerTeam* team)
{
	if (((HuSoccerTeam*)team)->Defender() == NULL) {
		PlayerBase* defender = ((HuSoccerTeam*)team)->DetermineBestDefender();
		if (defender != NULL) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				defender->ID(),
				defender->ID(),
				Msg_Defender,
				NULL);
		}
		((HuSoccerTeam*)team)->SetDefender(defender);
	}

	//if in control change states
	if (!((HuSoccerTeam*)team)->isBallInOurHalf()) {
		if (!team->InControl()) {
			team->GetFSM()->ChangeState(HuDefensiveAttack::Instance()); return;
		}
		else {
			team->GetFSM()->ChangeState(HuAttacking::Instance()); return;
		}
	}
}


void HuDefending::Exit(AbstSoccerTeam* team){
	PlayerBase* defender = ((HuSoccerTeam*)team)->Defender();
	PlayerBase* guarder = ((HuSoccerTeam*)team)->Guarder();
	if (defender!=NULL) {
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			defender->ID(),
			defender->ID(),
			Msg_GoHome,
			NULL);
		//there is no supporting player for defensive attacker
		((HuSoccerTeam*)team)->SetDefender(NULL);
	}

	if (guarder != NULL) {
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			guarder->ID(),
			guarder->ID(),
			Msg_GoHome,
			NULL);
		//there is no supporting player for defensive attacker
		((HuSoccerTeam*)team)->SetGuarder(NULL);
	}
	return;
}

//************************************************************************ KICKOFF
HuPrepareForKickOff* HuPrepareForKickOff::Instance()
{
  static HuPrepareForKickOff instance;

  return &instance;
}

void HuPrepareForKickOff::Enter(AbstSoccerTeam* team)
{
#ifdef DEBUG_HUTEAM_STATES
	debug_con << team->Name() << " entering HuPrepareForKickOff state" << "";
#endif
  //reset key player pointers
  team->SetControllingPlayer(NULL);
  team->SetSupportingPlayer(NULL);
  team->SetReceiver(NULL);
  team->SetPlayerClosestToBall(NULL);

  //send Msg_GoHome to each player.
  team->ReturnAllFieldPlayersToHome();
}

void HuPrepareForKickOff::Execute(AbstSoccerTeam* team)
{
  //if both teams in position, start the game
  if (team->AllPlayersAtHome() && team->Opponents()->AllPlayersAtHome() ||
		(team->AllPlayersAtHome() && team->Pitch()->OneTeamReady()))
  {
    team->GetFSM()->ChangeState(HuDefending::Instance());
  }
}

void HuPrepareForKickOff::Exit(AbstSoccerTeam* team)
{
	if (team->Color() == AbstSoccerTeam::blue)
		team->Pitch()->SetBlueTeamReady();
	else
		team->Pitch()->SetRedTeamReady();

}


//************************************************************************HuDefensiveAttack
//*change
HuDefensiveAttack* HuDefensiveAttack::Instance()
{
	static HuDefensiveAttack instance;

	return &instance;
}

void HuDefensiveAttack::Enter(AbstSoccerTeam* team)
{
#ifdef DEBUG_HUTEAM_STATES
	debug_con << team->Name() << " entering HuDefensiveAttack state" << "";
#endif

	const int BlueRegions[TeamSize] = { 1,9,13,11,10 };
	const int RedRegions[TeamSize] = { 16,6,4,8,7 };

	//set up the player's home regions
	if (team->Color() == AbstSoccerTeam::blue)
	{
		team->ChangePlayerHomeRegions(BlueRegions);
	}
	else
	{
		team->ChangePlayerHomeRegions(RedRegions);
	}

	//**
	PlayerBase* defensiveattacker = ((HuSoccerTeam*)team)->DetermineBestDefensiveAttacker();
	if (defensiveattacker != NULL) {
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			defensiveattacker->ID(),
			defensiveattacker->ID(),
			Msg_DefensiveAttacker,
			NULL);
	}
	((HuSoccerTeam*)team)->SetDefensiveAttacker(defensiveattacker);

	//if a player is in either the Wait or ReturnToHomeRegion states, its
	//steering target must be updated to that of its new home region
	team->UpdateTargetsOfWaitingPlayers();
}

void HuDefensiveAttack::Execute(AbstSoccerTeam* team)
{	

	if (((HuSoccerTeam*)team)->DefensiveAttacker() == NULL) {
		PlayerBase* defensiveattacker = ((HuSoccerTeam*)team)->DetermineBestDefensiveAttacker();
		if (defensiveattacker != NULL) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				defensiveattacker->ID(),
				defensiveattacker->ID(),
				Msg_Defender,
				NULL);
		}
		((HuSoccerTeam*)team)->SetDefensiveAttacker(defensiveattacker);
	}

	if (team->InControl()) {
		team->GetFSM()->ChangeState(HuAttacking::Instance()); 
		return;
	}
	else if (!team->InControl() && ((HuSoccerTeam*)team)->isBallInOurHalf()) {
		team->GetFSM()->ChangeState(HuDefending::Instance()); 
		return;
	}

}

void HuDefensiveAttack::Exit(AbstSoccerTeam* team)
{	
	PlayerBase* defensiveattacker = ((HuSoccerTeam*)team)->DefensiveAttacker();
	if (defensiveattacker!=NULL) {
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			defensiveattacker->ID(),
			defensiveattacker->ID(),
			Msg_GoHome,
			NULL);
		//there is no supporting player for defensive attacker
		((HuSoccerTeam*)team)->SetDefensiveAttacker(NULL);
	}
	
	return;
}
