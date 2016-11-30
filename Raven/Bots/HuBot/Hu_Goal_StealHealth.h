#ifndef HU_GOAL_STEALHEALTH
#define HU_GOAL_STEALHEALTH


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

	Hu_Goal_StealHealth(AbstRaven_Bot* pOwner) :Goal_Composite<AbstRaven_Bot>(pOwner, goal_get_health)
	{}

	void Activate();

	int  Process();

	void Terminate() { m_iStatus = completed; }

};




#endif 