#include "Hu_BotMaker.h"


const Hu_BotMaker Hu_BotMaker::registerThis;

Hu_BotMaker::Hu_BotMaker() : BotMaker("Hu_Bot") {}

AbstRaven_Bot* Hu_BotMaker::makeBot(Raven_Game* world, Vector2D pos) const
   { 
      return new Hu_Bot(world, pos); 
   }