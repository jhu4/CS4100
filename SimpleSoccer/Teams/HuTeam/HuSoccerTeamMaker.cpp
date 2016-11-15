#include "HuSoccerTeamMaker.h"


const HuSoccerTeamMaker HuSoccerTeamMaker::registerThis;

HuSoccerTeamMaker::HuSoccerTeamMaker() : TeamMaker("HuTeam") {}

AbstSoccerTeam* HuSoccerTeamMaker::makeTeam(Goal* home_goal,
             Goal*        opponents_goal,
             SoccerPitch* pitch,
			 AbstSoccerTeam::team_color   color) const
   { 
      return new HuSoccerTeam(home_goal, opponents_goal, pitch, color); 
   }