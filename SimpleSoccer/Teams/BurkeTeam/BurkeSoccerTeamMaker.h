#ifndef BURKESOCCERTEAMMAKER_H
#define BURKESOCCERTEAMMAKER_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   SoccerTeamMaker.h
//
//  Desc:   Factory class for SoccerTeam. 
//
//  Author: Robin Burke 2005 rburke@cs.depaul.edu
//
//------------------------------------------------------------------------

#include "../../TeamMaker.h"
#include "../../AbstSoccerTeam.h"
#include <string>
#include "../../Goal.h"
#include "../../SoccerPitch.h"
#include "BurkeSoccerTeam.h"

class BurkeSoccerTeamMaker : public TeamMaker {
public:

private:
   BurkeSoccerTeamMaker();

   AbstSoccerTeam* makeTeam(Goal*        home_goal,
             Goal*        opponents_goal,
             SoccerPitch* pitch,
			 AbstSoccerTeam::team_color   color) const;
	
   // creation of static instance does automatic registration
    static const BurkeSoccerTeamMaker registerThis;
};
#endif