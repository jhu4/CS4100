#ifndef HU_RAVEN_SENSORY_SYSTEM_H
#define HU_RAVEN_SENSORY_SYSTEM_H
#pragma warning (disable:4786)

#include <map>
#include <list>
#include <vector>
#include "2d/vector2d.h"
#include "../../Raven_SensoryMemory.h"

class AbstRaven_Bot;

//*HU helper records
class AttackerRecord {

public:
	bool isShootable;
	bool isWithinFOV;
	int damageMade;
	double health;
	double strength;

	AttackerRecord():isShootable(false)
		, isWithinFOV(false)
		, damageMade(0)
		, health(0)
		, strength(0){}

	AttackerRecord(bool shootable,bool inFOV, int dmg, double heal, double str):isShootable(shootable)
		,isWithinFOV(inFOV)
		,damageMade(dmg)
		,health(heal)
		,strength(str){}
};

//*HU
class Hu_Raven_SensoryMemory:public Raven_SensoryMemory
{
private:
	typedef std::map<AbstRaven_Bot*, AttackerRecord> AttackerMap;
	
	AttackerMap attackermap;
	AbstRaven_Bot* lastAttack;
	AbstRaven_Bot* me;
	std::vector<AbstRaven_Bot*> enemiesInFOV;
	double enemiesHealth;
	double enemiesStrength;

public: 
	Hu_Raven_SensoryMemory(AbstRaven_Bot* owner, double MemorySpan):Raven_SensoryMemory(owner,MemorySpan)
		,me(owner)
		,enemiesHealth(0)
		,enemiesStrength(0){}

//*HU added
	int NumberBotInFOV();
	double getHealthOfEnemiesInFOV();
	double getStrengthOfEnemiesInFOV();
	void updateAttackerMap();
	void recordAttackSource(AbstRaven_Bot* enemy);
	AbstRaven_Bot* lowestHealthAttacker();
	int getAttackerNum();
	AbstRaven_Bot* getLastAttack();
};


#endif