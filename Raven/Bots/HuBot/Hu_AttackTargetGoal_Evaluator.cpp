#include "Hu_AttackTargetGoal_Evaluator.h"
#include "Hu_Raven_SensoryMemory.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "../../AbstRaven_Bot.h"
#include "HuGoal_Think.h"
#include "../../goals/Raven_Feature.h"
#include "Debug\DebugConsole.h"
//*HU modified function
double Hu_AttackTargetGoal_Evaluator::CalculateDesirability(AbstRaven_Bot* pBot)
{
	double Desirability = 0.0;

	//*HU this is too CPU consuming so I disabled them
	//int enemiesInFOV = ((Hu_Raven_SensoryMemory*)pBot->GetSensoryMem())->NumberBotInFOV();
	//double enemiesHealth = ((Hu_Raven_SensoryMemory*)pBot->GetSensoryMem())->getHealthOfEnemiesInFOV();
	//double enemiesStrength = ((Hu_Raven_SensoryMemory*)pBot->GetSensoryMem())->getStrengthOfEnemiesInFOV();
	double myHealth = Raven_Feature::Health(pBot);
	double myStrength = Raven_Feature::TotalWeaponStrength(pBot);

	
	//do not attack group of enemies or higher health enemies 
	//if (enemiesInFOV > 2){
		//return 0;
	//}

	//only do the calculation if there is a target present
	if (pBot->GetTargetSys()->isTargetPresent())
	{
		const double Tweaker = 1.0;
		
		AbstRaven_Bot* enemy = pBot->GetTargetBot();

		Desirability = Tweaker * myHealth * myStrength * Raven_Feature::Health(enemy);

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

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void Hu_AttackTargetGoal_Evaluator::RenderInfo(Vector2D Position, AbstRaven_Bot* pBot)
{
	gdi->TextAtPos(Position, "AT: " + ttos(CalculateDesirability(pBot), 2));
	return;

	std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
	gdi->TextAtPos(Position + Vector2D(0, 12), s);
}

bool Hu_AttackTargetGoal_Evaluator::suvivialCalculator(double myhealth,double mystrength, double theirhealth, double theirstrength, int numOfEnemies) {
	if (myhealth > theirhealth && mystrength > theirstrength) {
		return true;
	}
	else if (myhealth > theirhealth && mystrength<theirstrength && mystrength > (0.5*theirstrength) && numOfEnemies == 1){
		return true;
	}
	else if(myhealth > theirhealth && mystrength<theirstrength && mystrength>(0.7*theirstrength) && numOfEnemies == 2){
		return true;
	}

	return false;
}