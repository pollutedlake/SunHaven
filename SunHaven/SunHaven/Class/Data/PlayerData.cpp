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
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/PlayerData.json");

	for (auto it = root["Skill"]["Exploration"].begin(); it != root["Skill"]["Exploration"].end(); it++)
	{
		if ((*it).isObject())
		{
			Skill* qExplor = new ExplorationSkill;

			/*qExplor->init
			(
				(*it)["_index"].asString(),
				(*it)["_name"].asString(),
				(*it)["_type"].asString(), 
				(*it)["_tier"].asInt(),
				(*it)["_description"].asString(),
				(*it)["_value1"][(Json::Value::UInt)0].asDouble(),
				(*it)["_value1"][1].asDouble(),
				(*it)["_value1"][2].asDouble(),


			);*/

			_skill.push(qExplor);
		}
	}
}