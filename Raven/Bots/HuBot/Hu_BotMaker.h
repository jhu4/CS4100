#ifndef HUBOTMAKER_H
#define HUBOTMAKER_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   Hu_BotMaker.h
//
//  Desc:   Factory class for Hu_BotMaker. 
//
//  Author: Robin Burke 2006 rburke@cs.depaul.edu
//
//------------------------------------------------------------------------

#include "../../BotMaker.h"
#include "../../AbstRaven_Bot.h"
#include "Hu_Bot.h"
#include <string>
#include "../../Raven_Game.h"

class Hu_BotMaker : public BotMaker {
private:
   Hu_BotMaker();

   AbstRaven_Bot* makeBot(Raven_Game* world, Vector2D pos) const;
	
   // creation of static instance does automatic registration
    static const Hu_BotMaker registerThis;
};
#endif