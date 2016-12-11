#ifndef HU_GETHEALTHGOAL_EVALUATOR
#define HU_GETHEALTHGOAL_EVALUATOR

#include "../../AbstRaven_Bot.h"
#include "../../goals/Goal_Evaluator.h"
#include "../../triggers/Trigger.h"
#include <vector>
class Hu_GetHealthGoal_Evaluator : public Goal_Evaluator
{

private:
	AbstRaven_Bot* me;
	Trigger<AbstRaven_Bot>* targetHealth;
	std::vector<Trigger<AbstRaven_Bot>*> healthPacks;

public:

	Hu_GetHealthGoal_Evaluator(double bias,AbstRaven_Bot* me);

	double CalculateDesirability(AbstRaven_Bot* pBot);

	void  SetGoal(AbstRaven_Bot* pEnt);

	void RenderInfo(Vector2D Position, AbstRaven_Bot* pBot);
};


#endif
