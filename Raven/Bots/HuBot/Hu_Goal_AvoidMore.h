#ifndef HU_GOAL_AVOIDMORE
#define HU_GOAL_AVOIDMORE

#include "HuGoal_Think.h"

#include "Goals/Goal_Composite.h"
#include "../../goals/Raven_Goal_Types.h"
#include "../../AbstRaven_Bot.h"
#include "Triggers/Trigger.h"

//*HU
class Hu_Goal_AvoidMore : public Goal_Composite<AbstRaven_Bot>
{

private:


public:

	Hu_Goal_AvoidMore(AbstRaven_Bot* pOwner, AbstRaven_Bot* tb) :Goal_Composite<AbstRaven_Bot>(pOwner, Hu_goal_avoid_more)
	{}

	void Activate();

	int  Process();

	void Terminate();

};






#endif