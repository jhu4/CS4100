#include "Hu_Goal_StealHealth.h"
#include "../../goals/Goal_GetItem.h"
#include "../../Raven_ObjectEnumerations.h"


#include "Debug\DebugConsole.h"

void Hu_Goal_StealHealth::Activate() {
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();

	//if the target die while the goal is activated OR
	//if the health pack is claimed, fail the goal, fail the goal
	if (target_bot->isDead() || !health_pack->isActive()) {
		m_iStatus = failed;
		return;
	}

	else {
		AddSubgoal(new Goal_GetItem(m_pOwner,type_health));
	}

	debug_con << "StealHealth activated" << "";
}

int  Hu_Goal_StealHealth::Process() {
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	return m_iStatus;
}

void Hu_Goal_StealHealth::Terminate() {
	m_iStatus = completed; 
}
