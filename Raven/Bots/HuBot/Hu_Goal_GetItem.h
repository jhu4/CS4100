#ifndef HU_GOAL_GETITEM
#define HU_GOAL_GETITEM

#include "../../goals/Goal_GetItem.h"
#include <vector>


class Hu_Goal_GetItem :public Goal_GetItem 
{
private: 
	std::vector<Trigger<AbstRaven_Bot>*> healths;
	Trigger<AbstRaven_Bot>* targethealthpack;
	int type;

public:
	//*HU overload constructor
	Hu_Goal_GetItem(AbstRaven_Bot* bot, int item, std::vector<Trigger<AbstRaven_Bot>*> health) :Goal_GetItem(bot, item)
		,healths(health)
		,type(item){};

	Hu_Goal_GetItem(AbstRaven_Bot* bot, int item) :Goal_GetItem(bot, item){}

	//*HU Overide function
	void Activate();
	int  Process();
	void Terminate();
	bool hasItemBeenStolen()const;
	//*HU new functions
	Trigger<AbstRaven_Bot>* getClosestHealthPack();
	Trigger<AbstRaven_Bot>* getSecondClosestHealthPack();

};

#endif // !HU_GOAL_GETITEM
