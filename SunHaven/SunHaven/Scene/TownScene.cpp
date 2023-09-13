#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
    _enemyData = new EnemyData;

    enemyPopUp();

    return S_OK;
}

void TownScene::update(void)
{
  
}

void TownScene::render(void)
{
}

void TownScene::release(void)
{
    SAFE_DELETE(_enemyData);
}

void TownScene::skillPopUp(void)
{

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
