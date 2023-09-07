// 정성진
#include "Stdafx.h"
#include "DynusScene.h"

HRESULT DynusScene::init(void)
{
	IMAGEMANAGER->addImage("충돌", "FarmMapCollision.bmp", 3600, 3600);
	_player = new Player;

	_dynus = new Dynus;

	//_player->setEnemyMangerMemoryAddress(_dynus);

	/*_shadeclaw = new Shadeclaw;
	_shadeclaw->setPlayerMemoryAddress(_player);*/

	_em = new EnemyManager;
	_dynus->setEnemyManagerMemoryAddress(_em);
	_em->setPlayerMemoryAddress(_player);
	_dynus->setPlayerMemoryAddress(_player);
	_player->init(CENTER_X, CENTER_Y + 250);
	_dynus->init();

	wsprintf(_text, "DynusScene");

	return S_OK;
}

void DynusScene::release(void)
{
	_dynus->release();
	_em->release();

	SAFE_DELETE(_player);
	SAFE_DELETE(_shadeclaw);
}

void DynusScene::update(void)
{
	_dynus->update();
	_player->update();
	_em->update();

	collision();
}

void DynusScene::render(void)
{
	//IMAGEMANAGER->render("StarShader", getMemDC(), 0, 0);
	//IMAGEMANAGER->render("StarShader", getMemDC(), 0, 400);
	IMAGEMANAGER->render("StarShaderTest", getMemDC(), 0, 0);
	//IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), 0, 0, 200);
	IMAGEMANAGER->render("DynusLayer0", getMemDC(), 0, 0, 30, 95, WINSIZE_X, WINSIZE_Y);
	_dynus->render();
	_em->render();
	_player->render();
}