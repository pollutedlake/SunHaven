// 김성의
#include "Stdafx.h"
#include "ShopScene.h"


HRESULT ShopScene::init(void)
{
	IMAGEMANAGER->addImage("충돌", "Shop_Bg_Collision.bmp", WINSIZE_X, WINSIZE_Y);
	_player = new Player;
	_player->init(700,500);
	
	_solonRc = RectMake(600, 320, 100, 100);
	_shopBg = RectMake(WINSIZE_X / 2 - 261, WINSIZE_Y / 2 - 327, 522, 654);

	_ID = new ItemData;
	_ID->init();

	for (int i = 0; i < 6; i++)
	{
		if (i < 4)
		{
			_vWeapon.push_back(_ID->getWeapon()->front());
			_ID->getWeapon()->pop();
		}

		if (i == 4)
		{
			_vAccessory.push_back(_ID->getAccessory()->front());
			_ID->getAccessory()->pop();

		}

		if (i == 5)
		{
			_vConsumable.push_back(_ID->getConsumable()->front());
			_ID->getConsumable()->pop();

		}
	}
	
	
	// 쇠뇌 /아다만트 쇠뇌/ 검 /아다만트 검/ 아다만트 반지/ 쿠키

	shopList temp;


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			
			if (i < 2)
			{
				temp._rc = RectMake(_shopBg.left + 25 + 241 * j, _shopBg.top + 60 + (10 + 103 * i), 231, 93);
				temp._name = _vWeapon[i * 2 + j]->name;
				temp._buyGold = _vWeapon[i * 2 + j]->gold;
				temp._sellGold = _vWeapon[i * 2 + j]->sellGold;
				 
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
					temp._name = _vAccessory.front()->name;
					temp._buyGold = _vAccessory.front()->gold;
					temp._sellGold = _vAccessory.front()->sellGold;
					
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
					temp._name = _vConsumable.front()->name;
					temp._buyGold = _vConsumable.front()->gold;
					temp._sellGold = _vConsumable.front()->sellGold;
					
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
	
}

void ShopScene::update(void)
{
	_player->update();

	cout << _vShopList[0]._name.c_str() << endl;

	
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Dynus");
	}
}

void ShopScene::render(void)
{
	IMAGEMANAGER->render("Shop_Bg", getMemDC());
	_player->render();
	DrawRectMake(getMemDC(), _solonRc);
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

		IMAGEMANAGER->render(_vShopList[i]._name.c_str(), getMemDC(), _vShopList[i]._rc.left + 20, _vShopList[i]._rc.top + 40);

		IMAGEMANAGER->render("UI_icon_coin", getMemDC(), _vShopList[i]._rc.right - 15, _vShopList[i]._rc.top + 5);
		//FONTMANAGER->textOut(getMemDC(), _playerStat[0].left + 15, _playerStat[0].top, "배달의민족 을지로체", 12, 5, "체력", strlen("체력"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), _vShopList[i]._rc.left + 5, _vShopList[i]._rc.top + 6, "", 12, 5, const_cast <char*> (_vShopList[i]._name.c_str()), strlen(_vShopList[i]._name.c_str()), RGB(255, 255, 255));
		
		FONTMANAGER->textOut(getMemDC(), (_vShopList[i]._rc.right - 5 -_vShopList[i]._buyGold + 48), _vShopList[i]._rc.top + 6, "", 12, 5, (char*)(_vShopList[i]._buyGold + 48), strlen((char*)(_vShopList[i]._buyGold + 48)), RGB(255, 255, 255));


		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				IMAGEMANAGER->render("x1_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
			}

			if (j == 1)
			{
				IMAGEMANAGER->render("x5_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
			}

			if (j == 2)
			{
				IMAGEMANAGER->render("x20_button", getMemDC(), _vShopList[i]._buttonRc[j].left, _vShopList[i]._buttonRc[j].top);
			}

		}



	}


}

