#include "Hu_Raven_SensoryMemory.h"
#include "../../AbstRaven_Bot.h"
#include "../../Raven_Game.h"
#include "../../goals/Raven_Feature.h"
#include "time/crudetimer.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Debug\DebugConsole.h"
#include <vector>

//*HU get the number of the bot in the view of sight and update other variables
int Hu_Raven_SensoryMemory::NumberBotInFOV() {
	enemiesInFOV = me->GetWorld()->GetAllBotsInFOV(me);

	debug_con << "enemiesInFOV:" << enemiesInFOV.size() << "";

	return enemiesInFOV.size();
}

double Hu_Raven_SensoryMemory::getHealthOfEnemiesInFOV() {
	enemiesHealth = 0;
	std::vector<AbstRaven_Bot*>::iterator it;
	for (it = enemiesInFOV.begin(); it != enemiesInFOV.end(); it++) {
		AbstRaven_Bot* bot = static_cast<AbstRaven_Bot*> (*it);
		enemiesHealth += Raven_Feature::Health((AbstRaven_Bot*)(bot));
	}
	return enemiesHealth;
}

double Hu_Raven_SensoryMemory::getStrengthOfEnemiesInFOV() {
	enemiesStrength = 0;
	std::vector<AbstRaven_Bot*>::iterator it;
	for (it = enemiesInFOV.begin(); it != enemiesInFOV.end(); it++) {
		AbstRaven_Bot* bot = static_cast<AbstRaven_Bot*> (*it);
		enemiesStrength += Raven_Feature::TotalWeaponStrength(bot);
	}
	return enemiesStrength;
}


//*HU update the attackermap in a frequency, kick out the dead attacker
void Hu_Raven_SensoryMemory::updateAttackerMap() {
	AttackerMap::iterator it;


	for (it = attackermap.begin(); it != attackermap.end(); it++) {

		//if the bot is dead
		if (it->first->isDead()) {
			attackermap.erase(it->first);
		}
	}
}

//*HU record the dmg source
void Hu_Raven_SensoryMemory::recordAttackSource(AbstRaven_Bot* enemy) {
	
	//if attacker is alive 	
	if (me!=enemy && enemy->isAlive()) {
		AttackerMap::iterator record = attackermap.find(enemy);

		//if it doesn't exist, make a new record
		if (record == attackermap.end())
		{
			attackermap[enemy] = AttackerRecord(isOpponentShootable(enemy)
				, isOpponentWithinFOV(enemy)
				, GetDamage(enemy)
				, Raven_Feature::Health(enemy)
				, Raven_Feature::TotalWeaponStrength(enemy));
		}
		else {//update the record
			attackermap[enemy].damageMade = GetDamage(enemy);
			attackermap[enemy].health = Raven_Feature::Health(enemy);
			attackermap[enemy].strength = Raven_Feature::TotalWeaponStrength(enemy);
			attackermap[enemy].isWithinFOV = isOpponentWithinFOV(enemy);
			attackermap[enemy].isShootable = isOpponentShootable(enemy);
		}

		debug_con << "Add DMG source" << "";

	}
}

//*HU find the lowest health attack in the attacker map
AbstRaven_Bot* Hu_Raven_SensoryMemory::lowestHealthAttacker() {
	AttackerMap::iterator it;
	double health = MaxDouble;
	AbstRaven_Bot* bot;
	for (it = attackermap.begin(); it != attackermap.end(); it++) {
		//if the bot is dead
		if (it->first->isDead()) {
			attackermap.erase(it->first);
		}
		if (it->second.health <= health) {
			health = it->second.health;
			bot = (AbstRaven_Bot*)it->first;
		}
	}
	debug_con << "Lowest health bot:" << bot->GetName() << "";
	return bot;
}

//*HU get the number of attacker
int Hu_Raven_SensoryMemory::getAttackerNum() {
	return attackermap.size();
}

//*HU get the latest attacker
AbstRaven_Bot* Hu_Raven_SensoryMemory::getLastAttack() {
	return attackermap.end()->first;
}