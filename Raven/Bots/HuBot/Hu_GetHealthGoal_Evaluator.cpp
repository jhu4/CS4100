#include "Hu_GetHealthGoal_Evaluator.h"
#include "HuGoal_Think.h"
#include "Hu_Bot.h"

#include "misc/Stream_Utility_Functions.h"
#include "../../Raven_ObjectEnumerations.h"
#include "../../goals/Raven_Feature.h"
#include "Hu_Raven_SensoryMemory.h"
#include "../../Raven_Game.h"
#include "../../Raven_Map.h"
#include "../../triggers/Trigger_HealthGiver.h"
#include "../../triggers/TriggerSystem.h"

#include "2D\Vector2D.h"
#include "Debug\DebugConsole.h"


//*HU
Hu_GetHealthGoal_Evaluator::Hu_GetHealthGoal_Evaluator(double bias, AbstRaven_Bot* bot) :Goal_Evaluator(bias),me(bot){
	
	Raven_Map::TriggerSystem::TriggerList trigger_list = bot->GetWorld()->GetMap()->GetTriggers();
	Raven_Map::TriggerSystem::TriggerList::const_iterator it;
	for (it = trigger_list.begin(); it != trigger_list.end(); it++) {

		//store references to health packs in this goal evaluators
		if ((*it)->EntityType() == type_health) {
			Trigger<AbstRaven_Bot>* trigger = static_cast<Trigger<AbstRaven_Bot>*>(*it);
			healthPacks.push_back(trigger);
		}
	}

}


//---------------------- CalculateDesirability -------------------------------------
//-----------------------------------------------------------------------------
double Hu_GetHealthGoal_Evaluator::CalculateDesirability(AbstRaven_Bot* pBot)
{
	//first grab the distance to the closest instance of a health item
	double Distance = Raven_Feature::DistanceToItem(pBot, type_health);

	//if the distance feature is rated with a value of 1 it means that the
	//item is either not present on the map or too far away to be worth 
	//considering, therefore the desirability is zero
	if (Distance == 1)
	{
		return 0;
	}
	else
	{
		//the desirability of finding a health item is proportional to the amount
		//of health remaining and inversely proportional to the distance from the
		//nearest instance of a health item.
		double Desirability = 0.6 * (1 - Raven_Feature::Health(pBot)) /
			(Raven_Feature::DistanceToItem(pBot, type_health));

		//ensure the value is in the range 0 to 1
		Clamp(Desirability, 0, 1);

		//bias the value according to the personality of the bot
		Desirability *= m_dCharacterBias;

		return Desirability;
	}
}



//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void Hu_GetHealthGoal_Evaluator::SetGoal(AbstRaven_Bot* pBot)
{
	((HuGoal_Think*)pBot->GetBrain())->AddGoal_GetItem(type_health,healthPacks);
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void Hu_GetHealthGoal_Evaluator::RenderInfo(Vector2D Position, AbstRaven_Bot* pBot)
{
	gdi->TextAtPos(Position, "H: " + ttos(CalculateDesirability(pBot), 2));
	return;

	std::string s = ttos(1 - Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::DistanceToItem(pBot, type_health));
	gdi->TextAtPos(Position + Vector2D(0, 15), s);
}