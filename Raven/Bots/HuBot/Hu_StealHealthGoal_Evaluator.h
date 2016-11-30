#ifndef HU_STEALHEALTHGOAL_EVALUATOR
#define HU_STEALHEALTHGOAL_EVALUATOR
#pragma warning (disable:4786)

#include "../../AbstRaven_Bot.h"
#include "../../goals/Goal_Evaluator.h"

class Hu_StealHealthGoal_Evaluator : public Goal_Evaluator
{
public:

	Hu_StealHealthGoal_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(AbstRaven_Bot* pBot);

	void  SetGoal(AbstRaven_Bot* pEnt);

	void RenderInfo(Vector2D Position, AbstRaven_Bot* pBot);
};


#endif