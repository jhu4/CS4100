#include "HuSoccerTeam.h"
#include "HuTeamStates.h"
#include "HuFieldPlayer.h"
#include "HuGoalKeeperStates.h"

#include "../../SoccerPitch.h"
#include "../../Goal.h"
#include "../../ParamLoader.h"
#include "FSM/StateMachine.h"
#include "../../Goalkeeper.h"
#include "../../SteeringBehaviors.h"
#include "HuPlayerStates.h"
#include "Debug/DebugConsole.h"

//----------------------------- ctor -------------------------------------
//
//------------------------------------------------------------------------
HuSoccerTeam::HuSoccerTeam(Goal*        home_goal,
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

void HuSoccerTeam::InitStateMachine ()
{
  m_pStateMachine = new StateMachine<AbstSoccerTeam>(this);

  m_pStateMachine->SetCurrentState(HuDefending::Instance());
  m_pStateMachine->SetPreviousState(HuDefending::Instance());
  m_pStateMachine->SetGlobalState(NULL);
}

//------------------------- CreatePlayers --------------------------------
//
//  creates the players
//------------------------------------------------------------------------
void HuSoccerTeam::CreatePlayers()
{
  if (Color() == blue)
  {
    //Hugoalkeeper
    m_Players.push_back(new GoalKeeper(this,
                               1,
                               HuTendGoal::Instance(),
                               HuGlobalKeeperState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale));
 
    //create the players
    m_Players.push_back(new HuFieldPlayer(this,
                               4,
                               HuWait::Instance(),
							   HuGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));



        m_Players.push_back(new HuFieldPlayer(this,
                               8,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));


 


        m_Players.push_back(new HuFieldPlayer(this,
                               7,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
                               Vector2D(0,1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::defender));


        m_Players.push_back(new HuFieldPlayer(this,
                               6,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
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

     //Hugoalkeeper
    m_Players.push_back(new GoalKeeper(this,
                               16,
                               HuTendGoal::Instance(),
                               HuGlobalKeeperState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale));


    //create the players
    m_Players.push_back(new HuFieldPlayer(this,
                               13,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));

    m_Players.push_back(new HuFieldPlayer(this,
                               11,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::attacker));


 
    m_Players.push_back(new HuFieldPlayer(this,
                               10,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
                               Vector2D(0,-1),
                               Vector2D(0.0, 0.0),
                               Prm.PlayerMass,
                               Prm.PlayerMaxForce,
                               Prm.PlayerMaxSpeedWithoutBall,
                               Prm.PlayerMaxTurnRate,
                               Prm.PlayerScale,
                               PlayerBase::defender));


    m_Players.push_back(new HuFieldPlayer(this,
                               9,
                               HuWait::Instance(),
                               HuGlobalPlayerState::Instance(),
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

void HuSoccerTeam::InitPlayers()
{
  //set default steering behaviors
  std::vector<PlayerBase*>::iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {
    (*it)->Steering()->SeparationOn();   
  }
}

void HuSoccerTeam::prepareForKickoff ()
{
	GetFSM()->ChangeState(HuPrepareForKickOff::Instance());
}


//----------------------- isPassSafeFromOpponent -------------------------
//
//  test if a dribble in direction dir can be intercepted by an opposing
//  player
//------------------------------------------------------------------------
bool HuSoccerTeam::isDribbleSafeFromOpponent(Vector2D    from,
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
bool HuSoccerTeam::isDribbleSafeFromAllOpponents(Vector2D                from,
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
void HuSoccerTeam::UpdateTargetsOfWaitingPlayers()const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {  
    if ( (*it)->Role() != PlayerBase::goal_keeper )
    {
      //cast to a field player
      FieldPlayer* plyr = static_cast<FieldPlayer*>(*it);
      
      if ( plyr->GetFSM()->isInState(*HuWait::Instance()) ||
           plyr->GetFSM()->isInState(*HuReturnToHomeRegion::Instance()) )
      {
        plyr->Steering()->SetTarget(plyr->HomeRegion()->Center());
      }
    }
  }
}


//*-----------------------Hu Added Functions------------------------------------
bool HuSoccerTeam::isBallInOurHalf() {
	Vector2D ballpos=Pitch()->m_pBall->Pos();
	double pitchWidth=Pitch()->PlayingArea()->Width();
	
	double scale = 0.5;
	
	if (ballpos.x-(scale*pitchWidth)>0 && Color() == AbstSoccerTeam::blue) { 
		return true;
	}
	else if(ballpos.x-(scale*pitchWidth)<0 && Color() == AbstSoccerTeam::red) {
		return true;
	}
	else {
		return false;
	}
}

PlayerBase* HuSoccerTeam::DetermineBestGuarder() {
	debug_con << "HuSoccerTeam::DetermineBestGuarder()" << "";

	double ClosestSoFar = MaxFloat;

	PlayerBase* BestPlayer = NULL;

	std::vector<PlayerBase*>::iterator it = m_Players.begin();

	for (it; it != m_Players.end(); ++it)
	{

		//only defenders can be a guarder
		if (((*it)->Role() == PlayerBase::defender) && ((*it) != m_pControllingPlayer))
		{
			
			//calculate the dist. Use the squared value to avoid sqrt
			double dist = ((*it))->DistToHomeGoal();

			//if the distance is the closest so far and the player is not a
			//goalkeeper and the player is not the one currently controlling
			//the ball, keep a record of this player
			if ((dist < ClosestSoFar))
			{
				ClosestSoFar = dist;

				BestPlayer = (*it);
			}
		}
	}

	return BestPlayer;

}
PlayerBase* HuSoccerTeam::DetermineBestDefensiveAttacker() {
	debug_con << "HuSoccerTeam::DetermineBestDefensiveAttacker()" << "";
	double ClosestSoFar = MaxFloat;

	PlayerBase* BestPlayer = NULL;

	std::vector<PlayerBase*>::iterator it = m_Players.begin();

	for (it; it != m_Players.end(); ++it)
	{

		//only defenders can be a defensive attacker
		if (((*it)->Role() == PlayerBase::defender) && ((*it) != m_pControllingPlayer))
		{
			
			//calculate the dist btw a defender and the opponent controlling player
			double dist = Vec2DDistanceSq((*it)->Pos(), Opponents()->ControllingPlayer()->Pos());

			//if the distance is the closest so far and the player is not a
			//goalkeeper and the player is not the one currently controlling
			//the ball, keep a record of this player
			if ((dist < ClosestSoFar))
			{
				ClosestSoFar = dist;

				BestPlayer = (*it);
			}
		}
	}

	return BestPlayer;
}


PlayerBase* HuSoccerTeam::DetermineBestDefender() {
	debug_con << "HuSoccerTeam::DetermineBestDefender()" << "";
	double ClosestSoFar = MaxFloat;

	PlayerBase* BestPlayer = NULL;

	std::vector<PlayerBase*>::iterator it = m_Players.begin();

	for (it; it != m_Players.end(); ++it)
	{

		if (((*it)->Role() == PlayerBase::defender) && ((*it) != m_pControllingPlayer))
		{

			//calculate the dist btw a defender and the opponent Supporting Player
			double dist = Vec2DDistanceSq((*it)->Pos(), Opponents()->SupportingPlayer()->Pos());

			//if the distance is the closest so far and the player is not a
			//goalkeeper and the player is not the one currently controlling
			//the ball, keep a record of this player
			if ((dist < ClosestSoFar))
			{
				ClosestSoFar = dist;

				BestPlayer = (*it);
			}
		}
	}

	return BestPlayer;
}