#include "Hu_Goal_GetItem.h"
#include "../../AbstRaven_Bot.h"
#include "../../goals/Goal_Wander.h"
#include "../../goals/Goal_MoveToPosition.h"
#include "../../Raven_ObjectEnumerations.h"
#include "../../navigation/Raven_PathPlanner.h"
#include "../../Raven_Map.h"
#include "../../Raven_Game.h"
#include "Hu_Raven_SensoryMemory.h"
#include "Debug\DebugConsole.h"


void Hu_Goal_GetItem::Activate()
{	

	m_iStatus = active;

	m_pGiverTrigger = 0;

	//*HU request the path to the position of the closet health
	Trigger<AbstRaven_Bot>* healthpack = getClosestHealthPack();
	if (healthpack == NULL) {
		Terminate();
	}

	if (m_iItemToGet == type_health) {	
		m_pOwner->GetPathPlanner()->RequestPathToPosition(healthpack->Pos());
	}
	else {
		m_pOwner->GetPathPlanner()->RequestPathToItem(m_iItemToGet);
	}
	
	

	//the bot may have to wait a few update cycles before a path is calculated
	//so for appearances sake it just wanders
	AddSubgoal(new Goal_Wander(m_pOwner));

}

int  Hu_Goal_GetItem::Process() {
	ActivateIfInactive();

	//*HU 
	if (hasItemBeenStolen())
	{	
		targethealthpack = NULL;
		Terminate();
	}

	else
	{
		//process the subgoals
		m_iStatus = ProcessSubgoals();
	}

	return m_iStatus;
}


bool Hu_Goal_GetItem::hasItemBeenStolen()const {
	//if the target is health
	if (targethealthpack) {
		if (!targethealthpack->isActive() && m_pOwner->hasLOSto(targethealthpack->Pos())) {
			return true;
		}
	}
	else{//if the target is other thing
		if (m_pGiverTrigger &&
			!m_pGiverTrigger->isActive() &&
			m_pOwner->hasLOSto(m_pGiverTrigger->Pos()))
		{
			return true;
		}
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

	return healthpack;
}


Trigger<AbstRaven_Bot>* Hu_Goal_GetItem::getSecondClosestHealthPack() {
	
	return NULL;
}