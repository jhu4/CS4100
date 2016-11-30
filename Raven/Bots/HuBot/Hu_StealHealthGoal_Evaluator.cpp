#include "Hu_StealHealthGoal_Evaluator.h"
#include "HuGoal_Think.h"
#include "Hu_Bot.h"

#include "misc/Stream_Utility_Functions.h"
#include "../../Raven_ObjectEnumerations.h"
#include "../../goals/Raven_Feature.h"
#include "../../Raven_SensoryMemory.h"
#include "../../Raven_Game.h"
#include "../../Raven_Map.h"
#include "../../triggers/Trigger_HealthGiver.h"
#include "../../triggers/TriggerSystem.h"

#include "2D\Vector2D.h"
#include "Debug\DebugConsole.h"

double Hu_StealHealthGoal_Evaluator::CalculateDesirability(AbstRaven_Bot* bot) {
	
	//find the closest active health pack
	Trigger<AbstRaven_Bot>* closest_health_pack = ClosestActiveHealth(bot);

	//if no active health packs
	if (closest_health_pack == NULL)
	{
		return 0;
	}

	double me_to_health = Vec2DDistanceSq(bot->Pos(), closest_health_pack->Pos());
	double opp_to_health = MaxDouble;

	AbstRaven_Bot* closest_opponent = ClosestBotToHealth(bot, closest_health_pack, opp_to_health);

	//if there are no known opponents or the closest opponent closer to the health pack
	if (closest_opponent == NULL || opp_to_health < me_to_health){
		return 0;
	}
	
	const double tweaker = 1;
	

	double desirability = tweaker *
		(1 - Raven_Feature::Health(closest_opponent) * Raven_Feature::Health(closest_opponent)) *
		(1 - Raven_Feature::DistanceToItem(closest_opponent,type_health));

	Clamp(desirability, 0, 1);

	desirability *= m_dCharacterBias;

	//save a record for the target bot and health pack
	TargetBot = closest_opponent;
	HealthPack = closest_health_pack;

	return desirability;
}

void  Hu_StealHealthGoal_Evaluator::SetGoal(AbstRaven_Bot* bot) {
	((HuGoal_Think*)bot->GetBrain())->AddGoal_StealHealth(TargetBot,HealthPack);
}

void Hu_StealHealthGoal_Evaluator::RenderInfo(Vector2D posistion, AbstRaven_Bot* bot) {
	gdi->TextAtPos(posistion, "SH:"+ttos(CalculateDesirability(bot)));
}



Trigger<AbstRaven_Bot>* Hu_StealHealthGoal_Evaluator::ClosestActiveHealth(AbstRaven_Bot* bot) {
	Trigger<AbstRaven_Bot>* closest_health_pack = NULL;
	double smallest_dist = MaxDouble;

	//iterate throught all of the trigger in the map
	Raven_Map::TriggerSystem::TriggerList trigger_list = bot->GetWorld()->GetMap()->GetTriggers();
	Raven_Map::TriggerSystem::TriggerList::const_iterator it;
	for (it = trigger_list.begin(); it != trigger_list.end(); it++) {
		
		//only if the trigger is a health trigger, and it's active
		//calculate the distance btw the bot and the health pack
		//update the minimum distance and the closest bot if it can
		if ((*it)->EntityType() == type_health && (*it)->isActive()) {
			double dist = Vec2DDistanceSq((*it)->Pos(), bot->Pos());


			if (dist <= smallest_dist) {
				smallest_dist = dist;
				closest_health_pack = (*it);
			}
		}
	}

	return closest_health_pack;
}

AbstRaven_Bot* Hu_StealHealthGoal_Evaluator::ClosestBotToHealth(AbstRaven_Bot* mybot, Trigger<AbstRaven_Bot>* health_pack,double &distance){
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
			distance = smallest_dist;
		}
	}	

	return closest_bot;
}

