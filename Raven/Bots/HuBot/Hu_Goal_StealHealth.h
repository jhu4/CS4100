#ifndef HU_GOAL_STEALHEALTH
#define HU_GOAL_STEALHEALTH

#include "HuGoal_Think.h"

#include "Goals/Goal_Composite.h"
#include "../../goals/Raven_Goal_Types.h"
#include "../../AbstRaven_Bot.h"
#include "Triggers/Trigger.h"



//*HU
class Hu_Goal_StealHealth : public Goal_Composite<AbstRaven_Bot>
{

private:
	AbstRaven_Bot* target_bot;
	Trigger<AbstRaven_Bot>* health_pack;


public:

	Hu_Goal_StealHealth(AbstRaven_Bot* pOwner, AbstRaven_Bot* tb, Trigger<AbstRaven_Bot>* hp) :Goal_Composite<AbstRaven_Bot>(pOwner, Hu_goal_steal_health),target_bot(tb),health_pack(hp)
	{}
	//Hu_Goal_StealHealth(AbstRaven_Bot* pOwner) :Goal_Composite<AbstRaven_Bot>(pOwner, Hu_goal_steal_health)
	//{}
	void Activate();

	int  Process();

	void Terminate();

};




#endif 