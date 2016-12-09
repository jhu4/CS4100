#ifndef HU_RAVEN_SENSORY_SYSTEM_H
#define HU_RAVEN_SENSORY_SYSTEM_H
#pragma warning (disable:4786)

#include <map>
#include <list>
#include "2d/vector2d.h"
#include "../../Raven_SensoryMemory.h"

class AbstRaven_Bot;

class Hu_Raven_SensoryMemory:public Raven_SensoryMemory
{

public: 
	Hu_Raven_SensoryMemory(AbstRaven_Bot* owner, double MemorySpan):Raven_SensoryMemory(owner,MemorySpan){}

//*HU added
	int NumberBotInFOV();
};


#endif