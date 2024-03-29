#ifndef HUTARGETING_SYSTEM_H
#define HUTARGETING_SYSTEM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_TargetingSystem.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to select a target from the opponents currently in a bot's
//          perceptive memory.
//-----------------------------------------------------------------------------
#include "2d/Vector2D.h"
#include <list>
#include "../../AbstTargetingSystem.h"

class AbstRaven_Bot;

class Hu_TargetingSystem : public AbstTargetingSystem
{

public:

	Hu_TargetingSystem(AbstRaven_Bot* owner) :AbstTargetingSystem(owner) {}

	//each time this method is called the opponents in the owner's sensory 
	//memory are examined and the closest  is assigned to m_pCurrentTarget.
	//if there are no opponents that have had their memory records updated
	//within the memory span of the owner then the current target is set
	//to null
	void       Update();

	//*HU Check if a bot is within the range of the weapon and can be killed in one shot
	bool		CanBeKilledInAShot(AbstRaven_Bot* bot);
	void		setTarget(AbstRaven_Bot* bot);
};

#endif
