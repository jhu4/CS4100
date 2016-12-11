#include "Hu_Goal_FightBack.h"
#include "../../goals/Raven_Feature.h"

void Hu_Goal_FightBack::Activate() {
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();
	
	double threshold = 0.2;
	double myHealth = Raven_Feature::Health(m_pOwner);
	
	
}

int  Hu_Goal_FightBack::Process() {
	return 0;
}

void Hu_Goal_FightBack::Terminate() {

}