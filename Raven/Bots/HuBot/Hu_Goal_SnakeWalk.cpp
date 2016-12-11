#include "Hu_Goal_SnakeWalk.h"
#include "Hu_Bot.h"
#include "../../goals/Goal_SeekToPosition.h"
#include "../../AbstRaven_Bot.h"
#include "../../AbstTargetingSystem.h"
#include "../../AbstSteeringBehaviors.h"
#include "Hu_Raven_SensoryMemory.h"

void Hu_Goal_SnakeWalk::Activate()
{
	m_iStatus = active;

	m_pOwner->GetSteering()->SeekOn();

	if(walktype==sidedodge){
		if (m_bClockwise)
		{
			if (((Hu_Bot*)m_pOwner)->canStepRight(m_vStrafeTarget))
			{
				m_pOwner->GetSteering()->SetTarget(m_vStrafeTarget);
			}
			else
			{
				m_bClockwise = !m_bClockwise;
				m_iStatus = inactive;
			}
		}

		else
		{
			if (((Hu_Bot*)m_pOwner)->canStepLeft(m_vStrafeTarget))
			{
				m_pOwner->GetSteering()->SetTarget(m_vStrafeTarget);
			}
			else
			{
				m_bClockwise = !m_bClockwise;
				m_iStatus = inactive;
			}
		}
	}
	else if (walktype == snakewalk) {
		if (m_bClockwise)
		{
			if (((Hu_Bot*)m_pOwner)->canStepBackwardRight(m_vStrafeTarget))
			{
				
				m_pOwner->GetSteering()->SetTarget(m_vStrafeTarget);
			}
			else
			{
				m_bClockwise = !m_bClockwise;
				m_iStatus = failed;
			}
		}

		else
		{
			if (((Hu_Bot*)m_pOwner)->canStepBackwardLeft(m_vStrafeTarget))
			{
				
				m_pOwner->GetSteering()->SetTarget(m_vStrafeTarget);
			}
			else
			{
				m_bClockwise = !m_bClockwise;
				m_iStatus = failed;
			}
		}
	}
}


//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Hu_Goal_SnakeWalk::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//*HU if target goes out of view terminate
	if (sidedodge && !m_pOwner->GetTargetSys()->isTargetWithinFOV())
	{
		m_iStatus = completed;
	}
	else if (snakewalk && !m_pOwner->GetSensoryMem()->isUnderAttack()) {
		m_iStatus = completed;
	}

	//else if bot reaches the target position set status to inactive so the goal 
	//is reactivated on the next update-step
	else if (m_pOwner->isAtPosition(m_vStrafeTarget))
	{
		m_iStatus = inactive;
	}

	return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Hu_Goal_SnakeWalk::Terminate()
{
	m_pOwner->GetSteering()->SeekOff();
}

void Hu_Goal_SnakeWalk::Render()
{
#define SHOW_TARGET
#ifdef SHOW_TARGET
	gdi->OrangePen();
	gdi->HollowBrush();

	gdi->Line(m_pOwner->Pos(), m_vStrafeTarget);
	gdi->Circle(m_vStrafeTarget, 3);
#endif

}

