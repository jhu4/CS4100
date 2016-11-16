#include "HuFieldPlayer.h"
#include "HuSoccerMessages.h"
#include "HuSoccerTeam.h"

#include "../../PlayerBase.h"
#include "../../SteeringBehaviors.h"
#include "2D/Transformations.h"
#include "2D/Geometry.h"
#include "misc/Cgdi.h"
#include "2D/C2DMatrix.h"
#include "../../Goal.h"
#include "Game/Region.h"
#include "game/EntityFunctionTemplates.h"
#include "../../ParamLoader.h"
#include "../../AbstSoccerTeam.h"
#include "time/Regulator.h"
#include "Debug/DebugConsole.h"
#include "Messaging/MessageDispatcher.h"

#include <limits>

using std::vector;

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
HuFieldPlayer::~HuFieldPlayer() {

}

HuFieldPlayer::HuFieldPlayer(HuSoccerTeam*    home_team,
             int        home_region,
             State<FieldPlayer>* start_state,
			 State<FieldPlayer>* global_state,
             Vector2D  heading,
             Vector2D      velocity,
             double         mass,
             double         max_force,
             double         max_speed,
             double         max_turn_rate,
             double         scale,
             player_role    role):myteam(home_team),FieldPlayer(home_team
             													,home_region
             													,start_state
             													,global_state
             													,heading
             													,velocity
             													,mass
             													,max_force,
             													max_speed,
             													max_turn_rate,
             													scale,
             													role)
{

}

//------------------------------------------------------------------------------
void HuFieldPlayer::FindDefensiveAttacker(){
	//if there is no support we need to find a suitable player.
	if (Team()->DefensiveAttacker() == NULL)
	{
		PlayerBase* BestDefensiveAttackerPly = Team()->DetermineBestDefensiveAttacker();

		Team()->SetDefensiveAttacker(BestDefensiveAttackerPly);

		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			ID(),
			Team()->DefensiveAttacker()->ID(),
			Msg_DefensiveAttacker,
			NULL);
	}

	PlayerBase* BestDefensiveAttackerPly = Team()->DetermineBestDefensiveAttacker();

	//if the best player changes, update
	//the pointers and send messages to the relevant players to update their
	//states
	if (BestDefensiveAttackerPly && (BestDefensiveAttackerPly != Team()->DefensiveAttacker()))
	{

		if (Team()->DefensiveAttacker())
		{
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				ID(),
				Team()->DefensiveAttacker()->ID(),
				Msg_GoHome,
				NULL);
		}



		Team()->SetGuarder(BestDefensiveAttackerPly);

		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			ID(),
			Team()->DefensiveAttacker()->ID(),
			Msg_DefensiveAttacker,
			NULL);
	}


}
void HuFieldPlayer::FindDefender(){
	//if there is no support we need to find a suitable player.
	if (Team()->Defender() == NULL)
	{
		PlayerBase* BestDefenderPly = Team()->DetermineBestDefender();

		Team()->SetDefender(BestDefenderPly);

		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			ID(),
			Team()->Defender()->ID(),
			Msg_Defender,
			NULL);
	}

	PlayerBase* BestDefenderPly = Team()->DetermineBestDefender();

	//if the best player changes, update
	//the pointers and send messages to the relevant players to update their
	//states
	if (BestDefenderPly && (BestDefenderPly != Team()->Defender()))
	{

		if (Team()->Defender())
		{
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				ID(),
				Team()->Defender()->ID(),
				Msg_GoHome,
				NULL);
		}



		Team()->SetGuarder(BestDefenderPly);

		Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
			ID(),
			Team()->Guarder()->ID(),
			Msg_Defender,
			NULL);
	}


}

void HuFieldPlayer::FindGuarder(){

      //if there is no support we need to find a suitable player.
      if (Team()->Guarder() == NULL)
      {
            PlayerBase* BestGuarderPly = Team()->DetermineBestGuarder();

			Team()->SetGuarder(BestGuarderPly);

            Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                  ID(),
				  Team()->Guarder()->ID(),
                  Msg_Guarder,
                  NULL);
      }

      PlayerBase* BestGuarderPly = Team()->DetermineBestGuarder();

      //if the best player changes, update
      //the pointers and send messages to the relevant players to update their
      //states
      if (BestGuarderPly && (BestGuarderPly != Team()->Guarder()))
      {

            if (Team()->Guarder())
            {
                  Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                        ID(),
					    Team()->Guarder()->ID(),
                        Msg_GoHome,
                        NULL);
            }



			Team()->SetGuarder(BestGuarderPly);

            Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                  ID(),
			      Team()->Guarder()->ID(),
                  Msg_Guarder,
                  NULL);
      }


}