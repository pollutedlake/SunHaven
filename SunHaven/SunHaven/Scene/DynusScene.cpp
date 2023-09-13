// Á¤¼ºÁø
#include "Stdafx.h"
#include "DynusScene.h"

HRESULT DynusScene::init(void)
{

	IMAGEMANAGER->addImage("DynusMapCollision", "DynusMapCollision.bmp", 1280, 720);
	_player = new Player;
	_player->init(CENTER_X, CENTER_Y + 200, "DynusMapCollision");

	_dynus = new Dynus;

	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(1280 - WINSIZE_X / 2);
	_camera->setLimitBottom(720 - WINSIZE_Y / 2);

	_em = new EnemyManager;
	_dynus->setEnemyManagerMemoryAddress(_em);
	_em->setPlayerMemoryAddress(_player);
	_dynus->setPlayerMemoryAddress(_player);
	_dynus->init();

	wsprintf(_text, "DynusScene");
	return S_OK;
}

void DynusScene::release(void)
{
	_dynus->release();
	_em->release();
	_player->release();
	_camera->release();

	SAFE_DELETE(_player);
	SAFE_DELETE(_dynus);
	SAFE_DELETE(_em);
	SAFE_DELETE(_camera);
}

void DynusScene::update(void)
{
	_player->update();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->update();
	_player->worldToCamera(_camera->worldToCamera
	(_player->getPlayerPosition()));
	_dynus->update();
	_em->update();

	collision();
}

void DynusScene::render(void)
{
	IMAGEMANAGER->render("StarShader", getMemDC(), 0, 0);
	IMAGEMANAGER->render("StarShader", getMemDC(), 960, 0);
	IMAGEMANAGER->render("StarShader", getMemDC(), 960, 400);
	//IMAGEMANAGER->render("StarShader", getMemDC(), 0, 400);
	IMAGEMANAGER->render("StarShaderTest", getMemDC(), 0, 0);
	//IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), 0, 0, 200);
	IMAGEMANAGER->render("DynusLayer0", getMemDC(), 0, 0, 30, 95, WINSIZE_X, WINSIZE_Y);
	_em->render();
	_dynus->drawPlatform();
	_player->render();
	_dynus->render();
}