#ifndef HuSOCCERTEAM_H
#define HuSOCCERTEAM_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   HuSoccerTeam.h
//
//  Desc:   HuSoccerTeam. Differs only from the original in the preferred
//			positions of the players.
//
//  Author: Robin Hu 2005 (rHu@cs.depaul.edu)
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
	void SetGuarder(PlayerBase* player) { m_pGuarder = player; }
	void SetDefensiveAttacker(PlayerBase* player) { m_pDefensiveAttacker = player; }

	PlayerBase* Guarder();
	PlayerBase* DefensiveAttacker();

protected:
	std::string Name()const{if (m_Color == blue) return "Blue Hu"; return "Red Hu";}

	void InitStateMachine();
	void CreatePlayers();
	void InitPlayers();
	void prepareForKickoff();
	

	//pointers to 'key' players
	PlayerBase*               m_pDefensiveAttacker;
	PlayerBase*               m_pGuarder;

	//*
    void UpdateTargetsOfWaitingPlayers()const;
	PlayerBase* DetermineBestSupportingAttacker();
	PlayerBase* DetermineBestDefensiveAttacker();
	PlayerBase* DetermineBestGuarder();

};

#endif