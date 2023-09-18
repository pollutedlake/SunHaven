// 김성의
#include "Stdafx.h"
#include "ShopScene.h"
#include "../Class/UI/UI.h"

HRESULT ShopScene::init(void)
{
	IMAGEMANAGER->addImage("Shop_Bg_Collision", "Shop_Bg_Collision.bmp", WINSIZE_X, WINSIZE_Y);
	_player = new Player;
	_player->init(700,500, "Shop_Bg_Collision");
	_player->setPlayerState(DATAMANAGER->getPlayereState());
	SOUNDMANAGER->play("Salon_Final1", 0.5f);
	CAMERA->init();
	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(1280 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(720 - WINSIZE_Y / 2);
	
	_solonRc = RectMake(600, 320, 100, 100);
	_shopBg = RectMake(WINSIZE_X / 2 - 261, WINSIZE_Y / 2 - 327, 522, 654);

	_inven = new Inventory;
	_inven->init();
	_inven->setInvenList(DATAMANAGER->getInvenList());
	_inven->setEuqipmentList(DATAMANAGER->getEquipmentList());

	_inven->setPlayerAdsress(_player);
	shopList temp;


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			
			if (i < 2)
			{
				temp._rc = RectMake(_shopBg.left + 25 + 241 * j, _shopBg.top + 60 + (10 + 103 * i), 231, 93);
				temp._name = DATAMANAGER->getWeaponInfo(i * 2 + j)->name;
				temp._buyGold = DATAMANAGER->getWeaponInfo(i * 2 + j)->gold;
				temp._sellGold = DATAMANAGER->getWeaponInfo(i * 2 + j)->sellGold;
				temp._grade = DATAMANAGER->getWeaponInfo(i * 2 + j)->grade;
				temp._index = DATAMANAGER->getWeaponInfo(i * 2 + j)->index;
				for (int k = 0; k < 3; k++)
				{
					if (k == 0)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 93, temp._rc.top + 45, 22 + k, 20);
					}

					if (k == 1)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 65, temp._rc.top + 45, 22 + k, 20);
					}

					if(k == 2)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right -38, temp._rc.top + 45, 22 + k * 6, 20);
					}

				}
				
			}
			
			if(i == 2)
			{
				if (j < 1)
				{
					temp._rc = RectMake(_shopBg.left + 25 + 241 * j, _shopBg.top + 60 + (10 + 103 * i), 231, 93);
					temp._name = DATAMANAGER->getAccessoryInfo(j)->name;
					temp._buyGold = DATAMANAGER->getAccessoryInfo(j)->gold;
					temp._sellGold = DATAMANAGER->getAccessoryInfo(j)->sellGold;
					temp._grade = DATAMANAGER->getAccessoryInfo(j)->grade;
					temp._index = DATAMANAGER->getAccessoryInfo(j)->index;
					for (int k = 0; k < 3; k++)
					{
						if (k == 0)
						{
							temp._buttonRc[k] = RectMake(temp._rc.right - 93, temp._rc.top + 45, 22 + k, 20);
						}

						if (k == 1)
						{
							temp._buttonRc[k] = RectMake(temp._rc.right - 65, temp._rc.top + 45, 22 + k, 20);
						}

						if (k == 2)
						{
							temp._buttonRc[k] = RectMake(temp._rc.right - 38, temp._rc.top + 45, 22 + k * 6, 20);
						}

					}
					
				}
				
				if(j==1)
				{
					temp._rc = RectMake(_shopBg.left + 25 + 241 * j, _shopBg.top + 60 + (10 + 103 * i), 231, 93);
					temp._name = DATAMANAGER->getConsumableInfo(0)->name;
					temp._buyGold = DATAMANAGER->getConsumableInfo(0)->gold;
					temp._sellGold = DATAMANAGER->getConsumableInfo(0)->sellGold;
					temp._grade = "커먼";
					temp._index = DATAMANAGER->getConsumableInfo(0)->index;
					for (int k = 0; k < 3; k++)
					{
						if (k == 0)
						{
							temp._buttonRc[k] = RectMake(temp._rc.right - 93, temp._rc.top + 45, 22 + k, 20);
						}

						if (k == 1)
						{
							temp._buttonRc[k] = RectMake(temp._rc.right - 65, temp._rc.top + 45, 22 + k, 20);
						}

						if (k == 2)
						{
							temp._buttonRc[k] = RectMake(temp._rc.right - 38, temp._rc.top + 45, 22 + k * 6, 20);
						}

					}
					
				}
			}

			if (i == 3)
			{
				temp._rc = RectMake(_shopBg.left + 25 + 241 * j, _shopBg.top + 60 + (10 + 103 * i), 231, 93);
				temp._name = DATAMANAGER->getArmorInfo(j)->name;
				temp._buyGold = DATAMANAGER->getArmorInfo(j)->gold;
				temp._sellGold = DATAMANAGER->getArmorInfo(j)->sellGold;
				temp._grade = "레어";
				temp._index = DATAMANAGER->getArmorInfo(j)->index;
				for (int k = 0; k < 3; k++)
				{
					if (k == 0)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 93, temp._rc.top + 45, 22 + k, 20);
					}

					if (k == 1)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 65, temp._rc.top + 45, 22 + k, 20);
					}

					if (k == 2)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 38, temp._rc.top + 45, 22 + k * 6, 20);
					}

				}
			}

			if (i == 4)
			{
				temp._rc = RectMake(_shopBg.left + 25 + 241 * j, _shopBg.top + 60 + (10 + 103 * i), 231, 93);
				temp._name = DATAMANAGER->getArmorInfo(j +2)->name;
				temp._buyGold = DATAMANAGER->getArmorInfo(j+2)->gold;
				temp._sellGold = DATAMANAGER->getArmorInfo(j+2)->sellGold;
				temp._grade = "레어";
				temp._index = DATAMANAGER->getArmorInfo(j+2)->index;
				for (int k = 0; k < 3; k++)
				{
					if (k == 0)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 93, temp._rc.top + 45, 22 + k, 20);
					}

					if (k == 1)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 65, temp._rc.top + 45, 22 + k, 20);
					}

					if (k == 2)
					{
						temp._buttonRc[k] = RectMake(temp._rc.right - 38, temp._rc.top + 45, 22 + k * 6, 20);
					}

				}
			}
				
			_vShopList.push_back(temp);
		}
	}
	_ui = new UI;
	_ui->init("Mine");
	_ui->setAdressPlayer(_player);
	_moveMap = true;
	_portal = RectMake( 660, 560, 110, 40);
	_clippingRaius = 0.0f;
	_moveMapImg = IMAGEMANAGER->addImage("MoveMap", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_enterScene = true;
	return S_OK;
}

void ShopScene::release(void)
{
	_player->release();
    SAFE_DELETE(_player);
	
}

void ShopScene::update(void)
{
	SOUNDMANAGER->update();
	_player->update();
	_inven->update();
	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->update();
	_player->worldToCamera(CAMERA->worldToCamera
		(_player->getPlayerPosition()));

	_player->setGold(_inven->getSellGold());

	
	if(!_moveMap)
	{



		if (KEYMANAGER->isToggleKey('E'))
		{
			for (int i = 0; i < _vShopList.size(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (PtInRect(&(_vShopList[i]._buttonRc[j]), _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
					{
						switch (j)
						{
						case 0:
							_inven->getItem(_vShopList[i]._index);
							_player->setGold(-_vShopList[i]._buyGold);
							break;

						case 1:
							for (int k = 0; k < 5; k++)
							{
								_inven->getItem(_vShopList[i]._index);
								_player->setGold(-_vShopList[i]._buyGold);
							}

							break;

						case 2:
							for (int l = 0; l < 20; l++)
							{
								_inven->getItem(_vShopList[i]._index);
								_player->setGold(-_vShopList[i]._buyGold);
							}
							break;
						}
					}
				}

			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_inven->itemMove();
				_inven->invenXButton();
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_inven->putItem();
			}
		}

		if (PtInRect(&_portal, _player->getPlayerPosition()))
		{
			_moveMap = true;
			SOUNDMANAGER->play("SceneTransition1", 1.0f);
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
				SOUNDMANAGER->stop("Salon_Final1");
				SCENEMANAGER->changeScene("Mine");
				DATAMANAGER->setData(_player->getPlayerState(), _inven->getInvenList(), _inven->getEquipmentList());
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->stop("Salon_Final1");
		SOUNDMANAGER->play("SceneTransition1", 1.0f);
		DATAMANAGER->setData(_player->getPlayerState(), _inven->getInvenList(), _inven->getEquipmentList());
		SCENEMANAGER->changeScene("Mine");
	}
}

void ShopScene::render(void)
{
	IMAGEMANAGER->render("Shop_Bg", getMemDC());
	_player->render();
	_inven->render();
	_inven->setCurrentSlot();
	RECT temp;

	if (IntersectRect(&temp, &_player->getPlayerRC(), &_solonRc))
	{
		if(KEYMANAGER->isToggleKey('E'))
		{
			
			shopMold();
			shopSlot();
		}
	}

	_ui->render();
	char att[2000];
	sprintf_s(att, "%d", (_player->getAttackDamage()));
	char def[2000];
	sprintf_s(def, "%d", (_player->getDefense()));
	char hp[2000];
	sprintf_s(hp, "%d", (_player->getHP()));
	char mp[2000];
	sprintf_s(mp, "%d", (_player->getMaxMP()));

	if (_inven->getSeeInven())
	{
		FONTMANAGER->textOut(getMemDC(), _inven->getPlayerStatSlot1().left + 75, _inven->getPlayerStatSlot1().top, "배달의민족 을지로체", 12, 5, hp, strlen(hp), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), _inven->getPlayerStatSlot2().left + 75, _inven->getPlayerStatSlot2().top, "배달의민족 을지로체", 12, 5, mp, strlen(mp), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), _inven->getPlayerStatSlot3().left + 75, _inven->getPlayerStatSlot3().top, "배달의민족 을지로체", 12, 5, def, strlen(def), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), _inven->getPlayerStatSlot4().left + 75, _inven->getPlayerStatSlot4().top, "배달의민족 을지로체", 12, 5, att, strlen(att), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), _inven->getPlayerStatSlot5().left + 75, _inven->getPlayerStatSlot5().top, "배달의민족 을지로체", 12, 5, att, strlen(att), RGB(255, 255, 255));
	}
	
	
	IMAGEMANAGER->render("Cursor", getMemDC(), _ptMouse.x, _ptMouse.y);
	if (_moveMap)
	{
		PatBlt(_moveMapImg->getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		HBRUSH magenta = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_moveMapImg->getMemDC(), magenta);
		//EllipseMakeCenter(_moveMapImg->getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _clippingRaius, _clippingRaius);
		EllipseMakeCenter(_moveMapImg->getMemDC(), (CAMERA->worldToCameraRect(_player->getPlayerRC()).right + CAMERA->worldToCameraRect(_player->getPlayerRC()).left) / 2.0f,
			(CAMERA->worldToCameraRect(_player->getPlayerRC()).bottom + CAMERA->worldToCameraRect(_player->getPlayerRC()).top) / 2.0f, _clippingRaius, _clippingRaius);
		SelectObject(_moveMapImg->getMemDC(), oldBrush);
		DeleteObject(magenta);
		_moveMapImg->render(getMemDC());
	}
}

void ShopScene::shopMold()
{
	IMAGEMANAGER->render("store_bg", getMemDC(), _shopBg.left, _shopBg.top);
	IMAGEMANAGER->render("store_upper_icon_wip", getMemDC(), WINSIZE_X / 2 - 250, WINSIZE_Y / 2 - 347);
	IMAGEMANAGER->render("goldbanner", getMemDC(), _shopBg.right, _shopBg.top + 60);
	char addGold[2000];
	sprintf_s(addGold, "%d", (_player->getGold()));
	FONTMANAGER->textOut(getMemDC(), _shopBg.right + 70, _shopBg.top + 70, "배달의민족 을지로체", 15, 5, addGold, strlen(addGold), RGB(255, 255, 255));
}

void ShopScene::shopSlot()
{
	for (int i = 0; i < 10; i++)
	{
		IMAGEMANAGER->render("store_item_bg", getMemDC(), _vShopList[i]._rc.left, _vShopList[i]._rc.top);

		if (_vShopList[i]._grade == "커먼")
		{
			IMAGEMANAGER->render("item_bg_common", getMemDC(), _vShopList[i]._rc.left + 20, _vShopList[i]._rc.top + 40);
		}
		else
		{
			IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vShopList[i]._rc.left + 20, _vShopList[i]._rc.top + 40);
		}
		IMAGEMANAGER->render(_vShopList[i]._name.c_str(), getMemDC(), _vShopList[i]._rc.left + 20, _vShopList[i]._rc.top + 40);

		IMAGEMANAGER->render("UI_icon_coin", getMemDC(), _vShopList[i]._rc.right - 15, _vShopList[i]._rc.top + 5);
		//FONTMANAGER->textOut(getMemDC(), _playerStat[0].left + 15, _playerStat[0].top, "배달의민족 을지로체", 12, 5, "체력", strlen("체력"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), _vShopList[i]._rc.left + 5, _vShopList[i]._rc.top + 6, "배달의민족 을지로체", 12, 5, const_cast <char*> (_vShopList[i]._name.c_str()), strlen(_vShopList[i]._name.c_str()), RGB(255, 255, 255));
		char showGold[2000];
		
		if (PtInRect(&_vShopList[i]._buttonRc[2], _ptMouse))
		{
			sprintf_s(showGold, "%d", (_vShopList[i]._buyGold * 20));
			FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 55), _vShopList[i]._rc.top + 6, "배달의민족 을지로체", 12, 5, showGold, strlen(showGold), RGB(255, 255, 255));

		}
		else if (PtInRect(&_vShopList[i]._buttonRc[1], _ptMouse))
		{
			sprintf_s(showGold, "%d", (_vShopList[i]._buyGold * 5));
			FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 55), _vShopList[i]._rc.top + 6, "배달의민족 을지로체", 12, 5, showGold , strlen(showGold), RGB(255, 255, 255));

		}
		else
		{
			sprintf_s(showGold, "%d", (_vShopList[i]._buyGold));
			FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 50), _vShopList[i]._rc.top + 6, "배달의민족 을지로체", 12, 5, showGold, strlen(showGold), RGB(255, 255, 255));

		}
		

		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				//소지골드에 따라 버튼활성화추가예정
				IMAGEMANAGER->render("x1_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
				FONTMANAGER->textOut(getMemDC(), _vShopList[i]._buttonRc[j].left + 5, _vShopList[i]._buttonRc[j].top + 3, "배달의민족 을지로체", 10, 5, "x1", strlen("x1"), RGB(255, 255, 255));
			}

			if (j == 1)
			{
				IMAGEMANAGER->render("x5_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
				FONTMANAGER->textOut(getMemDC(), _vShopList[i]._buttonRc[j].left + 5, _vShopList[i]._buttonRc[j].top + 3, "배달의민족 을지로체", 10, 5, "x5", strlen("x5"), RGB(255, 255, 255));
			}

			if (j == 2)
			{
				IMAGEMANAGER->render("x20_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
				FONTMANAGER->textOut(getMemDC(), _vShopList[i]._buttonRc[j].left + 5, _vShopList[i]._buttonRc[j].top + 3, "배달의민족 을지로체", 10, 5, "x20", strlen("x20"), RGB(255, 255, 255));
			}

		}



	}


}

