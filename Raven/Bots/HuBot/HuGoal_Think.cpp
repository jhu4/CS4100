#include "HuGoal_Think.h"
#include <list>
#include "misc/Cgdi.h"
#include "../../Raven_ObjectEnumerations.h"
#include "misc/utils.h"

#include "Hu_BotScriptor.h"
#include "Hu_Goal_StealHealth.h"
#include "Hu_StealHealthGoal_Evaluator.h"

#include "../../goals/Goal_MoveToPosition.h"
#include "../../goals/Goal_Explore.h"
#include "../../goals/Goal_GetItem.h"
#include "../../goals/Goal_Wander.h"
#include "../../goals/Raven_Goal_Types.h"
#include "../../goals/Goal_AttackTarget.h"

#include "../../goals/GetWeaponGoal_Evaluator.h"
#include "../../goals/GetHealthGoal_Evaluator.h"
#include "../../goals/ExploreGoal_Evaluator.h"
#include "../../goals/AttackTargetGoal_Evaluator.h"


HuGoal_Think::HuGoal_Think(AbstRaven_Bot* pBot):Goal_Think (pBot)
{
  // load priorities from script
  Hu_BotScriptor* pMyScript = Hu_BotScriptor::Instance();
  double HealthBias = pMyScript->GetDouble("Bot_HealthGoalTweaker");
  double ShotgunBias = pMyScript->GetDouble("Bot_ShotgunGoalTweaker");
  double RocketLauncherBias = pMyScript->GetDouble("Bot_RocketLauncherTweaker");
  double RailgunBias = pMyScript->GetDouble("Bot_RailgunGoalTweaker");
  double ExploreBias = pMyScript->GetDouble("Bot_ExploreTweaker");
  double AttackBias = pMyScript->GetDouble("Bot_AggroGoalTweaker");
  //*HU
  double StealHealthBias = pMyScript->GetDouble("Bot_StealHealthTweaker");
  // get rid of the evaluators added by the superclass
  m_Evaluators.clear();

  //create the evaluator objects
  m_Evaluators.push_back(new GetHealthGoal_Evaluator(HealthBias));
  m_Evaluators.push_back(new ExploreGoal_Evaluator(ExploreBias));
  m_Evaluators.push_back(new AttackTargetGoal_Evaluator(AttackBias));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(ShotgunBias,
                                                     type_shotgun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(RailgunBias,
                                                     type_rail_gun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(RocketLauncherBias,
                                                     type_rocket_launcher));
  //*HU
  m_Evaluators.push_back(new Hu_StealHealthGoal_Evaluator(StealHealthBias));
}

//----------------------------- dtor ------------------------------------------
//-----------------------------------------------------------------------------
HuGoal_Think::~HuGoal_Think()
{

}

void HuGoal_Think::AddGoal_StealHealth() {

}
