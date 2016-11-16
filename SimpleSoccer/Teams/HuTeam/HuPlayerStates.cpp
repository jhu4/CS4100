#include "HuPlayerStates.h"
#include "HuSoccerTeam.h"
#include "HuSoccerMessages.h"

#include "Debug/DebugConsole.h"
#include "../../SoccerPitch.h"
#include "../../FieldPlayer.h"
#include "../../SteeringBehaviors.h"
#include "../../AbstSoccerTeam.h"
#include "../../Goal.h"
#include "2D/geometry.h"
#include "../../SoccerBall.h"
#include "../../ParamLoader.h"
#include "Messaging/Telegram.h"
#include "Messaging/MessageDispatcher.h"


#include "time/Regulator.h"


//uncomment below to send state info to the debug window
//#define HUPLAYER_STATE_INFO_ON
#define HUSTRATEGYIC_STATE_INFO_ON
#define HU_INTERPOSE_DIST 100
//************************************************************************ Global state

HuGlobalPlayerState* HuGlobalPlayerState::Instance()
{
  static HuGlobalPlayerState instance;

  return &instance;
}


void HuGlobalPlayerState::Execute(FieldPlayer* player)                                     
{
  //if a player is in possession and close to the ball reduce his max speed
  if((player->BallWithinReceivingRange()) && (player->isControllingPlayer()))
  {
    player->SetMaxSpeed(Prm.PlayerMaxSpeedWithBall);
  }

  else
  {
     player->SetMaxSpeed(Prm.PlayerMaxSpeedWithoutBall);
  }
    
}


bool HuGlobalPlayerState::OnMessage(FieldPlayer* player, const Telegram& telegram)
{
  switch(telegram.Msg)
  {
  case Msg_ReceiveBall:
    {
      //set the target
      player->Steering()->SetTarget(*(static_cast<Vector2D*>(telegram.ExtraInfo)));

      //change state 
      player->GetFSM()->ChangeState(HuReceiveBall::Instance());

      return true;
    }

    break;

  case Msg_SupportAttacker:
    {
		#ifdef HUSTRATEGYIC_STATE_INFO_ON
				debug_con << "Player " << player->ID() << " received Msg " <<" SupportAttacker" << "";
		#endif
      //if already supporting just return
      if (player->GetFSM()->isInState(*HuSupportAttacker::Instance()))
      {
        return true;
      }
      
      //set the target to be the best supporting position
      player->Steering()->SetTarget(player->Team()->GetSupportSpot());

      //change the state
      player->GetFSM()->ChangeState(HuSupportAttacker::Instance());

      return true;
    }

    break;

  case Msg_DefensiveAttacker:
  {
#ifdef HUSTRATEGYIC_STATE_INFO_ON
	  debug_con << "Player " << player->ID() << " received Msg " << " DefensiveAttacker" << "";
#endif
	  //if already supporting just return
	  if (player->GetFSM()->isInState(*HuDefensiveAttacker::Instance()))
	  {
		  return true;
	  }

	  //change the state
	  player->GetFSM()->ChangeState(HuDefensiveAttacker::Instance());

	  return true;
  }

  break;

  case Msg_Guarder:
  {
#ifdef HUSTRATEGYIC_STATE_INFO_ON
	  debug_con << "Player " << player->ID() << " received Msg " << " Guarder" << "";
#endif
	  //if already supporting just return
	  if (player->GetFSM()->isInState(*HuGuarder::Instance()))
	  {
		  return true;
	  }

	  //change the state
	  player->GetFSM()->ChangeState(HuGuarder::Instance());

	  return true;
  }

  break;

 case Msg_Wait:
    {
      //change the state
      player->GetFSM()->ChangeState(HuWait::Instance());

      return true;
    }

    break;

  case Msg_GoHome:
    {
      player->SetDefaultHomeRegion();
      
      player->GetFSM()->ChangeState(HuReturnToHomeRegion::Instance());

      return true;
    }

    break;

  case Msg_PassToMe:
    {  
      
      //get the position of the player requesting the pass 
      FieldPlayer* receiver = static_cast<FieldPlayer*>(telegram.ExtraInfo);

      #ifdef HUSTRATEGYIC_STATE_INFO_ON
      debug_con << "Player " << player->ID() << " received request from " <<
                    receiver->ID() << " to make pass" << "";
      #endif

      //if the ball is not within kicking range or their is already a 
      //receiving player, this player cannot pass the ball to the player
      //making the request.
      if (player->Team()->Receiver() != NULL ||
         !player->BallWithinKickingRange() )
      {
        #ifdef HUPLAYER_STATE_INFO_ON
        debug_con << "Player " << player->ID() << " cannot make requested pass <cannot kick ball>" << "";
        #endif

        return true;
      }
      
      //make the pass   
      player->Ball()->Kick(receiver->Pos() - player->Ball()->Pos(),
                           Prm.MaxPassingForce);

          
     #ifdef HUSTRATEGYIC_STATE_INFO_ON
     debug_con << "Player " << player->ID() << " Passed ball to requesting player" << "";
     #endif
        
      //let the receiver know a pass is coming 
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              player->ID(),
                              receiver->ID(),
                              Msg_ReceiveBall,
                              &receiver->Pos());

   

      //change state   
      player->GetFSM()->ChangeState(HuWait::Instance());

      player->FindSupport();

      return true;
    }

    break;

  }//end switch

  return false;
}
                                

       

//***************************************************************************** HuChaseBall

HuChaseBall* HuChaseBall::Instance()
{
  static HuChaseBall instance;

  return &instance;
}


void HuChaseBall::Enter(FieldPlayer* player)
{
  player->Steering()->SeekOn();

  #ifdef HUPLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters mychase state" << "";
  #endif
}

void HuChaseBall::Execute(FieldPlayer* player)                                     
{
  //if the ball is within kicking range the player changes state to HuKickBall.
  if (player->BallWithinKickingRange())
  {
    player->GetFSM()->ChangeState(HuKickBall::Instance());
    
    return;
  }
                                                                              
  //if the player is the closest player to the ball then he should keep
  //chasing it
  if (player->isClosestTeamMemberToBall())
  {
    player->Steering()->SetTarget(player->Ball()->Pos());

    return;
  }
  
  //if the player is not closest to the ball anymore, he should return back
  //to his home region and wait for another opportunity
  player->GetFSM()->ChangeState(HuReturnToHomeRegion::Instance());
}


void HuChaseBall::Exit(FieldPlayer* player)
{
  player->Steering()->SeekOff();
}



//*****************************************************************************SUPPORT ATTACKING PLAYER

HuSupportAttacker* HuSupportAttacker::Instance()
{
  static HuSupportAttacker instance;

  return &instance;
}


void HuSupportAttacker::Enter(FieldPlayer* player)
{
  player->Steering()->ArriveOn();

  player->Steering()->SetTarget(player->Team()->GetSupportSpot());
  
  #ifdef HUPLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters mysupport state" << "";
  #endif
}

void HuSupportAttacker::Execute(FieldPlayer* player)                                     
{
  //if his team loses control go back home
  if (!player->Team()->InControl())
  {
    player->GetFSM()->ChangeState(HuReturnToHomeRegion::Instance()); return;
  } 


  //if the best supporting spot changes, change the steering target
  if (player->Team()->GetSupportSpot() != player->Steering()->Target())
  {    
    player->Steering()->SetTarget(player->Team()->GetSupportSpot());

    player->Steering()->ArriveOn();
  }

  //if this player has a shot at the goal AND the attacker can pass
  //the ball to him the attacker should pass the ball to this player
  if( player->Team()->CanShoot(player->Pos(),
                               Prm.MaxShootingForce))
  {
    player->Team()->RequestPass(player);
  }


  //if this player is located at the support spot and his team still have
  //possession, he should remain still and turn to face the ball
  if (player->AtTarget())
  {
    player->Steering()->ArriveOff();
        
    //the player should keep his eyes on the ball!
    player->TrackBall();

    player->SetVelocity(Vector2D(0,0));

    //if not threatened by another player request a pass
    if (!player->isThreatened())
    {
      player->Team()->RequestPass(player);
    }
  }
}


void HuSupportAttacker::Exit(FieldPlayer* player)
{
  //set supporting player to null so that the team knows it has to 
  //determine a new one.
  player->Team()->SetSupportingPlayer(NULL);

  player->Steering()->ArriveOff();
}




//************************************************************************ RETURN TO HOME REGION

HuReturnToHomeRegion* HuReturnToHomeRegion::Instance()
{
  static HuReturnToHomeRegion instance;

  return &instance;
}


void HuReturnToHomeRegion::Enter(FieldPlayer* player)
{
  player->Steering()->ArriveOn();

  if (!player->HomeRegion()->Inside(player->Steering()->Target(), Region::halfsize))
  {
    player->Steering()->SetTarget(player->HomeRegion()->Center());
  }

  #ifdef HUPLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters myReturnToHome state" << "";
  #endif
}

void HuReturnToHomeRegion::Execute(FieldPlayer* player)
{
  if (player->Pitch()->GameOn())
  {
    //if the ball is nearer this player than any other team member  &&
    //there is not an assigned receiver && the goalkeeper does not gave
    //the ball, go chase it
    if ( player->isClosestTeamMemberToBall() &&
         (player->Team()->Receiver() == NULL) &&
         !player->Pitch()->GoalKeeperHasBall())
    {
      player->GetFSM()->ChangeState(HuChaseBall::Instance());

      return;
    }
  }

  //if game is on and close enough to home, change state to wait and set the 
  //player target to his current position.(so that if he gets jostled out of 
  //position he can move back to it)
  if (player->Pitch()->GameOn() && player->HomeRegion()->Inside(player->Pos(),
                                                             Region::halfsize))
  {
    player->Steering()->SetTarget(player->Pos());
    player->GetFSM()->ChangeState(HuWait::Instance());
  }
  //if game is not on the player must return much closer to the center of his
  //home region
  else if(!player->Pitch()->GameOn() && player->AtTarget())
  {
    player->GetFSM()->ChangeState(HuWait::Instance());
  }
}

void HuReturnToHomeRegion::Exit(FieldPlayer* player)
{
  player->Steering()->ArriveOff();
}




//***************************************************************************** WAIT

HuWait* HuWait::Instance()
{
  static HuWait instance;

  return &instance;
}


void HuWait::Enter(FieldPlayer* player)
{
  #ifdef HUPLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters mywait state" << "";
  #endif

  //if the game is not on make sure the target is the center of the player's
  //home region. This is ensure all the players are in the correct positions
  //ready for kick off
  if (!player->Pitch()->GameOn())
  {
    player->Steering()->SetTarget(player->HomeRegion()->Center());
  }
}

void HuWait::Execute(FieldPlayer* player)
{    
  //if the player has been jostled out of position, get back in position  
  if (!player->AtTarget())
  {
    player->Steering()->ArriveOn();

    return;
  }

  else
  {
    player->Steering()->ArriveOff();

    player->SetVelocity(Vector2D(0,0));

    //the player should keep his eyes on the ball!
    player->TrackBall();
  }

  //if this player's team is controlling AND this player is not the attacker
  //AND is further up the field than the attacker he should request a pass.
  if ( player->Team()->InControl()    &&
     (!player->isControllingPlayer()) &&
       player->isAheadOfAttacker() )
  {
    player->Team()->RequestPass(player);

    return;
  }

  if (player->Pitch()->GameOn())
  {
   //if the ball is nearer this player than any other team member  AND
    //there is not an assigned receiver AND neither goalkeeper has
    //the ball, go chase it
   if (player->isClosestTeamMemberToBall() &&
       player->Team()->Receiver() == NULL  &&
       !player->Pitch()->GoalKeeperHasBall())
   {
     player->GetFSM()->ChangeState(HuChaseBall::Instance());

     return;
   }
  } 
}

void HuWait::Exit(FieldPlayer* player){}




//************************************************************************ KICK BALL

HuKickBall* HuKickBall::Instance()
{
  static HuKickBall instance;

  return &instance;
}


void HuKickBall::Enter(FieldPlayer* player)
{
  //let the team know this player is controlling
   player->Team()->SetControllingPlayer(player);
   
   //the player can only make so many kick attempts per second.
   if (!player->isReadyForNextKick()) 
   {
     player->GetFSM()->ChangeState(HuChaseBall::Instance());
   }

   
  #ifdef HUPLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters mykick state" << "";
  #endif
}

void HuKickBall::Execute(FieldPlayer* player)
{ 
  //calculate the dot product of the vector pointing to the ball
  //and the player's heading
  Vector2D ToBall = player->Ball()->Pos() - player->Pos();
  double   dot    = player->Heading().Dot(Vec2DNormalize(ToBall)); 

  //cannot kick the ball if the goalkeeper is in possession or if it is 
  //behind the player or if there is already an assigned receiver. So just
  //continue chasing the ball
  if (player->Team()->Receiver() != NULL   ||
      player->Pitch()->GoalKeeperHasBall() ||
      (dot < 0) ) 
  {
    #ifdef HUPLAYER_STATE_INFO_ON
    debug_con << "Goaly has ball / ball behind player" << "";
    #endif
    
    player->GetFSM()->ChangeState(HuChaseBall::Instance());

    return;
  }

  /* Attempt a shot at the goal */

  //if a shot is possible, this vector will hold the position along the 
  //opponent's goal line the player should aim for.
  Vector2D    BallTarget;

  //the dot product is used to adjust the shooting force. The more
  //directly the ball is ahead, the more forceful the kick
  double power = Prm.MaxShootingForce * dot;

  //if it is determined that the player could score a goal from this position
  //OR if he should just kick the ball anyway, the player will attempt
  //to make the shot
  if (player->Team()->CanShoot(player->Ball()->Pos(),
                               power,
                               BallTarget)                   || 
     (RandFloat() < Prm.ChancePlayerAttemptsPotShot))
  {
   #ifdef HUPLAYER_STATE_INFO_ON
   debug_con << "Player " << player->ID() << " attempts a shot at " << BallTarget << "";
   #endif

   //add some noise to the kick. We don't want players who are 
   //too accurate! The amount of noise can be adjusted by altering
   //Prm.PlayerKickingAccuracy
   BallTarget = AddNoiseToKick(player->Ball()->Pos(), BallTarget);

   //this is the direction the ball will be kicked in
   Vector2D KickDirection = BallTarget - player->Ball()->Pos();
   
   player->Ball()->Kick(KickDirection, power);
    
   //change state   
   player->GetFSM()->ChangeState(HuWait::Instance());
   
   player->FindSupport();
  
   return;
 }


  /* Attempt a pass to a player */

  //if a receiver is found this will point to it
  PlayerBase* receiver = NULL;

  power = Prm.MaxPassingForce * dot;
  
  //test if there are any potential candidates available to receive a pass
  if (player->isThreatened()  &&
      player->Team()->FindPass(player,
                              receiver,
                              BallTarget,
                              power,
                              Prm.MinPassDist))
  {     
    //add some noise to the kick
    BallTarget = AddNoiseToKick(player->Ball()->Pos(), BallTarget);

    Vector2D KickDirection = BallTarget - player->Ball()->Pos();
   
    player->Ball()->Kick(KickDirection, power);

    #ifdef HUPLAYER_STATE_INFO_ON
    debug_con << "Player " << player->ID() << " passes the ball with force " << power << "  to player " 
              << receiver->ID() << "  Target is " << BallTarget << "";
    #endif

    
    //let the receiver know a pass is coming 
    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            player->ID(),
                            receiver->ID(),
                            Msg_ReceiveBall,
                            &BallTarget);                            
   

    //the player should wait at his current position unless instruced
    //otherwise  
    player->GetFSM()->ChangeState(HuWait::Instance());

    player->FindSupport();

    return;
  }

  //cannot shoot or pass, so dribble the ball upfield
  else
  {   
    player->FindSupport();

    player->GetFSM()->ChangeState(HuDribble::Instance());
  }   
}


//*************************************************************************** HuDribble

HuDribble* HuDribble::Instance()
{
  static HuDribble instance;

  return &instance;
}


void HuDribble::Enter(FieldPlayer* player)
{
  //let the team know this player is controlling
  player->Team()->SetControllingPlayer(player);

#ifdef HUPLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters mydribble state" << "";
  #endif
}

void HuDribble::Execute(FieldPlayer* player)
{
  double dot = player->Team()->HomeGoal()->Facing().Dot(player->Heading());

  //if the ball is between the player and the home goal, it needs to swivel
  // the ball around by doing multiple small kicks and turns until the player 
  //is facing in the correct direction
  if (dot < 0)
  {
    //the player's heading is going to be rotated by a small amount (Pi/4) 
    //and then the ball will be kicked in that direction
    Vector2D direction = player->Heading();

    //calculate the sign (+/-) of the angle between the player heading and the 
    //facing direction of the goal so that the player rotates around in the 
    //correct direction
    double angle = QuarterPi * -1 *
                 player->Team()->HomeGoal()->Facing().Sign(player->Heading());

    Vec2DRotateAroundOrigin(direction, angle);

    //this value works well whjen the player is attempting to control the
    //ball and turn at the same time
    const double KickingForce = 0.8;

    player->Ball()->Kick(direction, KickingForce);
  }
  // if there is clear space to dibble straight to goal, do so
  Vector2D dir = player->Team()->HomeGoal()->Facing();
  HuSoccerTeam* team = (HuSoccerTeam*) player->Team();
  if (team->isDribbleSafeFromAllOpponents(player->Pos(), dir, Prm.MaxDribbleForce))
  {
    player->Ball()->Kick(player->Team()->HomeGoal()->Facing(),
                         Prm.MaxDribbleForce);  
  } else
	  // otherwise, choose randomly left or right and dribble around
  {
		if (RandBool())
		{ Vec2DRotateAroundOrigin(dir, QuarterPi); }
		else
		{ Vec2DRotateAroundOrigin(dir, QuarterPi); }

		player->Ball()->Kick(player->Team()->HomeGoal()->Facing(),
                         Prm.MaxDribbleForce); 

  }

  //the player has kicked the ball so he must now change state to follow it
  player->GetFSM()->ChangeState(HuChaseBall::Instance());
    
  return;  
}



//************************************************************************     RECEIVEBALL

HuReceiveBall* HuReceiveBall::Instance()
{
  static HuReceiveBall instance;

  return &instance;
}


void HuReceiveBall::Enter(FieldPlayer* player)
{
  //let the team know this player is receiving the ball
  player->Team()->SetReceiver(player);
  
  //this player is also now the controlling player
  player->Team()->SetControllingPlayer(player);

  //there are two types of receive behavior. One uses arrive to direct
  //the receiver to the position sent by the passer in its telegram. The
  //other uses the pursuit behavior to pursue the ball. 
  //This statement selects between them dependent on the probability
  //ChanceOfUsingArriveTypeReceiveBehavior, whether or not an opposing
  //player is close to the receiving player, and whether or not the receiving
  //player is in the opponents 'hot region' (the third of the pitch closest
  //to the opponent's goal
  const double PassThreatRadius = 70.0;

  if (( player->InHotRegion() ||
        RandFloat() < Prm.ChanceOfUsingArriveTypeReceiveBehavior) &&
     !player->Team()->isOpponentWithinRadius(player->Pos(), PassThreatRadius))
  {
    player->Steering()->ArriveOn();
    
    #ifdef HUPLAYER_STATE_INFO_ON
    debug_con << "Player " << player->ID() << " enters myreceive state (Using Arrive)" << "";
    #endif
  }
  else
  {
    player->Steering()->PursuitOn();

    #ifdef HUPLAYER_STATE_INFO_ON
    debug_con << "Player " << player->ID() << " enters myreceive state (Using Pursuit)" << "";
    #endif
  }
}

void HuReceiveBall::Execute(FieldPlayer* player)
{
  //if the ball comes close enough to the player or if his team lose control
  //he should change state to chase the ball
  if (player->BallWithinReceivingRange() || !player->Team()->InControl())
  {
    player->GetFSM()->ChangeState(HuChaseBall::Instance());

    return;
  }  

  if (player->Steering()->PursuitIsOn())
  {
    player->Steering()->SetTarget(player->Ball()->Pos());
  }

  //if the player has 'arrived' at the steering target he should wait and
  //turn to face the ball
  if (player->AtTarget())
  {
    player->Steering()->ArriveOff();
    player->Steering()->PursuitOff();
    player->TrackBall();    
    player->SetVelocity(Vector2D(0,0));
  } 
}

void HuReceiveBall::Exit(FieldPlayer* player)
{
  player->Steering()->ArriveOff();
  player->Steering()->PursuitOff();

  player->Team()->SetReceiver(NULL);
}

//***********************************************************************************************

HuDefensiveAttacker* HuDefensiveAttacker::Instance()
{
	static HuDefensiveAttacker instance;

	return &instance;
}

void HuDefensiveAttacker::Enter(FieldPlayer* player) {
	player->Steering()->InterposeOn(HU_INTERPOSE_DIST);
	player->Steering()->SetTarget(player->Team()->Opponents()->PlayerClosestToBall()->Pos());
}

void HuDefensiveAttacker::Execute(FieldPlayer* player) {
	if (player->isClosestTeamMemberToBall()) {
		player->GetFSM()->ChangeState(HuChaseBall::Instance());
		
		//let the new defensive attacker to do its job!
		PlayerBase* newDefensivaAttacker = ((HuSoccerTeam*)player->Team())->DefensiveAttacker();
		if (newDefensivaAttacker != NULL) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				newDefensivaAttacker->ID(),
				newDefensivaAttacker->ID(),
				Msg_DefensiveAttacker,
				NULL);
		}
		return;
	}

	if (player->Team()->Opponents()->SupportingPlayer() != NULL) {
		player->Steering()->SetTarget(player->Team()->Opponents()->SupportingPlayer()->Pos());
	}
	else {
		player->Steering()->SetTarget(player->Team()->Opponents()->PlayerClosestToBall()->Pos());
	}
}

void HuDefensiveAttacker::Exit(FieldPlayer* player) {
	player->Steering()->InterposeOff();
	((HuSoccerTeam*)player->Team())->SetDefensiveAttacker(NULL);
}


//***********************************************************************************************
HuGuarder* HuGuarder::Instance()
{
	static HuGuarder instance;

	return &instance;
}

void HuGuarder::Enter(FieldPlayer* player) {
	player->Steering()->InterposeOn(HU_INTERPOSE_DIST);
}

void HuGuarder::Execute(FieldPlayer* player) {

}
void HuGuarder::Exit(FieldPlayer* player) {
	player->Steering()->InterposeOff();
}




