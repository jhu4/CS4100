#include "Hu_Goal_AvoidMore.h"




void Hu_Goal_AvoidMore::Activate() {
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();
}

int  Hu_Goal_AvoidMore::Process() {
	return 1;
}

void Hu_Goal_AvoidMore::Terminate() {

}