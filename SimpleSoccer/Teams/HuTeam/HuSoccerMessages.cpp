#include "HuSoccerMessages.h"


inline std::string MessageToString(int msg)
{
  switch (msg)
  {
  case Msg_ReceiveBall:
    
    return "Msg_ReceiveBall";

  case Msg_PassToMe:
    
    return "Msg_PassToMe";

  case Msg_SupportAttacker:

    return "Msg_SupportAttacker";

  case Msg_GoHome:

    return "Msg_GoHome";

  case Msg_Wait:

    return "Msg_Wait";

  case   Msg_DefensiveAttacker:
    return "Msg_DefensiveAttacker";

  case Msg_Guarder:
    return "Msg_Guarder";
    
  case Msg_Defender:
    return "Msg_Defender";

  default:

    return "INVALID MESSAGE!!";
  }
}