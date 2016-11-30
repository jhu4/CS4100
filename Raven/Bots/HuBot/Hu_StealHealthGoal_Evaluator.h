#ifndef HU_STEALHEALTHGOAL_EVALUATOR
#define HU_STEALHEALTHGOAL_EVALUATOR
#pragma warning (disable:4786)

#include "../../AbstRaven_Bot.h"
#include "../../goals/Goal_Evaluator.h"
#include "../../triggers/Trigger.h"


class Hu_StealHealthGoal_Evaluator : public Goal_Evaluator
{
public:

	Hu_StealHealthGoal_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(AbstRaven_Bot* pBot);

	void  SetGoal(AbstRaven_Bot* pEnt);

	void RenderInfo(Vector2D Position, AbstRaven_Bot* pBot);

	//helper function
	//Given a bot, return the pointer to the closest health pack
	Trigger<AbstRaven_Bot>* ClosestActiveHealth(AbstRaven_Bot* opponent);
	//Given my bot and a pointer to a health pack, return the closest opponent to the health pack
	AbstRaven_Bot* ClosestBotToHealth(AbstRaven_Bot* mybot, Trigger<AbstRaven_Bot>* health_pack, double &distance);

};


#endif