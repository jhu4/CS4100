#ifndef BURKESOCCERTEAM_H
#define BURKESOCCERTEAM_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   BurkeSoccerTeam.h
//
//  Desc:   BurkeSoccerTeam. Differs only from the original in the preferred
//			positions of the players.
//
//  Author: Robin Burke 2005 (rburke@cs.depaul.edu)
//
//------------------------------------------------------------------------

#include "../../AbstSoccerTeam.h"
                
class BurkeSoccerTeam : public AbstSoccerTeam
{
public:
	BurkeSoccerTeam(Goal*        home_goal,
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
protected:
	std::string Name()const{if (m_Color == blue) return "Blue Burke"; return "Red Burke";}

	void InitStateMachine();
	void CreatePlayers();
	void InitPlayers();
	void prepareForKickoff();
	
  void UpdateTargetsOfWaitingPlayers()const;
};

#endif