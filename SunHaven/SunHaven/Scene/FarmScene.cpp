// 민용식
#include "Stdafx.h"
#include "FarmScene.h"
#include "../Class/UI/UI.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("농장", "FarmMap.bmp", 3600, 3600);
	IMAGEMANAGER->addImage("충돌", "FarmMapCollision.bmp", 3600, 3600);

	_player = new Player;
	_player->init(2400, 1400, "충돌");

	

	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(3276 - WINSIZE_X / 2);
	_camera->setLimitBottom(3600 - WINSIZE_Y / 2);

	_om = new ObjectManager;
	_om->init();
	_om->setCameraAddress(_camera);



	_player->setPlayerPosition(PointMake(2496, 1500));

	_MouseOver = IMAGEMANAGER->addImage("오브젝트 선택",
		"Resources/Images/Player/ObjectMouseOver.bmp",
		36, 36, true, RGB(255, 0, 255));

	_MouseRC = RectMakeCenter(_camera->cameraToWorld(_ptMouse).x,
		_camera->cameraToWorld(_ptMouse).y,
		_MouseOver->getWidth(), _MouseOver->getHeight());

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

	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		_player->UseTool(_om, _ptMouse);
	_player->UseToolAnim(KEYMANAGER->isStayKeyDown(VK_LBUTTON));

	_player->UseFishingLod(_camera->cameraToWorld(_ptMouse));

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Shop");
	}
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), 0, 0, _camera->getPosition().x - WINSIZE_X / 2,
		_camera->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);
	// 정렬된 순서로 렌더
	while (!_vRenderList.empty())
	{
		_vRenderList.top().first->render();
		_vRenderList.pop();
	}


	
	_player->MouseOver(_om, _ptMouse);


	_om->render();


	if (KEYMANAGER->isToggleKey('Q'))
	{
		IMAGEMANAGER->render("충돌", getMemDC(), _camera->worldToCameraX(0),
			_camera->worldToCameraY(0));
	}
	_ui->render();
}

void FarmScene::Collision(void)
{
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;

		if (IntersectRect(&temp,
			&RectMakeCenter(_player->getPlayerPosition().x,
				_player->getPlayerPosition().y,48,52),
			&_om->getObjectList()[i]->getRC()))
		{
			cout << "충돌" << endl;
		}
	}
}