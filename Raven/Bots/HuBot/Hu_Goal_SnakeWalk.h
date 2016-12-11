#ifndef GOAL_SNACKWALK_H
#define GOAL_SNACKWALK_H

#include "../../Goals/Goal_Composite.h"
#include "../../AbstRaven_Bot.h"

const int sidedodge = 1;
const int snakewalk = 2;

class Hu_Goal_SnakeWalk : public Goal_Composite<AbstRaven_Bot>
{
protected:

	Vector2D    m_vStrafeTarget;

	bool        m_bClockwise;

	Vector2D  GetStrafeTarget()const;

	int walktype;

public:

	Hu_Goal_SnakeWalk(AbstRaven_Bot* pBot,int type) :Goal_Composite<AbstRaven_Bot>(pBot, 21), walktype(type),m_bClockwise(RandBool())
	{}


	void Activate();

	int  Process();

	void Render();

	void Terminate();

};

#endif