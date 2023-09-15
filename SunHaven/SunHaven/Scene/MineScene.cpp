#include "Stdafx.h"
#include "MineScene.h"
#include "../Class/UI/UI.h"

HRESULT MineScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("MineMap", "./Resources/Data/Map/MineMap.bmp", 3600, 3600);
	IMAGEMANAGER->addImage("MineMapCollision", "./Resources/Data/Map/MineMapCollision.bmp", 3600, 3600);

	_player = new Player;
	_player->init(500, 1000, "MineMapCollision");

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(2556 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(1548 - WINSIZE_Y / 2);

	_om = new ObjectManager;
	_om->init("Mine");

	_inven = new Inventory;
	_inven->init();

	_MouseOver = IMAGEMANAGER->addImage("오브젝트 선택",
		"Resources/Images/Player/ObjectMouseOver.bmp",
		36, 36, true, RGB(255, 0, 255));

	_MouseRC = RectMakeCenter(CAMERA->cameraToWorld(_ptMouse).x,
		CAMERA->cameraToWorld(_ptMouse).y,
		_MouseOver->getWidth(), _MouseOver->getHeight());

	_ui = new UI;
	_ui->init("Mine");

	_em = new EnemyManager;
	_em->setPlayerMemoryAddress(_player);
	//_slug->setPlayerMemoryAddress(_player);

	_em->spawnSteelSlug();
	_em->spawnFlameImp();

	return S_OK;
}

void MineScene::release(void)
{
	_inven->release();
	SAFE_DELETE(_inven);
	_player->release();
	SAFE_DELETE(_player);
	_om->release();
	SAFE_DELETE(_om);
	_em->release();
	SAFE_DELETE(_em);
}

void MineScene::update(void)
{
	_player->update();
	_inven->update();
	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->update();
	_player->worldToCamera(CAMERA->worldToCamera
	(_player->getPlayerPosition()));
	queue<pair<string, POINT>> dropItems = _om->updateObjects();
	while (!dropItems.empty())
	{
		_lDropItem.push_back(dropItems.front());
		dropItems.pop();
	}
	_vRenderList.push(make_pair(_player, _player->getPlayertoCameraRect().bottom));
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;
		// 카메라안에 잡히는 것만 클리핑해서 렌더링
		if (IntersectRect(&temp, &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), &_om->getObjectList()[i]->getRC()))
		{
			// 이미지가 겹치면 반투명화
			if (IntersectRect(&temp, &_player->getPlayertoCameraRect(), &_om->getObjectList()[i]->getRC()) && _om->getObjectList()[i]->getRC().bottom > _player->getPlayertoCameraRect().bottom)
			{
				_om->getObjectList()[i]->setHalfTrans(true);
			}
			else
			{
				_om->getObjectList()[i]->setHalfTrans(false);
			}
			// y값으로 정렬
			_vRenderList.push(make_pair(_om->getObjectList()[i], _om->getObjectList()[i]->getRC().bottom));
		}
	}


	_player->ObjectCollision(_om);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_player->UseTool(_om, _ptMouse);
		_inven->itemMove();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{

	}
	_player->UseToolAnim(KEYMANAGER->isStayKeyDown(VK_LBUTTON));

	_player->UseFishingLod(CAMERA->cameraToWorld(_ptMouse));
	getDropItem();

	_em->update();
	//_slug->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Dizzy");
	}
}

void MineScene::render(void)
{
	_bg->render(getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2,
		CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);
	// 정렬된 순서로 렌더
	while (!_vRenderList.empty())
	{
		_vRenderList.top().first->render();
		_vRenderList.pop();
	}

	_player->MouseOver(_om, _ptMouse);

	renderDropItem();

	_om->render();

	if (KEYMANAGER->isToggleKey('Q'))
	{
		IMAGEMANAGER->render("MineMapCollision", getMemDC(), CAMERA->worldToCameraX(0),
			CAMERA->worldToCameraY(0));
	}

	_em->render();
	//_slug->render();

	_inven->render();
	_ui->render();
}

void MineScene::Collision(void)
{
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;

		if (IntersectRect(&temp,
			&RectMakeCenter(_player->getPlayerPosition().x,
				_player->getPlayerPosition().y, 48, 52),
			&_om->getObjectList()[i]->getRC()))
		{
		}
	}

}

void MineScene::renderDropItem()
{
	for (_liDropItem = _lDropItem.begin(); _liDropItem != _lDropItem.end(); ++_liDropItem)
	{
		string itemIndex = _liDropItem->first.substr(2, _liDropItem->first.length() - 2);
		tagTool* toolInfo = nullptr;
		tagWeapon* waeponInfo = nullptr;
		tagArmor* armorInfo = nullptr;
		tagAccessory* accessoryInfo = nullptr;
		tagIngredient* ingredientInfo = nullptr;
		tagConsumable* consumableInfo = nullptr;
		if (CAMERA->worldToCameraX(_liDropItem->second.x) + 32 < 0 || CAMERA->worldToCameraX(_liDropItem->second.x) > WINSIZE_X)
		{
			continue;
		}
		if (CAMERA->worldToCameraY(_liDropItem->second.y) + 32 < 0 || CAMERA->worldToCameraY(_liDropItem->second.y) > WINSIZE_Y)
		{
			continue;
		}
		switch (_liDropItem->first[0])
		{
		case '0':
			toolInfo = DATAMANAGER->getToolInfo(atoi(itemIndex.c_str()));
			IMAGEMANAGER->addImage(toolInfo->name, toolInfo->filePath.c_str(), 32, 32, true, RGB(255, 0, 255))->render(getMemDC(),
				CAMERA->worldToCameraX(_liDropItem->second.x), CAMERA->worldToCameraY(_liDropItem->second.y));
			break;
		case '1':
			waeponInfo = DATAMANAGER->getWeaponInfo(atoi(itemIndex.c_str()));
			IMAGEMANAGER->addImage(waeponInfo->name, waeponInfo->filePath.c_str(), 32, 32, true, RGB(255, 0, 255))->render(getMemDC(),
				CAMERA->worldToCameraX(_liDropItem->second.x), CAMERA->worldToCameraY(_liDropItem->second.y));
			break;
		case '2':
			armorInfo = DATAMANAGER->getArmorInfo(atoi(itemIndex.c_str()));
			IMAGEMANAGER->addImage(armorInfo->name, armorInfo->filePath.c_str(), 32, 32, true, RGB(255, 0, 255))->render(getMemDC(),
				CAMERA->worldToCameraX(_liDropItem->second.x), CAMERA->worldToCameraY(_liDropItem->second.y));
			break;
		case '3':
			accessoryInfo = DATAMANAGER->getAccessoryInfo(atoi(itemIndex.c_str()));
			IMAGEMANAGER->addImage(accessoryInfo->name, accessoryInfo->filePath.c_str(), 32, 32, true, RGB(255, 0, 255))->render(getMemDC(),
				CAMERA->worldToCameraX(_liDropItem->second.x), CAMERA->worldToCameraY(_liDropItem->second.y));
			break;
		case '4':
			ingredientInfo = DATAMANAGER->getIngredientInfo(atoi(itemIndex.c_str()));
			IMAGEMANAGER->addImage(ingredientInfo->name, ingredientInfo->filePath.c_str(), 32, 32, true, RGB(255, 0, 255))->render(getMemDC(),
				CAMERA->worldToCameraX(_liDropItem->second.x), CAMERA->worldToCameraY(_liDropItem->second.y));
			break;
		case '5':
			consumableInfo = DATAMANAGER->getConsumableInfo(atoi(itemIndex.c_str()));
			IMAGEMANAGER->addImage(consumableInfo->name, consumableInfo->filePath.c_str(), 32, 32, true, RGB(255, 0, 255))->render(getMemDC(),
				CAMERA->worldToCameraX(_liDropItem->second.x), CAMERA->worldToCameraY(_liDropItem->second.y));
			break;
		}
	}
}

void MineScene::getDropItem()
{
	for (_liDropItem = _lDropItem.begin(); _liDropItem != _lDropItem.end();)
	{
		if (getDistance(_liDropItem->second.x,
			_liDropItem->second.y,
			_player->getPlayerPosition().x,
			_player->getPlayerPosition().y) < 120)
		{
			_liDropItem->second.x +=
				cosf(getAngle(_liDropItem->second.x,
					_liDropItem->second.y,
					_player->getPlayerPosition().x,
					_player->getPlayerPosition().y)) * 2.2f;

			_liDropItem->second.y +=
				-sinf(getAngle(_liDropItem->second.x,
					_liDropItem->second.y,
					_player->getPlayerPosition().x,
					_player->getPlayerPosition().y)) * 2.2f;


			if (PtInRect(&_player->getPlayerRC(), _liDropItem->second))
			{
				_inven->getItem(_liDropItem->first);
				_liDropItem = _lDropItem.erase(_liDropItem);
			}
			else
			{
				++_liDropItem;
			}
		}
		else
		{
			++_liDropItem;
		}
	}
}