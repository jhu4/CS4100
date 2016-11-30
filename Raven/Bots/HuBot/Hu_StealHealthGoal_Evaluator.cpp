#include "Hu_StealHealthGoal_Evaluator.h"
#include "misc/Stream_Utility_Functions.h"
#include "../../Raven_ObjectEnumerations.h"
#include "../../goals/Raven_Feature.h"
#include "HuGoal_Think.h"

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

