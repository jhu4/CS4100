#pragma warning (disable:4786)
#ifndef HUHuFIELDPLAYER_H
#define HUHuFIELDPLAYER_H
//------------------------------------------------------------------------
//
//  Name:   HuFieldPlayer.h
//
//  Desc:   Derived from a PlayerBase, this class encapsulates a player
//          capable of moving around a soccer pitch, kicking, dribbling,
//          shooting etc
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

//#include "HuFieldPlayerStates.h"
#include "2D/Vector2D.h"
#include "FSM/StateMachine.h"
#include "../../PlayerBase.h"
#include "FSM/StateMachine.h"
#include "time/Regulator.h"

class CSteeringBehavior;
class AbstSoccerTeam;
class SoccerPitch;
class Goal;
struct Telegram;


class HuFieldPlayer : public PlayerBase
{
private:

   //an instance of the state machine class
  StateMachine<HuFieldPlayer>*  m_pStateMachine;
  
  //limits the number of kicks a player may take per second
  Regulator*                  m_pKickLimiter;

  
public:

  HuFieldPlayer(AbstSoccerTeam*    home_team,
             int        home_region,
             State<HuFieldPlayer>* start_state,
			 State<HuFieldPlayer>* global_state,
             Vector2D  heading,
             Vector2D      velocity,
             double         mass,
             double         max_force,
             double         max_speed,
             double         max_turn_rate,
             double         scale,
             player_role    role);   
  
  ~HuFieldPlayer();

  //call this to update the player's position and orientation
  void        Update();   

  void        Render();

  bool        HandleMessage(const Telegram& msg);

  StateMachine<HuFieldPlayer>* GetFSM()const{return m_pStateMachine;}

  bool        isReadyForNextKick()const{return m_pKickLimiter->isReady();}

         
};




#endif