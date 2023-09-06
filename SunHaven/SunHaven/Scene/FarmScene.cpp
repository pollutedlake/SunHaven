// ¹Î¿ë½Ä
#include "Stdafx.h"
#include "FarmScene.h"
#include "../Class/UI.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("³óÀå", "FarmMap.bmp", 4800, 4800);
	IMAGEMANAGER->addImage("Ãæµ¹", "FarmMapCollision.bmp", 4800, 4800);

	
	_player = new Player;
	_player->init(2800, 1400);


	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(4368 - WINSIZE_X / 2);
	_camera->setLimitBottom(4800 - WINSIZE_Y / 2);

	_om = new ObjectManager;
	_om->init();
	_om->setCameraAddress(_camera);

	_ui = new UI;
	_ui->init("Farm");

	_vRenderList.clear();
	/*_vRenderList.push_back(_player);
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		_vRenderList.push_back(_om->getObjectList()[i]);
	}*/
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
	_vRenderList.push_back(make_pair(_player, _player->getPlayerRC().bottom));
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		_vRenderList.push_back(make_pair(_om->getObjectList()[i], _om->getObjectList()[i]->getRC().bottom));
	}
	sortingRenderList(0, _vRenderList.size());
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), _camera->worldToCameraX(0),
		_camera->worldToCameraY(0));

	_player->render();
	bool playerRender = false;
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;
		if(IntersectRect(&temp, &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), &_om->getObjectList()[i]->getRC()))
		{
			if(&_om->getObjectList())
			if (IntersectRect(&temp, &_player->getPlayerRC(), &_om->getObjectList()[i]->getRC()) && _om->getObjectList()[i]->getType() / 2 == 1)
			{
				_om->getObjectList()[i]->halfTransRender();
			}
			else
			{
				_om->getObjectList()[i]->render();
			}
		}
	}

	if (KEYMANAGER->isToggleKey('W'))
	{
		IMAGEMANAGER->render("Ãæµ¹", getMemDC(), _camera->worldToCameraX(0),
			_camera->worldToCameraY(0));
	}

	
	_ui->render();
}

void FarmScene::sortingRenderList(int start, int end)
{
	if (start >= end)
	{
		return;
	}
	
	int pivot  = start;
	int i = pivot + 1;
	int j = end;
	pair<GameNode*, int> temp;
	while (i <= j)
	{
		while (i <= end && _vRenderList[i].second <= _vRenderList[pivot].second)
		{
			i++;
		}
		while (j > start && _vRenderList[j].second >= _vRenderList[pivot].second)
		{
			j--;
		}
	
		if (i > j)
		{
			temp = _vRenderList[j];
			_vRenderList[j] = _vRenderList[pivot];
			_vRenderList[pivot] = temp;
		}
		else
		{
			temp = _vRenderList[i];
			_vRenderList[i] = _vRenderList[j];
			_vRenderList[j] = temp;
		}
	}
	sortingRenderList(start, j - 1);
	sortingRenderList(j + 1, end);
}
