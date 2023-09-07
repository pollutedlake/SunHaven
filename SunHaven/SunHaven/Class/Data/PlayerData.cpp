#include "Stdafx.h"
#include "PlayerData.h"
#include "../Skill/ExplorationSkill.h"

void PlayerData::init(void)
{
	explorationSetUp();
	farmingSetUp();
	miningSetUp();
	combatSetUp();
	fishingSetUp();
}

void PlayerData::explorationSetUp(tagSkill* qExplor)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Player.json");

	for (auto it = root["Skill"]["Exploration"].begin(); it != root["Skill"]["Exploration"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagSkill* qExplor = new tagSkill;
			
			qExplor->index = (*it)["_index"].asString();
			qExplor->name = (*it)["_name"].asString();
			qExplor->type = (*it)["_type"].asString();
			qExplor->tier = (*it)["_tier"].asInt();
			qExplor->description = (*it)["_description"].asString();
			qExplor->value1[0] = (*it)["_value1"][(Json::Value::UInt)0].asDouble();
			qExplor->value1[1] = (*it)["_value1"][1].asDouble();
			qExplor->value1[2] = (*it)["_value1"][2].asDouble();
			qExplor->value2[0] = (*it)["_value2"][(Json::Value::UInt)0].asDouble();
			qExplor->value2[1] = (*it)["_value2"][1].asDouble(),
			qExplor->value2[2] = (*it)["_value2"][2].asDouble();

			_explor.push(qExplor);
		}
	}
}

void PlayerData::farmingSetUp(tagSkill* qFarm)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Player.json");

	for (auto it = root["Skill"]["Farming"].begin(); it != root["Skill"]["Farming"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagSkill* qFarm = new tagSkill;

			qFarm->index = (*it)["_index"].asString();
			qFarm->name = (*it)["_name"].asString();
			qFarm->type = (*it)["_type"].asString();
			qFarm->tier = (*it)["_tier"].asInt();
			qFarm->description = (*it)["_description"].asString();
			qFarm->value1[0] = (*it)["_value1"][(Json::Value::UInt)0].asDouble();
			qFarm->value1[1] = (*it)["_value1"][1].asDouble();
			qFarm->value1[2] = (*it)["_value1"][2].asDouble();
			qFarm->value2[0] = (*it)["_value2"][(Json::Value::UInt)0].asDouble();
			qFarm->value2[1] = (*it)["_value2"][1].asDouble(),
			qFarm->value2[2] = (*it)["_value2"][2].asDouble();

			_farm.push(qFarm);
		}
	}
}

void PlayerData::miningSetUp(tagSkill* qMine)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Player.json");

	for (auto it = root["Skill"]["Mining"].begin(); it != root["Skill"]["Mining"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagSkill* qMine = new tagSkill;

			qMine->index = (*it)["_index"].asString();
			qMine->name = (*it)["_name"].asString();
			qMine->type = (*it)["_type"].asString();
			qMine->tier = (*it)["_tier"].asInt();
			qMine->description = (*it)["_description"].asString();
			qMine->value1[0] = (*it)["_value1"][(Json::Value::UInt)0].asDouble();
			qMine->value1[1] = (*it)["_value1"][1].asDouble();
			qMine->value1[2] = (*it)["_value1"][2].asDouble();
			qMine->value2[0] = (*it)["_value2"][(Json::Value::UInt)0].asDouble();
			qMine->value2[1] = (*it)["_value2"][1].asDouble(),
			qMine->value2[2] = (*it)["_value2"][2].asDouble();

			_mine.push(qMine);
		}
	}
}

void PlayerData::combatSetUp(tagSkill* qCombat)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Player.json");

	for (auto it = root["Skill"]["Combat"].begin(); it != root["Skill"]["Combat"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagSkill* qCombat = new tagSkill;

			qCombat->index = (*it)["_index"].asString();
			qCombat->name = (*it)["_name"].asString();
			qCombat->type = (*it)["_type"].asString();
			qCombat->tier = (*it)["_tier"].asInt();
			qCombat->description = (*it)["_description"].asString();
			qCombat->value1[0] = (*it)["_value1"][(Json::Value::UInt)0].asDouble();
			qCombat->value1[1] = (*it)["_value1"][1].asDouble();
			qCombat->value1[2] = (*it)["_value1"][2].asDouble();
			qCombat->value2[0] = (*it)["_value2"][(Json::Value::UInt)0].asDouble();
			qCombat->value2[1] = (*it)["_value2"][1].asDouble(),
			qCombat->value2[2] = (*it)["_value2"][2].asDouble();

			_combat.push(qCombat);
		}
	}
}

void PlayerData::fishingSetUp(tagSkill* qFish)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Player.json");

	for (auto it = root["Skill"]["Fishing"].begin(); it != root["Skill"]["Fishing"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagSkill* qfishing = new tagSkill;

			qfishing->index = (*it)["_index"].asString();
			qfishing->name = (*it)["_name"].asString();
			qfishing->type = (*it)["_type"].asString();
			qfishing->tier = (*it)["_tier"].asInt();
			qfishing->description = (*it)["_description"].asString();
			qfishing->value1[0] = (*it)["_value1"][(Json::Value::UInt)0].asDouble();
			qfishing->value1[1] = (*it)["_value1"][1].asDouble();
			qfishing->value1[2] = (*it)["_value1"][2].asDouble();
			qfishing->value2[0] = (*it)["_value2"][(Json::Value::UInt)0].asDouble();
			qfishing->value2[1] = (*it)["_value2"][1].asDouble(),
			qfishing->value2[2] = (*it)["_value2"][2].asDouble();

			_fish.push(qfishing);
		}
	}
}
