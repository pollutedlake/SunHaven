// 김성의
#include "Stdafx.h"
#include "ShopScene.h"


HRESULT ShopScene::init(void)
{
	IMAGEMANAGER->addImage("Shop_Bg_Collision", "Shop_Bg_Collision.bmp", WINSIZE_X, WINSIZE_Y);
	_player = new Player;
	_player->init(700,500, "Shop_Bg_Collision");

	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(1280 - WINSIZE_X / 2);
	_camera->setLimitBottom(720 - WINSIZE_Y / 2);
	
	_solonRc = RectMake(600, 320, 100, 100);
	_shopBg = RectMake(WINSIZE_X / 2 - 261, WINSIZE_Y / 2 - 327, 522, 654);


	shopList temp;


	for (int i = 0; i < 3; i++)
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
				
			_vShopList.push_back(temp);
		}
	}

	return S_OK;
}

void ShopScene::release(void)
{
	_player->release();
    SAFE_DELETE(_player);

	_camera->release();
	SAFE_DELETE(_camera);
	
}

void ShopScene::update(void)
{
	_player->update();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->update();
	_player->worldToCamera(_camera->worldToCamera
	(_player->getPlayerPosition()));

	if (KEYMANAGER->isToggleKey('E'))
	{
		for (int i = 0; i < _vShopList.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (PtInRect(&(_vShopList[i]._buttonRc[j]), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					switch (j)
					{
					case 0:
						_player->getInven()->getItem(_vShopList[i]._index);
						break;

					case 1:
						for (int k = 0; k < 5; k++)
						{
							_player->getInven()->getItem(_vShopList[i]._index);
						}

						break;

					case 2:
						for (int l = 0; l < 20; l++)
						{
							_player->getInven()->getItem(_vShopList[i]._index);
						}
						break;
					}
				}
			}

		}
	}
	


	
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Dynus");
	}
}

void ShopScene::render(void)
{
	IMAGEMANAGER->render("Shop_Bg", getMemDC());
	_player->render();
	
	RECT temp;

	if (IntersectRect(&temp, &_player->getPlayerRC(), &_solonRc))
	{
		if(KEYMANAGER->isToggleKey('E'))
		{
			
			shopMold();
			shopSlot();
		}
	}
	
	
	IMAGEMANAGER->render("Cursor", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void ShopScene::shopMold()
{
	IMAGEMANAGER->render("store_bg", getMemDC(), _shopBg.left, _shopBg.top);
	IMAGEMANAGER->render("store_upper_icon_wip", getMemDC(), WINSIZE_X / 2 - 250, WINSIZE_Y / 2 - 347);

	
}

void ShopScene::shopSlot()
{
	for (int i = 0; i < 6; i++)
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
		FONTMANAGER->textOut(getMemDC(), _vShopList[i]._rc.left + 5, _vShopList[i]._rc.top + 6, "", 12, 5, const_cast <char*> (_vShopList[i]._name.c_str()), strlen(_vShopList[i]._name.c_str()), RGB(255, 255, 255));
		char showGold[2000];
		
		if (PtInRect(&_vShopList[i]._buttonRc[2], _ptMouse))
		{
			sprintf_s(showGold, "%d", (_vShopList[i]._buyGold * 20));
			FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 55), _vShopList[i]._rc.top + 6, "", 12, 5, showGold, strlen(showGold), RGB(255, 255, 255));

		}
		else if (PtInRect(&_vShopList[i]._buttonRc[1], _ptMouse))
		{
			sprintf_s(showGold, "%d", (_vShopList[i]._buyGold * 5));
			FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 55), _vShopList[i]._rc.top + 6, "", 12, 5, showGold , strlen(showGold), RGB(255, 255, 255));

		}
		else
		{
			sprintf_s(showGold, "%d", (_vShopList[i]._buyGold));
			FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 50), _vShopList[i]._rc.top + 6, "", 12, 5, showGold, strlen(showGold), RGB(255, 255, 255));

		}
		

		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				//소지골드에 따라 버튼활성화추가예정
				IMAGEMANAGER->render("x1_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
				FONTMANAGER->textOut(getMemDC(), _vShopList[i]._buttonRc[j].left + 5, _vShopList[i]._buttonRc[j].top + 3, "", 10, 5, "x1", strlen("x1"), RGB(255, 255, 255));
			}

			if (j == 1)
			{
				IMAGEMANAGER->render("x5_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
				FONTMANAGER->textOut(getMemDC(), _vShopList[i]._buttonRc[j].left + 5, _vShopList[i]._buttonRc[j].top + 3, "", 10, 5, "x5", strlen("x5"), RGB(255, 255, 255));
			}

			if (j == 2)
			{
				IMAGEMANAGER->render("x20_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
				FONTMANAGER->textOut(getMemDC(), _vShopList[i]._buttonRc[j].left + 5, _vShopList[i]._buttonRc[j].top + 3, "", 10, 5, "x20", strlen("x20"), RGB(255, 255, 255));
			}

		}



	}


}

