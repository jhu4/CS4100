#ifndef HU_ATTACKTARGETGOAL_EVALUATOR
#define HU_ATTACKTARGETGOAL_EVALUATOR

#include "../../goals/AttackTargetGoal_Evaluator.h"

class Hu_AttackTargetGoal_Evaluator : public AttackTargetGoal_Evaluator {

public:
	Hu_AttackTargetGoal_Evaluator(double bias) :AttackTargetGoal_Evaluator(bias) {

	}

	//*HU overide function
	double CalculateDesirability(AbstRaven_Bot* pBot);
	void  SetGoal(AbstRaven_Bot* pEnt);
	void RenderInfo(Vector2D Position, AbstRaven_Bot* pBot);

	//*HU added
	bool suvivialCalculator(double myhealth, double mystrength, double theirhealth, double theirstrength, int numOfEnemies);
};

#endif // !HU_ATTACKTARGETGOAL_EVALUATOR
