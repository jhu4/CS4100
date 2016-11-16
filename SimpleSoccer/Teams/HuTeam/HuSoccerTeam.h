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



	//*getters and setters
	PlayerBase* Guarder(){ return m_pGuader;}
	PlayerBase* DefensiveAttacker(){ return m_pDefensiveAttacker; }
	PlayerBase* Defender(){return m_pDefender; }

	void SetGuarder(PlayerBase* player) { m_pGuader = player; }
	void SetDefensiveAttacker(PlayerBase* player) { m_pDefensiveAttacker = player; }
	void SetDefender(PlayerBase* player) { m_pDefender = player; }

	//*The function to find guaders and defensive attackers
	PlayerBase* DetermineBestGuarder();
	PlayerBase* DetermineBestDefensiveAttacker();
	PlayerBase* DetermineBestDefender();

protected:
	std::string Name()const{if (m_Color == blue) return "Blue Hu"; return "Red Hu";}

	//*Add 3 more characters in the team
	PlayerBase* m_pDefender;
	PlayerBase* m_pGuader;
	PlayerBase* m_pDefensiveAttacker;

	void InitStateMachine();
	void CreatePlayers();
	void InitPlayers();
	void prepareForKickoff();

  void UpdateTargetsOfWaitingPlayers()const;
};

#endif