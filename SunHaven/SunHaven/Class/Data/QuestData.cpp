#include "Stdafx.h"
#include "QuestData.h"

void QuestData::init(void)
{
	questSetUp();
}

void QuestData::questSetUp(Quest* qQuest)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Quest.json");

	for (auto it = root["Quest"].begin(); it != root["Quest"].end(); it++)
	{
		if ((*it).isObject())
		{
			Quest* qQuest = new Quest;
			qQuest->init
			(
				(*it)["_name"].asString(),
				(*it)["_exp"].asInt(),
				(*it)["_description"].asString(),
				(*it)["_item"].asString(),
				(*it)["_monster"].asInt(),
				(*it)["_questCheck"].asString(),
				(*it)["_gold"].asInt(),
				(*it)["_monsterName"].asString(),
				(*it)["_questPlace"].asString()
			);

			_quest.push(qQuest);
		}
	}
}