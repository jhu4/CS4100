#ifndef HUSOCCERTEAMMAKER_H
#define HUSOCCERTEAMMAKER_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   SoccerTeamMaker.h
//
//  Desc:   Factory class for SoccerTeam. 
//
//  Author: Jinan Hu 2016 (jhu4@wpi.edu)
//
//------------------------------------------------------------------------

#include "../../TeamMaker.h"
#include "../../AbstSoccerTeam.h"
#include <string>
#include "../../Goal.h"
#include "../../SoccerPitch.h"
#include "HuSoccerTeam.h"

class HuSoccerTeamMaker : public TeamMaker {
public:

private:
   HuSoccerTeamMaker();

   AbstSoccerTeam* makeTeam(Goal*        home_goal,
             Goal*        opponents_goal,
             SoccerPitch* pitch,
			 AbstSoccerTeam::team_color   color) const;
	
   // creation of static instance does automatic registration
    static const HuSoccerTeamMaker registerThis;
};
#endif