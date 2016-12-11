#include "Hu_Goal_FightBack.h"
#include "../../goals/Raven_Feature.h"
#include "Hu_TargetingSystem.h"
#include "Hu_Raven_SensoryMemory.h"
#include  "Hu_Goal_AttackTarget.h"

void Hu_Goal_FightBack::Activate() {
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();
	
	double threshold = 0.2;
	double myHealth = Raven_Feature::Health(m_pOwner);
	AbstRaven_Bot* enemey = ((Hu_Raven_SensoryMemory*)m_pOwner->GetSensoryMem())->getLastAttack();

	if (Raven_Feature::Health(enemey) > myHealth) {
		m_iStatus = failed;
		return;
	}

	((Hu_TargetingSystem*)m_pOwner->GetTargetSys())->setTarget(enemey);
	AddSubgoal(new Hu_Goal_AttackTarget(m_pOwner));
}

int  Hu_Goal_FightBack::Process() {
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	return m_iStatus;
}

void Hu_Goal_FightBack::Terminate() {
	m_iStatus = completed;
}