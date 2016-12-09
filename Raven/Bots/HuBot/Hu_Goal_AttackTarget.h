#ifndef HU_GOAL_ATTACKTARGET
#define HU_GOAL_ATTACKTARGET


#include "../../goals/Goal_AttackTarget.h"


class Hu_Goal_AttackTarget : public Goal_AttackTarget {

public:
	Hu_Goal_AttackTarget(AbstRaven_Bot* pOwner) :Goal_AttackTarget(pOwner) {

	}

	//*HU overide function
	void Activate();
};

#endif