#include "BurkeSoccerTeamMaker.h"


const BurkeSoccerTeamMaker BurkeSoccerTeamMaker::registerThis;

BurkeSoccerTeamMaker::BurkeSoccerTeamMaker() : TeamMaker("BurkeTeam") {}

AbstSoccerTeam* BurkeSoccerTeamMaker::makeTeam(Goal* home_goal,
             Goal*        opponents_goal,
             SoccerPitch* pitch,
			 AbstSoccerTeam::team_color   color) const
   { 
      return new BurkeSoccerTeam(home_goal, opponents_goal, pitch, color); 
   }