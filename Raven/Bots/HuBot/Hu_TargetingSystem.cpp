#include "Hu_TargetingSystem.h"
#include "Hu_Bot.h"
#include "Hu_BotScriptor.h"

#include "../../lua/Raven_Scriptor.h"
#include "../../AbstRaven_Bot.h"
#include "Hu_Raven_SensoryMemory.h"
#include "../../AbstWeaponSystem.h"
#include "../../armory/Raven_Weapon.h"
#include "../../Raven_ObjectEnumerations.h"
#include "Debug\DebugConsole.h"
//#include "../../Debug/DebugConsole.h"

//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Hu_TargetingSystem::Hu_TargetingSystem(AbstRaven_Bot* owner):
	AbstTargetingSystem(owner)
{}



//----------------------------- Update ----------------------------------------
// Differs from Buckland's only that we use the "Bully" tactic: target whichever
// bot is weakest (when we have a choice.)
//-----------------------------------------------------------------------------
void Hu_TargetingSystem::Update()
{
  int LowestHealthSoFar = MaxInt;
  m_pCurrentTarget       = 0;

  //grab a list of all the opponents the owner can sense
  std::list<AbstRaven_Bot*> SensedBots;
  SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();
  
  std::list<AbstRaven_Bot*>::const_iterator curBot = SensedBots.begin();
  for (curBot; curBot != SensedBots.end(); ++curBot)
  {
    //make sure the bot is alive and that it is not the owner
    if ((*curBot)->isAlive() && (*curBot != m_pOwner) )
    {
      
		//*HU
		if (CanBeKilledInAShot(*curBot)) {
			m_pCurrentTarget = *curBot;
			return;
		}

		//*HU
		//if (m_pOwner->GetSensoryMem()->isUnderAttack()) {
		//	m_pCurrentTarget = ((Hu_Raven_SensoryMemory*)m_pOwner->GetSensoryMem())->lowestHealthAttacker();
		//}
		//double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());
		int health = (*curBot)->Health();

      if (health < LowestHealthSoFar)
      {
        LowestHealthSoFar = health;
        m_pCurrentTarget = *curBot;
      }
    }
  }
}

//*HU
bool Hu_TargetingSystem::CanBeKilledInAShot(AbstRaven_Bot* bot) {
	int bot_health = bot->Health();
	Raven_Weapon* weapon = m_pOwner->GetWeaponSys()->GetCurrentWeapon();
	
	double dist = ((Hu_Bot*)m_pOwner)->GetDistanceToBot(bot);
	double range = weapon->GetIdealRange();

	

	if(dist<=range){
		switch(weapon->GetType()){
			case	type_rail_gun:
				if (bot_health <= script->GetDouble("Slug_Damage")) {
					debug_con << "Dist: " << dist << "Range:" << range << " Weapon dmg:"<< script->GetDouble("Slug_Damage") << "";
					debug_con << "One shot Killing " << bot->GetName() << " with Railgun" << "";
					return true;
				}
				break;
			case	type_rocket_launcher:
				if (bot_health <= script->GetDouble("Rocket_Damage")) {
					debug_con << "Dist: " << dist << " Range:" << range << " Weapon dmg:" << script->GetDouble("Rocket_Damage") << "";
					debug_con << "One shot Killing " << bot->GetName() << " with Rocket Launcher" << "";
					return true;
				}
				break;
			case	type_shotgun:
				if (bot_health <= script->GetDouble("Pellet_Damage")) {
					debug_con << "Dist: " << dist << " Range:" << range << " Weapon dmg:" << script->GetDouble("Pellet_Damage") << "";
					debug_con << "One shot Killing " << bot->GetName() << " with Shot gun" << "";
					return true;
				}
				break;
			case	type_blaster:
				if (bot_health <= script->GetDouble("Bolt_Damage")) {
					debug_con << "Dist: " << dist << " Range:" << range << " Weapon dmg:" << script->GetDouble("Bolt_Damage") << "";
					debug_con << "One shot Killing " << bot->GetName() << " with Blaster" << "";
					return true;
				}
				break;
			default:
				break;
		}
	}

	return false;
}

//*HU
void Hu_TargetingSystem::setTarget(AbstRaven_Bot* bot) {
	m_pCurrentTarget = bot;
}