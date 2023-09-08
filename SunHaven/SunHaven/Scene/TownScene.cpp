#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
    _playerData = new PlayerData;
    _playerData->init();

    _enemyData = new EnemyData;
    _enemyData->init();

    return S_OK;
}

void TownScene::update(void)
{
}

void TownScene::render(void)
{
    skillPopUp();
    //enemyPopUp();
}

void TownScene::release(void)
{
    SAFE_DELETE(_playerData);
    SAFE_DELETE(_enemyData);
}

void TownScene::skillPopUp(void)
{
    char str[256];

    queue<tagSkill*> temp = *_playerData->getExplor();
        tagSkill* node = temp.front();

        sprintf_s(str, "%s", node->name.c_str());
        TextOut(getMemDC(), 200, 100, str, strlen(str));

        sprintf_s(str, "%s", node->type.c_str());
        TextOut(getMemDC(), 200, 120, str, strlen(str));

        sprintf_s(str, "%d", node->tier);
        TextOut(getMemDC(), 200, 140, str, strlen(str));

        sprintf_s(str, "%s", node->description.c_str());
        TextOut(getMemDC(), 200, 160, str, strlen(str));
        temp.pop();
}

void TownScene::enemyPopUp(void)
{
    char str[256];

    queue<tagEnemy*>* temp = _enemyData->getEnemy();
    tagEnemy* node = temp->front();

    sprintf_s(str, "%s", node->name.c_str());
    TextOut(getMemDC(), 200, 100, str, strlen(str));

    sprintf_s(str, "%d", node->level);
    TextOut(getMemDC(), 200, 120, str, strlen(str));

    sprintf_s(str, "%d", node->hp);
    TextOut(getMemDC(), 200, 140, str, strlen(str));

    sprintf_s(str, "%d", node->minDmg);
    TextOut(getMemDC(), 200, 160, str, strlen(str));
}
