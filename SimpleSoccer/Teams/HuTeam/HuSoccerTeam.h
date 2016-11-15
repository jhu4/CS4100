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
	//*
	bool isBallInOurHalf();
protected:
	std::string Name()const{if (m_Color == blue) return "Blue Hu"; return "Red Hu";}

	//*Add two more characters in the team
	PlayerBase* m_pGuader;
	PlayerBase* m_pDefensiveAttacker;

	//*The function to find guaders and defensive attackers
	PlayerBase* DetermineBestGuader();
	PlayerBase* DetermineDefensiveAttacker();
	
	void InitStateMachine();
	void CreatePlayers();
	void InitPlayers();
	void prepareForKickoff();

  void UpdateTargetsOfWaitingPlayers()const;
};

#endif