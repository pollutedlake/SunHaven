// �輺��
#include "Stdafx.h"
#include "ShopScene.h"
//#include "../Class/Item/Weapon.h"

HRESULT ShopScene::init(void)
{
	_temp = new Inventory;
	_temp->init();

	_itemData = new ItemData;
	_itemData->init();

    _questData = new QuestData;
    _questData->init();

	return S_OK;
}

void ShopScene::release(void)
{

}

void ShopScene::update(void)
{
	_temp->update();
}

void ShopScene::render(void)
{
	_temp->render();
	IMAGEMANAGER->render("Cursor", getMemDC(), _ptMouse.x, _ptMouse.y);

	itemPopUp();
    //questPopUp();
}

void ShopScene::itemPopUp(void)
{
    char str[256];

    queue<tagWeapon*>* temp = _itemData->getWeapon();
	tagWeapon* node = temp->front();

	sprintf_s(str, "%s", node->name.c_str());
	TextOut(getMemDC(), 200, 100, str, strlen(str));

    sprintf_s(str, "%s", node->type.c_str());
    TextOut(getMemDC(), 200, 120, str, strlen(str));

    sprintf_s(str, "%s", node->grade.c_str());
    TextOut(getMemDC(), 200, 140, str, strlen(str));

    sprintf_s(str, "%s", node->description.c_str());
    TextOut(getMemDC(), 200, 160, str, strlen(str));

	/*switch (temp->front()->getType())
	{
	case EItemType::WEAPON:
		Weapon* node = (Weapon*)(temp->front());

		sprintf_s(str, "%s", node->getName().c_str());
		TextOut(getMemDC(), 200, 150, str, strlen(str));

		break;
	}*/
}

void ShopScene::questPopUp()
{
    char str[256];

    queue<Quest*>* temp = _questData->getQuest();
    Quest* node = temp->front();

    sprintf_s(str, "%s", node->getName().c_str());
    TextOut(getMemDC(), 200, 150, str, strlen(str));

    sprintf_s(str, "����: %s", node->getDescription().c_str());
    TextOut(getMemDC(), 200, 170, str, strlen(str));

    sprintf_s(str, "���� �̸�: %s", node->getMonsterName().c_str());
    TextOut(getMemDC(), 200, 190, str, strlen(str));

    sprintf_s(str, "óġ�ؾ� �� ����: %d", node->getMonster());
    TextOut(getMemDC(), 200, 210, str, strlen(str));

    sprintf_s(str, "����Ʈ üũ: %s", node->getQuestCheck().c_str());
    TextOut(getMemDC(), 200, 230, str, strlen(str));

    sprintf_s(str, "����Ʈ ���� ����ġ: %d", node->getExp());
    TextOut(getMemDC(), 200, 250, str, strlen(str));

    sprintf_s(str, "����Ʈ ���� ������: %s", node->getItem().c_str());
    TextOut(getMemDC(), 200, 270, str, strlen(str));

    sprintf_s(str, "����Ʈ ���� ���: %d", node->getGold());
    TextOut(getMemDC(), 200, 290, str, strlen(str));

    sprintf_s(str, "����Ʈ ��������: %s", node->getQuestPlace().c_str());
    TextOut(getMemDC(), 200, 310, str, strlen(str));
}
