#ifndef HUSOCCER_MESSAGES_H
#define HUSOCCER_MESSAGES_H

#include <string>

enum MessageType
{
  Msg_ReceiveBall=6,
  Msg_PassToMe=7,
  Msg_SupportAttacker=8,
  Msg_GoHome=9,
  Msg_Wait=10,
  Msg_DefensiveAttacker=11,
  Msg_Guarder=12,
  Msg_Defender=13
};

//converts an enumerated value to a string
inline std::string MessageToString(int msg);


#endif