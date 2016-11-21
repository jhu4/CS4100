#include "Hu_BotScriptor.h"

Hu_BotScriptor* Hu_BotScriptor::Instance()
{
  static Hu_BotScriptor instance;

  return &instance;
}



Hu_BotScriptor::Hu_BotScriptor():Scriptor()
{
  RunScriptFile("Bots/HuBot/Hu_Bot.lua");
}