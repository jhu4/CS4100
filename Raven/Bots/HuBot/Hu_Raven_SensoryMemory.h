#ifndef HU_RAVEN_SENSORY_SYSTEM_H
#define HU_RAVEN_SENSORY_SYSTEM_H
#pragma warning (disable:4786)

#include <map>
#include <list>
#include "2d/vector2d.h"
#include "../../Raven_SensoryMemory.h"

class AbstRaven_Bot;

class Hu_Raven_SensoryMemory
{

private:

	typedef std::map<AbstRaven_Bot*, MemoryRecord> MemoryMap;

protected:

	//the owner of this instance
	AbstRaven_Bot* m_pOwner;

	//this container is used to simulate memory of sensory events. A MemoryRecord
	//is created for each opponent in the environment. Each record is updated 
	//whenever the opponent is encountered. (when it is seen or heard)
	MemoryMap  m_MemoryMap;

	//a bot has a memory span equivalent to this value. When a bot requests a 
	//list of all recently sensed opponents this value is used to determine if 
	//the bot is able to remember an opponent or not.
	double      m_dMemorySpan;


	int botInFOV;

	//this methods checks to see if there is an existing record for pBot. If
	//not a new MemoryRecord record is made and added to the memory map.(called
	//by UpdateWithSoundSource & UpdateVision)
	void       MakeNewRecordIfNotAlreadyPresent(AbstRaven_Bot* pBot);

	
public:
	Hu_Raven_SensoryMemory(AbstRaven_Bot* owner, double MemorySpan);

	//this method is used to update the memory map whenever an opponent makes
	//a noise
	void     UpdateWithSoundSource(AbstRaven_Bot* pNoiseMaker);

	// *** added for lab
	void     UpdateWithDamageSource(AbstRaven_Bot* pShooter, int damage);

	//this removes a bot's record from memory
	void     RemoveBotFromMemory(AbstRaven_Bot* pBot);

	//this method iterates through all the opponents in the game world and 
	//updates the records of those that are in the owner's FOV
	void     UpdateVision();

	bool     isOpponentShootable(AbstRaven_Bot* pOpponent)const;
	bool     isOpponentWithinFOV(AbstRaven_Bot* pOpponent)const;
	Vector2D GetLastRecordedPositionOfOpponent(AbstRaven_Bot* pOpponent)const;
	double    GetTimeOpponentHasBeenVisible(AbstRaven_Bot* pOpponent)const;
	double    GetTimeSinceLastSensed(AbstRaven_Bot* pOpponent)const;
	double    GetTimeOpponentHasBeenOutOfView(AbstRaven_Bot* pOpponent)const;
	int		GetDamage(AbstRaven_Bot* pOpponent)const;
	bool      isUnderAttack() const;

	//this method returns a list of all the opponents that have had their
	//records updated within the last m_dMemorySpan seconds.
	std::list<AbstRaven_Bot*> GetListOfRecentlySensedOpponents()const;

	void     RenderBoxesAroundRecentlySensed()const;

//*HU added
	int NumberBotInFOV();
};


#endif