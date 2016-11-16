#ifndef HUFIELDPLAYER_H
#define HUFIELDPLAYER_H

#include "../../FieldPlayer.h"
#include "HuSoccerTeam.h"

class HuFieldPlayer : public FieldPlayer
{
private:
	HuSoccerTeam* myteam;

public:

  HuFieldPlayer(HuSoccerTeam*    home_team,
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
             player_role    role);   
  
  ~HuFieldPlayer();

  HuSoccerTeam* Team() { return myteam;}


  //*Find the defensive
  void		  FindDefensiveAttacker();
  void		  FindDefender();
  void		  FindGuarder();

         
};




#endif