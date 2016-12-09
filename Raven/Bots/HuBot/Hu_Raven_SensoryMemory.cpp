#include "Hu_Raven_SensoryMemory.h"
#include "../../AbstRaven_Bot.h"
#include "../../Raven_Game.h"
#include "time/crudetimer.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Debug\DebugConsole.h"

int Hu_Raven_SensoryMemory::NumberBotInFOV() {
	
	int num = me->GetWorld()->GetAllBotsInFOV(me).size();

	debug_con << "Enemies in FOV:" << num << "";

	return num;
}