#include "Stdafx.h"
#include "EnemyData.h"

void EnemyData::init(void)
{
	enemySetUp();
}

void EnemyData::enemySetUp(tagEnemy* qEnemy)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Enemy.json");

	for (auto it = root["Enemy"].begin(); it != root["Enemy"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagEnemy* qEnemy = new tagEnemy;

			qEnemy->name = (*it)["_name"].asString();
			qEnemy->level = (*it)["_level"].asInt();
			qEnemy->hp = (*it)["_hp"].asInt();
			qEnemy->minDmg = (*it)["_minDmg"].asInt();
			qEnemy->maxDmg = (*it)["_maxDmg"].asInt();
			qEnemy->def = (*it)["_def"].asInt();
			qEnemy->exp = (*it)["_exp"].asInt();

			_enemy.push(qEnemy);
		}
	}
}