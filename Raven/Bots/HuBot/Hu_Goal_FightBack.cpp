#include "Hu_Goal_FightBack.h"
#include "../../goals/Raven_Feature.h"
#include "Hu_TargetingSystem.h"
#include "Hu_Raven_SensoryMemory.h"
#include  "Hu_Goal_AttackTarget.h"

//*HU
void Hu_Goal_FightBack::Activate() {
	m_iStatus = active;

	//get the last attacker saved in my Hu_Raven_SensoryMemory
	AbstRaven_Bot* enemy = ((Hu_Raven_SensoryMemory*)m_pOwner->GetSensoryMem())->getLastAttack();

	((Hu_TargetingSystem*)m_pOwner->GetTargetSys())->setTarget(enemy);
}

int  Hu_Goal_FightBack::Process() {
	ActivateIfInactive();

	if (m_pOwner->GetTargetSys()->GetTarget()->isDead() || !m_pOwner->GetSensoryMem()->isUnderAttack()) {
		m_iStatus = completed;
	}
	
	return m_iStatus;
}

void Hu_Goal_FightBack::Terminate() {
	m_iStatus = completed;
}