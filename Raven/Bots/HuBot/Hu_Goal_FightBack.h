#ifndef HU_GOAL_FIGHTBACK
#define HU_GOAL_FIGHTBACK

#include "HuGoal_Think.h"

#include "Goals/Goal_Composite.h"
#include "../../goals/Raven_Goal_Types.h"
#include "../../AbstRaven_Bot.h"
#include "Triggers/Trigger.h"

//*HU
class Hu_Goal_FightBack : public Goal_Composite<AbstRaven_Bot>
{

private:


public:

	Hu_Goal_FightBack(AbstRaven_Bot* pOwner) :Goal_Composite<AbstRaven_Bot>(pOwner,Hu_goal_fight_back){}

	void Activate();

	int  Process();

	void Terminate();

};

#endif