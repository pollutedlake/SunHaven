#include "Stdafx.h"
#include "PlayerData.h"
#include "../Skill/ExplorationSkill.h"

void PlayerData::init(void)
{
	/*explorationSetUp();
	farmingSetUp();
	miningSetUp();
	combatSetUp();
	fishingSetUp();*/
}

void PlayerData::explorationSetUp(Skill* qExplor)
{
	/*Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/PlayerData.json");

	for (auto it = root["Skill"]["Exploration"].begin(); it != root["Skill"]["Exploration"].end(); it++)
	{
		if ((*it).isObject())
		{
			Skill* qExplor = new ExplorationSkill;

			Json::Value arrFloatType = (*it)["_value1"];
			float* floatType = (float*)malloc(sizeof(float) * arrFloatType.size());

			if (floatType != nullptr)
			{
				for (int i = 0; i < arrFloatType.size(); i++)
				{
					*(floatType + i) = (*it)["_value1"][i].asInt();
					*(floatType + i) = (*it)["_value2"][i].asInt();
				}
			}

			qExplor->init
			(
				(*it)["_index"].asString(),
				(*it)["_name"].asString(),
				(*it)["_type"].asString(),
				(*it)["_tier"].asInt(),
				(*it)["_description"].asString,


				(*it)["_filePath"].asString()
			);

			_skill.push(qExplor);
		}
	}*/
}