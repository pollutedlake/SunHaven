// ¹Î¿ë½Ä
#include "Stdafx.h"
#include "FarmScene.h"
#include "../Class/UI.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("³óÀå", "FarmMap.bmp", 3600, 3600);
	IMAGEMANAGER->addImage("Ãæµ¹", "FarmMapCollision.bmp", 3600, 3600);

	
	_player = new Player;
	_player->init(2800, 1400);


	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(3276 - WINSIZE_X / 2);
	_camera->setLimitBottom(3600 - WINSIZE_Y / 2);

	_om = new ObjectManager;
	_om->init();
	_om->setCameraAddress(_camera);

	_ui = new UI;
	_ui->init("Farm");
	return S_OK;
}

void FarmScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_om->release();
	SAFE_DELETE(_om);
}

void FarmScene::update(void)
{
	_player->update();
	_camera->setPosition(_player->getPlayerPosition());
	_player->worldToCamera(_camera->worldToCamera
	(_player->getPlayerPosition()));
	_om->update();
	/*_vRenderList.push(make_pair(_player, _player->getPlayerRC().bottom));
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), &_om->getObjectList()[i]->getRC()))
		{
			if (IntersectRect(&temp, &_player->getPlayerRC(), &_om->getObjectList()[i]->getRC()))
			{
				_om->getObjectList()[i]->setHalfTrans(true);
			}
			else
			{
				_om->getObjectList()[i]->setHalfTrans(false);
			}
			_vRenderList.push(make_pair(_om->getObjectList()[i], _om->getObjectList()[i]->getRC().bottom));
		}
	}*/
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), 0, 0, _camera->getPosition().x - WINSIZE_X / 2,
		_camera->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);

	_vRenderList.push(make_pair(_player, _player->getPlayerRC().bottom));
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), &_om->getObjectList()[i]->getRC()))
		{
			if (IntersectRect(&temp, &_player->getPlayerRC(), &_om->getObjectList()[i]->getRC()))
			{
				_om->getObjectList()[i]->setHalfTrans(true);
			}
			else
			{
				_om->getObjectList()[i]->setHalfTrans(false);
			}
			_vRenderList.push(make_pair(_om->getObjectList()[i], _om->getObjectList()[i]->getRC().bottom));
		}
	}
	while (!_vRenderList.empty())
	{
		_vRenderList.top().first->render();
		_vRenderList.pop();
	}

	if (KEYMANAGER->isToggleKey('W'))
	{
		IMAGEMANAGER->render("Ãæµ¹", getMemDC(), _camera->worldToCameraX(0),
			_camera->worldToCameraY(0));
	}

	_ui->render();
}