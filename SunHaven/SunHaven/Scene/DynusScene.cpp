// 정성진
#include "Stdafx.h"
#include "DynusScene.h"
#include "../Class/UI/UI.h"

HRESULT DynusScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("다이너스", "./Resources/Data/Map/DynusMap.bmp", 2400, 2400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("DynusMapCollision", "./Resources/Data/Map/DynusMapCollision.bmp", 2400, 2400);
	_player = new Player;
	_player->init(CENTER_X, CENTER_Y + 200, "DynusMapCollision");

	_dynus = new Dynus;

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(1320 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(816 - WINSIZE_Y / 2);

	for (int i = 0; i < 8; i++)
	{
		_rcStar[i] = RectMake(402 * (i % 4), 402 * (i / 4), 402, 402);
	}

	_loopImg = IMAGEMANAGER->addImage("BlueStarFill", "Resources/Images/Layer/StarShader.bmp",
		402, 402);
	_offsetX = _offsetY = 0.0f;
	_em = new EnemyManager;
	_dynus->setEnemyManagerMemoryAddress(_em);
	_em->setPlayerMemoryAddress(_player);
	_dynus->setPlayerMemoryAddress(_player);
	_dynus->init();

	_ui = new UI;
	_ui->init("Dynus");
	_ui->setAdressPlayer(_player);

	wsprintf(_text, "DynusScene");
	
	return S_OK;
}

void DynusScene::release(void)
{
	_dynus->release();
	_em->release();
	_player->release();

	_player->release();
	SAFE_DELETE(_player);
	SAFE_DELETE(_dynus);
	SAFE_DELETE(_em);
}

void DynusScene::update(void)
{
	SOUNDMANAGER->update();
	_player->update();
	CAMERA->setPosition(_player->getPlayerPosition());
	//CAMERA->update();
	_player->worldToCamera(CAMERA->worldToCamera
	(_player->getPlayerPosition()));
	_dynus->update();
	if (!_dynus->getIsDie())
	{
		_em->update();
	}
	/*if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_player->UseTool(_om, _ptMouse);
		_inven->itemMove();
	}*/
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{

	}
	_player->UseToolAnim(KEYMANAGER->isStayKeyDown(VK_LBUTTON));
	collision();

	static float offsetXDirection = 1.0f;
	_offsetX += 0.5f * offsetXDirection;

	if (_offsetX >= 100.0f || _offsetX <= -100.0f)
	{
		offsetXDirection *= -1.0f;
	}
}

void DynusScene::render(void)
{
	for (int i = 0; i < 8; i++)
	{
		_loopImg->loopRender(getMemDC(), &_rcStar[i],
			_offsetX, _offsetY);
	}

	/*IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 0, 0, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 960, 0, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 960, 400, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 0, 400, 250);*/
	/*IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraY(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(402), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(402), CAMERA->worldToCameraY(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(804), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(804), CAMERA->worldToCameraY(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(1206), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(1206), CAMERA->worldToCameraY(402), 150);*/
	//IMAGEMANAGER->render("StarShader", getMemDC(), 0, 400);
	//IMAGEMANAGER->alphaRender("StarShaderTest", getMemDC(), 0, 0, 150);
	//IMAGEMANAGER->render("DynusLayer0", getMemDC(), 0, 0, 30, 95, WINSIZE_X, WINSIZE_Y);
	//IMAGEMANAGER->alphaRender("DynusLayer0", getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2, CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y, _dynus->getBgAlpha());
	_bg->alphaRender(getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2, CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y, _dynus->getBgAlpha());
	if (!_dynus->getIsDie())
	{
		_em->render();
	}
	if (_dynus->getIsPlatform())
	{
		IMAGEMANAGER->render("DynusGuardPlatformL", getMemDC(), CAMERA->worldToCameraX(65), CAMERA->worldToCameraY(CENTER_Y + 45));
		IMAGEMANAGER->render("DynusGuardPlatformR", getMemDC(), CAMERA->worldToCameraX(WINSIZE_X - 95), CAMERA->worldToCameraY(CENTER_Y + 45));
		_dynus->drawPlatform();
	}
	_player->render();
	_dynus->render();
	_ui->render();
}