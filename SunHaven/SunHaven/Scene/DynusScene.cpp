// Á¤¼ºÁø
#include "Stdafx.h"
#include "DynusScene.h"
#include "../Class/UI/UI.h"

HRESULT DynusScene::init(void)
{

	IMAGEMANAGER->addImage("DynusMapCollision", "DynusMapCollision.bmp", 1320, 816);
	_player = new Player;
	_player->init(CENTER_X, CENTER_Y + 200, "DynusMapCollision");

	_dynus = new Dynus;

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(1320 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(816 - WINSIZE_Y / 2);

	for (int i = 0; i < 4; i++)
	{
		_rcStar[i] = RectMake(960 * (i % 2), 400 * (i / 2), 960, 400);
	}

	_loopImg = IMAGEMANAGER->addImage("StarShader", "Resources/Images/Layer/StarShader.bmp",
		960, 400);
	_offsetX = _offsetY = 0.0f;
	_em = new EnemyManager;
	_dynus->setEnemyManagerMemoryAddress(_em);
	_em->setPlayerMemoryAddress(_player);
	_dynus->setPlayerMemoryAddress(_player);
	_dynus->init();

	_ui = new UI;
	_ui->init("Dynus");

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
	_player->update();
	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->update();
	_player->worldToCamera(CAMERA->worldToCamera
	(_player->getPlayerPosition()));
	_dynus->update();
	_em->update();

	static float offsetXDirection = 1.0f;
	_offsetX += 0.5f * offsetXDirection;

	if (_offsetX >= 100.0f || _offsetX <= -100.0f)
	{
		offsetXDirection *= -1.0f;
	}

	collision();
}

void DynusScene::render(void)
{
	for (int i = 0; i < 4; i++)
	{
		_loopImg->loopRender(getMemDC(), &_rcStar[i],
			CAMERA->worldToCameraX(_offsetX), CAMERA->worldToCameraY(_offsetY));
	}

	/*IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 0, 0, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 960, 0, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 960, 400, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 0, 400, 250);*/
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraX(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(402), CAMERA->worldToCameraX(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(402), CAMERA->worldToCameraX(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(804), CAMERA->worldToCameraX(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(804), CAMERA->worldToCameraX(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(1206), CAMERA->worldToCameraX(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(1206), CAMERA->worldToCameraX(402), 150);
	//IMAGEMANAGER->render("StarShader", getMemDC(), 0, 400);
	//IMAGEMANAGER->alphaRender("StarShaderTest", getMemDC(), 0, 0, 150);
	//IMAGEMANAGER->render("DynusLayer0", getMemDC(), 0, 0, 30, 95, WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->alphaRender("DynusLayer0", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraX(0),
		30, 95, WINSIZE_X, WINSIZE_Y, _dynus->getBgAlpha());

	_em->render();
	_dynus->drawPlatform();
	//_dynus->drawGuardMine();
	_player->render();
	_dynus->render();

	_ui->render();
}