#include "Stdafx.h"
#include "DizzyScene.h"
#include "../Class/UI/UI.h"

HRESULT DizzyScene::init(void)
{
	IMAGEMANAGER->addImage("DizzyMapCollision", "./Resources/Data/Map/DizzyMapCollision.bmp", 1464 * 1.5, 1008 * 1.5);

	_player = new Player;
	_player->init(CENTER_X + 500, CENTER_Y + 700, "DizzyMapCollision");
	_player->setPlayerState(DATAMANAGER->getPlayereState());

	_dizzy = new Dizzy;
	_dizzy->setPlayerMemoryAddress(_player);
	_dizzy->init();

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(2196 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(1512 - WINSIZE_Y / 2);
	_player->worldToCamera(CAMERA->worldToCamera(_player->getPlayerPosition()));

	_ui = new UI;
	_ui->init("Dynus");
	_ui->setAdressPlayer(_player);

	wsprintf(_text, "DizzyScene");
	_moveMap = true;
	_portal = RectMake(1020, 1100, 180, 100);
	_moveMapImg = IMAGEMANAGER->addImage("MoveMap", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_clippingRaius = 0.0f;
	_enterScene = true;
	return S_OK;
}

void DizzyScene::release(void)
{
	_dizzy->release();
	SAFE_DELETE(_dizzy);

	_player->release();
	SAFE_DELETE(_player);
}

void DizzyScene::update(void)
{

	_player->update();
	_player->worldToCamera(CAMERA->worldToCamera(_player->getPlayerPosition()));
	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->update();
	if(!_moveMap)
	{
		_dizzy->update();
		collision();
		if (PtInRect(&_portal, _player->getPlayerPosition()))
		{
			_moveMap = true;
		}
	}
	else
	{
		if (_enterScene)
		{
			_clippingRaius += TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_clippingRaius > WINSIZE_X)
			{
				_clippingRaius = WINSIZE_X;
				_enterScene = false;
				_moveMap = false;
			}
		}
		else
		{
			_clippingRaius -= TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_clippingRaius < 0)
			{
				_clippingRaius = 0.0f;
				DATAMANAGER->setData(_player->getPlayerState());
				SCENEMANAGER->changeScene("Dynus");
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		DATAMANAGER->setData(_player->getPlayerState());
		SCENEMANAGER->changeScene("Dynus");
	}
}

void DizzyScene::render(void)
{
	IMAGEMANAGER->render("DizzyLayer", getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2,
		CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);

	_dizzy->render();
	_player->render();
	_ui->render();
	if (_moveMap)
	{
		PatBlt(_moveMapImg->getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		HBRUSH magenta = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_moveMapImg->getMemDC(), magenta);
		EllipseMakeCenter(_moveMapImg->getMemDC(), (CAMERA->worldToCameraRect(_player->getPlayerRC()).right + CAMERA->worldToCameraRect(_player->getPlayerRC()).left) / 2.0f,
			(CAMERA->worldToCameraRect(_player->getPlayerRC()).bottom + CAMERA->worldToCameraRect(_player->getPlayerRC()).top) / 2.0f, _clippingRaius, _clippingRaius);
		SelectObject(_moveMapImg->getMemDC(), oldBrush);
		DeleteObject(magenta);
		_moveMapImg->render(getMemDC());
	}
}