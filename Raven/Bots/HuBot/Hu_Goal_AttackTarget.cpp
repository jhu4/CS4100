#include "Hu_Goal_AttackTarget.h"
#include "Hu_Goal_SnakeWalk.h"
#include "Hu_Bot.h"
#include "Hu_TargetingSystem.h"
#include "../../goals/Goal_SeekToPosition.h"
#include "../../goals/Goal_HuntTarget.h"
#include "Debug\DebugConsole.h"

//*HU Need to be modified
void Hu_Goal_AttackTarget::Activate() {
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();

	//it is possible for a bot's target to die whilst this goal is active so we
	//must test to make sure the bot always has an active target
	if (!m_pOwner->GetTargetSys()->isTargetPresent())
	{
		m_iStatus = completed;

		return;
	}

	//if the bot is able to shoot the target (there is LOS between bot and
	//target), then select a tactic to follow while shooting
	if (m_pOwner->GetTargetSys()->isTargetShootable())
	{
		//if the bot has space to strafe then do so
		Vector2D dummy;
		if (((Hu_Bot*)m_pOwner)->canStepLeft(dummy) || ((Hu_Bot*)m_pOwner)->canStepRight(dummy))
		{
			AddSubgoal(new Hu_Goal_SnakeWalk(m_pOwner,sidedodge));
		}

		//if not able to strafe, head directly at the target's position 
		else
		{
			AddSubgoal(new Goal_SeekToPosition(m_pOwner, m_pOwner->GetTargetBot()->Pos()));
		}
	}

	//if the target is not visible, go hunt it.
	else
	{
		AddSubgoal(new Goal_HuntTarget(m_pOwner));
	}

	//debug_con << "Hu_AttackTarget Activate" << "";

}