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


const int Hu_goal_steal_health = 18;

class HuGoal_Think : public Goal_Think
{


public:

  HuGoal_Think(AbstRaven_Bot* pBot);
  ~HuGoal_Think();

  //*HU
  void AddGoal_StealHealth();
};


#endif