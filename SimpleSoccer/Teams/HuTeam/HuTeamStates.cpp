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
  const int BlueRegions[TeamSize] = { 1,14,13,12,10 };
  const int RedRegions[TeamSize] = { 16,2,3,7,13 };

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
  const int BlueRegions[TeamSize] = { 1,3,4,5,7 };
  const int RedRegions[TeamSize] = { 16,13,11,9,4 };

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
  //steering target must be updated to that of its new home region
  team->UpdateTargetsOfWaitingPlayers();
}

void HuDefending::Execute(AbstSoccerTeam* team)
{
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


void HuDefending::Exit(AbstSoccerTeam* team){}

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

	const int BlueRegions[TeamSize] = { 1,7,9,10,11 };
	const int RedRegions[TeamSize] = { 16,13,11,9,4 };

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
	PlayerBase* defensiveattacker = ((HuSoccerTeam*)team)->DefensiveAttacker();
	if (defensiveattacker != NULL) {
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			defensiveattacker->ID(),
			defensiveattacker->ID(),
			Msg_DefensiveAttacker,
			NULL);
	}


	//if a player is in either the Wait or ReturnToHomeRegion states, its
	//steering target must be updated to that of its new home region
	team->UpdateTargetsOfWaitingPlayers();
}

void HuDefensiveAttack::Execute(AbstSoccerTeam* team)
{	
	PlayerBase* defensiveattacker = ((HuSoccerTeam*)team)->DefensiveAttacker();

	if (team->InControl()) {
		team->GetFSM()->ChangeState(HuAttacking::Instance()); 
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			defensiveattacker->ID(),
			defensiveattacker->ID(),
			Msg_Wait,
			NULL);
		return;
	}
	else if (!team->InControl() && ((HuSoccerTeam*)team)->isBallInOurHalf()) {
		team->GetFSM()->ChangeState(HuDefending::Instance()); 
		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			defensiveattacker->ID(),
			defensiveattacker->ID(),
			Msg_Wait,
			NULL);
		return;
	}

	//calculate the best position for any supporting attacker to move to
	//team->DetermineBestSupportingPosition();

}

void HuDefensiveAttack::Exit(AbstSoccerTeam* team)
{
	//there is no supporting player for defense
	((HuSoccerTeam*)team)->SetDefensiveAttacker(NULL);
	return;
}
