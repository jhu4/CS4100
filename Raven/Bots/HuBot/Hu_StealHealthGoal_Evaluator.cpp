#include "Hu_StealHealthGoal_Evaluator.h"
#include "HuGoal_Think.h"

#include "misc/Stream_Utility_Functions.h"
#include "../../Raven_ObjectEnumerations.h"
#include "../../goals/Raven_Feature.h"
#include "../../Raven_SensoryMemory.h"
#include "../../Raven_Game.h"
#include "../../Raven_Map.h"
#include "../../triggers/Trigger_HealthGiver.h"
#include "2D\Vector2D.h"
#include "Triggers\TriggerSystem.h"
#include "../../triggers/TriggerSystem.h"


double Hu_StealHealthGoal_Evaluator::CalculateDesirability(AbstRaven_Bot* pBot) {
	//first grab the distance to the closest instance of a health item
	double dist_to_health = Raven_Feature::DistanceToItem(pBot, type_health);

	//if the distance feature is rated with a value of 1 it means that the
	//item is either not present on the map or too far away to be worth 
	//considering, therefore the desirability is zero
	if (dist_to_health == 1)
	{
		return 0;
	}


	double dist_to_bot = Raven_Feature::DistanceToItem(pBot, type_bot);
	


}

void  Hu_StealHealthGoal_Evaluator::SetGoal(AbstRaven_Bot* pEnt) {

}

void Hu_StealHealthGoal_Evaluator::RenderInfo(Vector2D Position, AbstRaven_Bot* pBot) {

}



Trigger<AbstRaven_Bot>* Hu_StealHealthGoal_Evaluator::ClosestActiveHealth(AbstRaven_Bot* opponent) {
	
	//iterate throught all of the trigger in the map
	Raven_Map::TriggerSystem::TriggerList trigger_list = opponent->GetWorld()->GetMap()->GetTriggers();
	Raven_Map::TriggerSystem::TriggerList::const_iterator it;
	for (it = trigger_list.begin(); it != trigger_list.end(); it++) {
		//only if the trigger is a health trigger
		if ((*it)->EntityType() == type_health) {

		}
	}


}

AbstRaven_Bot* Hu_StealHealthGoal_Evaluator::ClosestBotToHealth(AbstRaven_Bot* mybot, Trigger<AbstRaven_Bot>* health_pack){
	std::list<AbstRaven_Bot*> opponent_list = mybot->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	double smallest_dist = MaxDouble;
	AbstRaven_Bot* closest_bot = NULL;


	//iterate throught the opponent bot list and find out the closest bot to the health pack
	std::list<AbstRaven_Bot*>::const_iterator it;
	for (it = opponent_list.begin(); it != opponent_list.end(); it++) {
		
		double dist = Vec2DDistanceSq((*it)->Pos(), health_pack->Pos());

		if (dist <= smallest_dist) {
			closest_bot = (*it);
			smallest_dist = dist;
		}
	}	

	return closest_bot;
}

