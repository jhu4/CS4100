#ifndef HUSOCCER_MESSAGES_H
#define HUSOCCER_MESSAGES_H

#include <string>

enum MessageType
{
  Msg_ReceiveBall=0,
  Msg_PassToMe=1,
  Msg_SupportAttacker=2,
  Msg_GoHome=3,
  Msg_Wait=4,
  Msg_DefensiveAttacker=5,
  Msg_Guarder=6,
  Msg_Defender=7
};

//converts an enumerated value to a string
inline std::string MessageToString(int msg);


#endif