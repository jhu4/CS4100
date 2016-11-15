#include "BurkeSoccerTeam.h"
#include "BurkeTeamStates.h"
#include "../../SoccerPitch.h"
#include "../../Goal.h"
#include "../../ParamLoader.h"
#include "FSM/StateMachine.h"
#include "../../Goalkeeper.h"
#include "../BucklandTeam/GoalKeeperStates.h"
#include "../../FieldPlayer.h"
#include "../../SteeringBehaviors.h"
#include "BurkePlayerStates.h"


//----------------------------- ctor -------------------------------------
//
//------------------------------------------------------------------------
BurkeSoccerTeam::BurkeSoccerTeam(Goal*        home_goal,
                       Goal*        opponents_goal,
                       SoccerPitch* pitch,
                       team_color   color):
	AbstSoccerTeam(home_goal, opponents_goal, pitch, color)

{
  InitStateMachine ();
  	InitStateMachine();
	CreatePlayers();
	RegisterPlayers();
	InitPlayers();    

  //create the sweet spot calculator
  m_pSupportSpotCalc = new SupportSpotCalculator(Prm.NumSupportSpotsX,
                                                 Prm.NumSupportSpotsY,
                                                 this);
}

void BurkeSoccerTeam::InitStateMachine ()
{
  m_pStateMachine = new StateMachine<AbstSoccerTeam>(this);

  m_pStateMachine->SetCurrentState(BurkeDefending::Instance());
  m_pStateMachine->SetPreviousState(BurkeDefending::Instance());
  m_pStateMachine->SetGlobalState(NULL);
}

//------------------------- CreatePlayers --------------------------------
//
//  creates the players
//------------------------------------------------------------------------
void BurkeSoccerTeam::CreatePlayers()
{
  if (Color() == blue)
  {
    //goalkeeper
    m_Players.push_back(new GoalKeeper(this,
                               1,
                               TendGoal::Instance(),
                               GlobalKeeperState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale));
 
    //create the players
    m_Players.push_back(new FieldPlayer(this,
                               4,
                               BurkeWait::Instance(),
							   BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));



        m_Players.push_back(new FieldPlayer(this,
                               8,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));


 


        m_Players.push_back(new FieldPlayer(this,
                               7,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::defender));


        m_Players.push_back(new FieldPlayer(this,
                               6,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                              PlayerBase::defender));

  }

  else
  {

     //goalkeeper
    m_Players.push_back(new GoalKeeper(this,
                               16,
                               TendGoal::Instance(),
                               GlobalKeeperState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale));


    //create the players
    m_Players.push_back(new FieldPlayer(this,
                               13,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));

    m_Players.push_back(new FieldPlayer(this,
                               11,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));


 
    m_Players.push_back(new FieldPlayer(this,
                               10,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::defender));


    m_Players.push_back(new FieldPlayer(this,
                               9,
                               BurkeWait::Instance(),
                               BurkeGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::defender));
                      
  }
}

void BurkeSoccerTeam::InitPlayers()
{
  //set default steering behaviors
  std::vector<PlayerBase*>::iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    (*it)->Steering()->SeparationOn();   
  }
}

void BurkeSoccerTeam::prepareForKickoff ()
{
	GetFSM()->ChangeState(BurkePrepareForKickOff::Instance());
}


//----------------------- isPassSafeFromOpponent -------------------------
//
//  test if a dribble in direction dir can be intercepted by an opposing
//  player
//------------------------------------------------------------------------
bool BurkeSoccerTeam::isDribbleSafeFromOpponent(Vector2D    from,
                                        Vector2D    dir,
                                        const PlayerBase* const opp,
                                        double       kickingForce)const
{
  //move the opponent into local space.
  Vector2D DirNormalized = Vec2DNormalize(dir);

  Vector2D LocalPosOpp = PointToLocalSpace(opp->Pos(),
                                         DirNormalized,
                                         DirNormalized.Perp(),
                                         from);

  //if opponent is behind the kicker then pass is considered okay(this is 
  //based on the assumption that the ball is going to be kicked with a 
  //velocity greater than the opponent's max velocity)
  if ( LocalPosOpp.x < 0 )
  {     
    return true;
  }
  
  // how far the ball will go is a function of its speed and frictional slow-down
  // v = dir * force / mass
  // assume only friction. assume ball comes to a stop.
  // delta_x = v^2 / 2 * friction
  double kickVelocitySq = kickingForce / Prm.BallMass;
  Vector2D destination = DirNormalized * (kickVelocitySq / (2 * Prm.Friction));

  //if the opponent is further away than the target we need to consider if
  //the opponent can reach the position before the receiver.
  if (Vec2DDistanceSq(from, destination) < Vec2DDistanceSq(opp->Pos(), from))
  {
      if ( Vec2DDistanceSq(destination, opp->Pos())  > 
           Vec2DDistanceSq(destination, from) )
      {
        return true;
      }

      else
      {
        return false;
      } 
  }
  
  //calculate how long it takes the ball to cover the distance to the 
  //position orthogonal to the opponents position
  double TimeForBall = 
  Pitch()->Ball()->TimeToCoverDistance(Vector2D(0,0),
                                       Vector2D(LocalPosOpp.x, 0),
                                       kickingForce);

  //now calculate how far the opponent can run in this time
  double reach = opp->MaxSpeed() * TimeForBall +
                Pitch()->Ball()->BRadius()+
                opp->BRadius();

  //if the distance to the opponent's y position is less than his running
  //range plus the radius of the ball and the opponents radius then the
  //ball can be intercepted
  if ( fabs(LocalPosOpp.y) < reach )
  {
    return false;
  }

  return true;
}

//---------------------- isPassSafeFromAllOpponents ----------------------
//
//  tests a pass from position 'from' to position 'target' against each member
//  of the opposing team. Returns true if the pass can be made without
//  getting intercepted
//------------------------------------------------------------------------
bool BurkeSoccerTeam::isDribbleSafeFromAllOpponents(Vector2D                from,
                                            Vector2D                dir,
                                            double     kickingForce)const
{
  std::vector<PlayerBase*>::const_iterator opp = Opponents()->Members().begin();

  for (opp; opp != Opponents()->Members().end(); ++opp)
  {
    if (!isDribbleSafeFromOpponent(from, dir, *opp, kickingForce))
	{
        
      return false;
    }
  }

  return true;
}
//---------------------- UpdateTargetsOfWaitingPlayers ------------------------
//
//  
void BurkeSoccerTeam::UpdateTargetsOfWaitingPlayers()const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {  
    if ( (*it)->Role() != PlayerBase::goal_keeper )
    {
      //cast to a field player
      FieldPlayer* plyr = static_cast<FieldPlayer*>(*it);
      
      if ( plyr->GetFSM()->isInState(*BurkeWait::Instance()) ||
           plyr->GetFSM()->isInState(*BurkeReturnToHomeRegion::Instance()) )
      {
        plyr->Steering()->SetTarget(plyr->HomeRegion()->Center());
      }
    }
  }
}