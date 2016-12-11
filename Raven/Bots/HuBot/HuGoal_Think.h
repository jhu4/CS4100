#ifndef HuGOAL_THINK_H
#define HuGOAL_THINK_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   HuGoal_Think .h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to aHuitrate between a collection of high level goals, and
//          to process those goals.
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "2d/Vector2D.h"
#include "../../Goals/Goal_Think.h"
#include "../../AbstRaven_Bot.h"
#include "../../Goals/Goal_Evaluator.h"
#include "Triggers/Trigger.h"

const int Hu_goal_steal_health = 18;
const int Hu_goal_avoid_more = 19;

class HuGoal_Think : public Goal_Think
{


public:

  HuGoal_Think(AbstRaven_Bot* pBot);
  ~HuGoal_Think();

  //*HU added addGoal functions
  void AddGoal_StealHealth(AbstRaven_Bot* target_bot, Trigger<AbstRaven_Bot>* health_pack);
  void AddGoal_Hu_AttackTarget();
  void AddGoal_GetItem(int ItemType, std::vector<Trigger<AbstRaven_Bot>*> healthPacks);
};


#endif