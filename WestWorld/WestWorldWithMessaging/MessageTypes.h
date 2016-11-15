#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_BobsHome,
  Msg_StewReady,
  Msg_BobsLeavingSaloon,
  Msg_Punch,
  Msg_Insult,
  Msg_BobsEnteringSaloon
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

    return "LeavingTheSaloon";

  case 3:

    return "Punch";

  case 4:

    return "Insult";

  case 5:
    return "EnteringTheSaloon";

  default:

    return "Not recognized!";
  }
}

#endif