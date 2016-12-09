#include "Hu_AttackTargetGoal_Evaluator.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "../../AbstRaven_Bot.h"
#include "HuGoal_Think.h"
#include "../../goals/Raven_Feature.h"

//*HU
double Hu_AttackTargetGoal_Evaluator::CalculateDesirability(AbstRaven_Bot* pBot)
{
	double Desirability = 0.0;

	//only do the calculation if there is a target present
	if (pBot->GetTargetSys()->isTargetPresent())
	{
		const double Tweaker = 1.0;

		Desirability = Tweaker *
			Raven_Feature::Health(pBot) *
			Raven_Feature::TotalWeaponStrength(pBot);

		//bias the value according to the personality of the bot
		Desirability *= m_dCharacterBias;
	}

	return Desirability;
}

//*HU
void Hu_AttackTargetGoal_Evaluator::SetGoal(AbstRaven_Bot* pBot)
{
	((HuGoal_Think*)pBot->GetBrain())->AddGoal_Hu_AttackTarget();
}