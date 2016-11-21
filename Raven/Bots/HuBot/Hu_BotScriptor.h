#ifndef Hu_BOTSCRIPTOR_H
#define Hu_BOTSCRIPTOR_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Scriptor
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   A Singleton Scriptor class for use with the Raven project
//-----------------------------------------------------------------------------
#include "Script/scriptor.h"


class Hu_BotScriptor : public Scriptor
{
private:
  
  Hu_BotScriptor();

  //copy ctor and assignment should be private
  Hu_BotScriptor(const Hu_BotScriptor&);
  Hu_BotScriptor& operator=(const Hu_BotScriptor&);

public:

  static Hu_BotScriptor* Instance();

};

#endif

 
  

