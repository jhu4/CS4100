#include "Hu_Goal_GetItem.h"
#include "Hu_Goal_FightBack.h"
#include "Hu_Goal_SnakeWalk.h"
#include "../../AbstRaven_Bot.h"
#include "../../goals/Goal_Wander.h"
#include "../../goals/Goal_MoveToPosition.h"
#include "../../goals/Goal_FollowPath.h"
#include "../../Raven_ObjectEnumerations.h"
#include "../../navigation/Raven_PathPlanner.h"
#include "../../Raven_Map.h"
#include "../../Raven_Game.h"
#include "../../AbstSteeringBehaviors.h"
#include "Hu_Raven_SensoryMemory.h"
#include "Debug\DebugConsole.h"
#include "Hu_Bot.h"
#include "../../Raven_Messages.h"
#include "Messaging\Telegram.h"
void Hu_Goal_GetItem::Activate()
{	

	m_iStatus = active;

	m_pGiverTrigger = 0;

	
	m_pOwner->GetPathPlanner()->RequestPathToItem(m_iItemToGet);
	
	if (m_pOwner->GetSensoryMem()->isUnderAttack()) {
		debug_con << "GETITEM::SNAKEWALK" << "";
		AddSubgoal(new Hu_Goal_SnakeWalk(m_pOwner, snakewalk));
	}
	else {

		//the bot may have to wait a few update cycles before a path is calculated
		//so for appearances sake it just wanders
		AddSubgoal(new Goal_Wander(m_pOwner));
	}
	
	
}

int  Hu_Goal_GetItem::Process() {
	ActivateIfInactive();

	//*HU 
	if (hasItemBeenStolen())
	{	
		RemoveAllSubgoals();
		Terminate();
	}

	//*HU if bot is under attack 
	if (m_pOwner->GetSensoryMem()->isUnderAttack() && !fightbackon) {
		RemoveAllSubgoals();

		fightbackon = true;
		//debug_con << "GETITEM::FIGHTBACK " << "";
		AddSubgoal(new Hu_Goal_FightBack(m_pOwner));
		
		
		Vector2D dummy;
		if (((Hu_Bot*)m_pOwner)->canStepBackwardLeft(dummy) || ((Hu_Bot*)m_pOwner)->canStepBackwardRight(dummy))
		{
			//debug_con << "GETITEM::SNAKEWALK" << "";
			AddSubgoal(new Hu_Goal_SnakeWalk(m_pOwner, snakewalk));
		}
	}

	
	//process the subgoals
	m_iStatus = ProcessSubgoals();
	

	return m_iStatus;
}

void Hu_Goal_GetItem::Terminate() {
	m_pOwner->GetSteering()->WanderOff();
	m_iStatus = completed;
}

bool Hu_Goal_GetItem::hasItemBeenStolen()const {
	//if the target is health
	if (m_pGiverTrigger &&
		!m_pGiverTrigger->isActive())
	{
		return true;
	}

	return false;
}

//*Find the closet health pack based on the location
Trigger<AbstRaven_Bot>* Hu_Goal_GetItem::getClosestHealthPack() {

	std::vector<Trigger<AbstRaven_Bot>*>::iterator it;
	Raven_PathPlanner* pathplanner = m_pOwner->GetPathPlanner();
	Raven_Map* map = m_pOwner->GetWorld()->GetMap();
	double min_cost = MaxDouble;
	Trigger<AbstRaven_Bot>* healthpack;


	for(it = healths.begin(); it != healths.end(); it++){

		if((*it)->isActive()){
			Trigger<AbstRaven_Bot>* health = static_cast<Trigger<AbstRaven_Bot>*> (*it);

			double cost = map->CalculateCostToTravelBetweenNodes(pathplanner->GetClosestNodeToPosition(m_pOwner->Pos()),pathplanner->GetClosestNodeToPosition((*it)->Pos()));
		
			if (cost <= min_cost) {
				min_cost = cost;
				healthpack = health;
			}
		}
	}
	
	targethealthpack = healthpack;
	if (healthpack) {
		debug_con << "Healthpack exist" << "";

	}
	return healthpack;
}


Trigger<AbstRaven_Bot>* Hu_Goal_GetItem::getSecondClosestHealthPack() {
	
	return NULL;
}

bool Hu_Goal_GetItem::HandleMessage(const Telegram& msg)
{
	//first, pass the message down the goal hierarchy
	bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

	//if the msg was not handled, test to see if this goal can handle it
	if (bHandled == false)
	{
		switch (msg.Msg)
		{
		case Msg_PathReady:

			
			//RemoveAllSubgoals();

			AddSubgoal(new Goal_FollowPath(m_pOwner,
				m_pOwner->GetPathPlanner()->GetPath()));

			//get the pointer to the item
			m_pGiverTrigger = static_cast<Raven_Map::TriggerType*>(msg.ExtraInfo);

			return true; //msg handled


		case Msg_NoPathAvailable:

			m_iStatus = failed;

			return true; //msg handled

		default: return false;
		}
	}

	//handled by subgoals
	return true;
}
