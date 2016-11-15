#ifndef HUSOCCERTEAM_H
#define HUSOCCERTEAM_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   HuSoccerTeam.h
//
//  Desc:   HuSoccerTeam. Differs only from the original in the preferred
//			positions of the players.
//
//  Author: Jinan Hu 2016 (jhu4@wpi.edu)
//
//------------------------------------------------------------------------

#include "../../AbstSoccerTeam.h"
                
class HuSoccerTeam : public AbstSoccerTeam
{
public:
	HuSoccerTeam(Goal*        home_goal,
                 Goal*        opponents_goal,
                 SoccerPitch* pitch,
			     team_color   color);

	bool isDribbleSafeFromAllOpponents(Vector2D from,
                                            Vector2D  dir,
                                            double kickingForce)const;
	bool isDribbleSafeFromOpponent(Vector2D    from,
                                        Vector2D    dir,
                                        const PlayerBase* const opp,
                                        double kickingForce)const;
<<<<<<< HEAD
	//*
	bool isBallInOurHalf();
=======
>>>>>>> c4b9654db7364d58f930200457dc677c28e94fed
protected:
	std::string Name()const{if (m_Color == blue) return "Blue Hu"; return "Red Hu";}

	void InitStateMachine();
	void CreatePlayers();
	void InitPlayers();
	void prepareForKickoff();
<<<<<<< HEAD

=======
	
>>>>>>> c4b9654db7364d58f930200457dc677c28e94fed
  void UpdateTargetsOfWaitingPlayers()const;
};

#endif