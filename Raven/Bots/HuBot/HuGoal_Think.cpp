#include "HuGoal_Think.h"
#include <list>
#include "misc/Cgdi.h"
#include "../../Raven_ObjectEnumerations.h"
#include "misc/utils.h"
#include "Debug/DebugConsole.h"

#include "Hu_BotScriptor.h"
#include "Hu_Goal_StealHealth.h"
#include "Hu_StealHealthGoal_Evaluator.h"
#include "Hu_Goal_FightBack.h"

#include "../../goals/Goal_MoveToPosition.h"
#include "../../goals/Goal_Explore.h"
#include "../../goals/Goal_GetItem.h"
#include "../../goals/Goal_Wander.h"
#include "../../goals/Raven_Goal_Types.h"

//*HU my upgraded Goals
#include "Hu_Goal_AttackTarget.h"
#include "Hu_AttackTargetGoal_Evaluator.h"
#include "Hu_Goal_GetItem.h"
#include "Hu_GetHealthGoal_Evaluator.h"

#include "../../goals/GetWeaponGoal_Evaluator.h"
#include "../../goals/GetHealthGoal_Evaluator.h"
#include "../../goals/ExploreGoal_Evaluator.h"
#include "../../goals/AttackTargetGoal_Evaluator.h"


HuGoal_Think::HuGoal_Think(AbstRaven_Bot* pBot):Goal_Think (pBot)
{
  //*HU change to my lua scriptor
  double HealthBias = Hu_script->GetDouble("Bot_HealthGoalTweaker");
  double ShotgunBias = Hu_script->GetDouble("Bot_ShotgunGoalTweaker");
  double RocketLauncherBias = Hu_script->GetDouble("Bot_RocketLauncherTweaker");
  double RailgunBias = Hu_script->GetDouble("Bot_RailgunGoalTweaker");
  double AttackBias = Hu_script->GetDouble("Bot_AggroGoalTweaker");
  double StealHealthBias = Hu_script->GetDouble("Bot_StealHealthTweaker");
  // get rid of the evaluators added by the superclass
  m_Evaluators.clear();

  //*HU
  m_Evaluators.push_back(new Hu_StealHealthGoal_Evaluator(StealHealthBias));
  m_Evaluators.push_back(new Hu_GetHealthGoal_Evaluator(HealthBias,pBot));
  m_Evaluators.push_back(new Hu_AttackTargetGoal_Evaluator(AttackBias));

  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(ShotgunBias,
                                                     type_shotgun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(RailgunBias,
                                                     type_rail_gun));
  m_Evaluators.push_back(new GetWeaponGoal_Evaluator(RocketLauncherBias,
                                                     type_rocket_launcher));
  
}

//----------------------------- dtor ------------------------------------------
//-----------------------------------------------------------------------------
HuGoal_Think::~HuGoal_Think()
{

}
//*HU
void HuGoal_Think::AddGoal_StealHealth(AbstRaven_Bot* target_bot,Trigger<AbstRaven_Bot>* health_pack)
{
	debug_con << "AddGoal_StealHealth" << "";

	if (notPresent(Hu_goal_steal_health))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Hu_Goal_StealHealth(m_pOwner,target_bot,health_pack));
	}

}

//*HU
void HuGoal_Think::AddGoal_Hu_AttackTarget()
{
	if (notPresent(goal_attack_target))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Hu_Goal_AttackTarget(m_pOwner));
	}
}

//*HU
void HuGoal_Think::AddGoal_GetItem(int ItemType, std::vector<Trigger<AbstRaven_Bot>*> healthpacks)
{
	if (notPresent(ItemTypeToGoalType(ItemType)))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Hu_Goal_GetItem(m_pOwner, ItemType, healthpacks));
	}
}

//*HU
void HuGoal_Think::AddGoal_FightBack() {
	if (notPresent(Hu_goal_fight_back))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Hu_Goal_FightBack(m_pOwner));
	}
}