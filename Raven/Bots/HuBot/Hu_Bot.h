#ifndef Hu_BOT_H
#define Hu_BOT_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Hu_Bot.h
//
//  Author: Robin Burke
//
//  Desc:
//-----------------------------------------------------------------------------
#include <vector>
#include <iosfwd>
#include <map>

#include "game/MovingEntity.h"
#include "misc/utils.h"
#include "Hu_TargetingSystem.h"
#include "../../AbstRaven_Bot.h"
#include "Hu_BotScriptor.h"


class Raven_PathPlanner;
class Raven_Steering;
class Raven_Game;
class Regulator;
class Raven_Weapon;
struct Telegram;
class Raven_Bot;
class Goal_Think;
class Raven_WeaponSystem;
class Raven_SensoryMemory;




class Hu_Bot : public AbstRaven_Bot
{
protected:
	//bots shouldn't be copied, only created or respawned
  Hu_Bot(const Hu_Bot&);
  Hu_Bot& operator=(const Hu_Bot&);
  Hu_BotScriptor* m_pScript;

public:
  
  Hu_Bot(Raven_Game* world, Vector2D pos);
  virtual ~Hu_Bot();

  //the usual suspects
  std::string  const GetName() const;
  void         DoUpdate();
  bool         HandleMessage(const Telegram& msg);

  void			SelectBodyPen();
  void			SelectHeadPen();

  bool canDodgeRight(Vector2D& PositionToDodge, Vector2D destination)const;
  bool canDodgeLeft(Vector2D& PositionToDodge, Vector2D destination)const;
};

#endif