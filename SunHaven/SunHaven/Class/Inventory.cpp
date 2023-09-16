#include "Stdafx.h"
#include "Inventory.h"
//#include <string>


HRESULT Inventory::init(void)
{
	/*_ID = new ItemData;
	_ID->init();*/
	_sellGold = 0;
	_seeInven = false;

	_inInvenSlot = false;
	_inEquipmentSlot = false;
	
	_invenBG = RectMake(WINSIZE_X / 4, WINSIZE_Y / 4, WINSIZE_X / 2, WINSIZE_Y / 2);
	_playerBG = RectMake(_invenBG.left + 30, _invenBG.top + 50, WINSIZE_X / 6, WINSIZE_Y / 2 - 80);
	_playerName = RectMake(_playerBG.left, _playerBG.top - 20, 202, 20);
	_itemListBG = RectMake(_playerBG.right + 30, _playerBG.top, WINSIZE_X / 4 + 20, WINSIZE_Y / 2 - 80);
	_sortButton = RectMake(_itemListBG.left + 10, _itemListBG.bottom - 40, 26, 25);
	_dropButton = RectMake(_itemListBG.right - 75, _itemListBG.bottom - 40, 26, 25);
	_trashButton = RectMake(_itemListBG.right - 35, _itemListBG.bottom - 40, 26, 25);
	_xButton = RectMake(_invenBG.right - 27, _invenBG.top - 5, 27, 28);

	for (int i = 0; i < 5; i++)
	{
		_playerStat[i] = RectMake(_playerBG.left + 5, (_playerBG.top + 82) + 17 * i, 10, 10);
	}

	Slot itemUseSlot;

	for (int i = 0; i < 10; i++)
	{
		ZeroMemory(&itemUseSlot, sizeof(Slot));

		itemUseSlot._rc = RectMake(WINSIZE_X/2 -150 + 32*i, WINSIZE_Y -80, 32, 32);
		itemUseSlot._draw = false;
		itemUseSlot._category = "";
		itemUseSlot._currentStack = 0;

		_vItemUseSlot.push_back(itemUseSlot);

	}


	Slot  invenSlot;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ZeroMemory(&invenSlot, sizeof(Slot));

			invenSlot._rc = RectMake(_itemListBG.left + j * 42 + 7, _itemListBG.top + 10 + i * 42, 32, 32);
			invenSlot._draw = false;
			invenSlot._category = "";
			invenSlot._currentStack = 1;
		
			_vInvenList.push_back(invenSlot);

		}
	}

	Slot equipmentSlot;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ZeroMemory(&equipmentSlot, sizeof(Slot));

			if (i < 2)
			{
				equipmentSlot._rc = RectMake(_playerBG.right - 97 + i * 55, _playerBG.top + 40 + j * 50, 32, 32);
				equipmentSlot._draw = false;
				equipmentSlot._category = "";
				equipmentSlot._currentStack = 1;

				_vEquipmentSlot.push_back(equipmentSlot);
			}
			else
			{
				if (j == 0)
				{
					equipmentSlot._rc = RectMake(_playerBG.left + 13, _playerBG.bottom - 95, 32, 32);
					equipmentSlot._draw = false;
					equipmentSlot._category = "";
					equipmentSlot._currentStack = 1;

					_vEquipmentSlot.push_back(equipmentSlot);
				}

				if (j == 1)
				{
					equipmentSlot._rc = RectMake(_playerBG.left + 60, _playerBG.bottom - 95, 32, 32);
					equipmentSlot._draw = false;
					equipmentSlot._category = "";
					equipmentSlot._currentStack = 1;

					_vEquipmentSlot.push_back(equipmentSlot);
				}

				if (j == 2)
				{
					equipmentSlot._rc = RectMake(_playerBG.left + 13, _playerBG.bottom - 50, 32, 32);
					equipmentSlot._draw = false;
					equipmentSlot._category = "";
					equipmentSlot._currentStack = 1;

					_vEquipmentSlot.push_back(equipmentSlot);
				}

				if (j == 3)
				{
					equipmentSlot._rc = RectMake(_playerBG.left + 60, _playerBG.bottom - 50, 32, 32);
					equipmentSlot._draw = false;
					equipmentSlot._category = "";
					equipmentSlot._currentStack = 1;

					_vEquipmentSlot.push_back(equipmentSlot);
				}

				if (j == 4)
				{
					equipmentSlot._rc = {};

					_vEquipmentSlot.push_back(equipmentSlot);
				}
			}


		}
	}

	
	_selectedItem = -1;


	return S_OK;
}

void Inventory::release(void)
{
	
}

void Inventory::update(void)
{
	

	if (!_seeInven && KEYMANAGER->isOnceKeyDown('I'))
	{
		_seeInven = true;

	}
	else if (_seeInven && KEYMANAGER->isOnceKeyDown('I'))
	{
		_seeInven = false;
	}

	sellItem();

	
	/*for (int i = 0; i < 4; i++)
	{
		if(_vEquipmentSlot[i]._draw)
		_def = (DATAMANAGER->getArmorInfo((int)_vEquipmentSlot[0]._category[2])->defense) + (DATAMANAGER->getArmorInfo((int)_vEquipmentSlot[1]._category[2])->defense) + (DATAMANAGER->getArmorInfo((int)_vEquipmentSlot[2]._category[2])->defense) + (DATAMANAGER->getArmorInfo((int)_vEquipmentSlot[3]._category[2])->defense);

	}*/
}

void Inventory::render(void)
{
	for (int i = 0; i < 10; i++)
	{
		if (!_vItemUseSlot[i]._draw)
		{
			IMAGEMANAGER->render("item_bg_common", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
			switch (i)
			{
			case 0:
				IMAGEMANAGER->render("icon_scythe2", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 1:
				IMAGEMANAGER->render("녹슨 괭이", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 2:
				IMAGEMANAGER->render("녹슨 도끼", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 3:
				IMAGEMANAGER->render("녹슨 곡괭이", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 4:
				IMAGEMANAGER->render("검", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 5:
				IMAGEMANAGER->render("쇠뇌", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 6:
				IMAGEMANAGER->render("combat_skill_tree_icons_0", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 7:
				IMAGEMANAGER->render("combat_skill_tree_icons_6", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 8:
				IMAGEMANAGER->render("쿠키", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			case 9:
				IMAGEMANAGER->render("기본 낚싯대", getMemDC(), _vItemUseSlot[i]._rc.left, _vItemUseSlot[i]._rc.top);
				break;
			}
			
		}
		
	}
	
	if (_seeInven)
	{
		invenMold();

		invenSlot();

		equipment_Slot();

		moveItemRender();
		
		
	}
	
	popupItem();

	for (int i = 0; i < _vInvenList.size(); i++)
	{
		itemInfoPopup(i);
	}
	
}

void Inventory::getItem(string index)
{
	for (int i = 0; i < _vInvenList.size(); i++)
	{

		if (_vInvenList[i]._category[0] == '4' || _vInvenList[i]._category[0] == '5')
		{
			if (_vInvenList[i]._draw && _vInvenList[i]._category == index && _vInvenList[i]._currentStack < 255)
			{
				_vInvenList[i]._currentStack += 1;
				if (!SOUNDMANAGER->isPlaySound("E_getItem_Sound1"))
				{
					SOUNDMANAGER->play("E_getItem_Sound1", 1.0f);
				}
				
				break;
			}
			else if (!_vInvenList[i]._draw)
			{
				_vInvenList[i]._category = index;

				_vInvenList[i]._draw = true;

				_vInvenList[i]._currentStack + 1;
				if (!SOUNDMANAGER->isPlaySound("E_getItem_Sound1"))
				{
					SOUNDMANAGER->play("E_getItem_Sound1", 1.0f);
				}


				_lastItemTime = GetTickCount64();
				break;
			}
			
		}
		else if (!_vInvenList[i]._draw)
		{
			_vInvenList[i]._category = index;

			_vInvenList[i]._draw = true;
			if (!SOUNDMANAGER->isPlaySound("E_getItem_Sound1"))
			{
				SOUNDMANAGER->play("E_getItem_Sound1", 1.0f);
			}

			_lastItemTime = GetTickCount64();

			break;
		}

	}
}

void Inventory::itemMove()
{
	
	if (_seeInven)
	{
		//인벤칸
		// 해당하는 인덱스를 찾음
		int indexInven = -1;
		int indexEqui = -1;
		string temp = "";
		int shuffleStack = 0;
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, _ptMouse))
			{
				indexInven = i;
				
				break;
			}
		}

		//장비칸
		for (int j = 0; j < _vEquipmentSlot.size() - 1; j++)
		{
			if (PtInRect(&_vEquipmentSlot[j]._rc, _ptMouse) )
			{
				indexEqui = j;
				
				break;
			}
		}


		// 인덱스가 유효하고 아이템이 있으면 _selectedItem에 저장
		if (indexInven != -1 && _vInvenList[indexInven]._draw)
		{
			if (_selectedItem != -1)
			{
				if (_inInvenSlot)
				{
					
					temp = _vInvenList[indexInven]._category;
					_vInvenList[indexInven]._category = _vInvenList[_selectedItem]._category;
					_vInvenList[_selectedItem]._category = temp;

					shuffleStack = _vInvenList[indexInven]._currentStack;
					_vInvenList[indexInven]._currentStack = _vInvenList[_selectedItem]._currentStack;
					_vInvenList[_selectedItem]._currentStack = shuffleStack;
				}	

				if (_inEquipmentSlot)
				{
					temp = _vInvenList[indexInven]._category;
					_vInvenList[indexInven]._category = _vEquipmentSlot[_selectedItem]._category;
					_vEquipmentSlot[_selectedItem]._category = temp;

					shuffleStack = _vInvenList[indexInven]._currentStack;
					_vInvenList[indexInven]._currentStack = _vEquipmentSlot[_selectedItem]._currentStack;
					_vEquipmentSlot[_selectedItem]._currentStack = shuffleStack;
					
				}

			}
			else
			{
				_selectedItem = indexInven;
				_vInvenList[indexInven]._draw = false;

				shuffleStack = _vInvenList[indexInven]._currentStack;
				_vInvenList[indexInven]._currentStack = _vInvenList[_selectedItem]._currentStack;
				_vInvenList[_selectedItem]._currentStack = shuffleStack;

				_inInvenSlot = true;
				_inEquipmentSlot = false;
			}

		}

		
		if (indexEqui != -1 && _vEquipmentSlot[indexEqui]._draw)
		{
			if (_selectedItem != -1)
			{
				if (_inInvenSlot && _vInvenList[_selectedItem]._category[0] == '2' || _vInvenList[_selectedItem]._category[0] == '3')
				{
					temp = _vEquipmentSlot[indexEqui]._category;
					_vEquipmentSlot[indexEqui]._category = _vInvenList[_selectedItem]._category;
					_vInvenList[_selectedItem]._category = temp;	

					shuffleStack = _vEquipmentSlot[indexInven]._currentStack;
					_vEquipmentSlot[indexInven]._currentStack = _vInvenList[_selectedItem]._currentStack;
					_vInvenList[_selectedItem]._currentStack = shuffleStack;
					
				}

				if (_inEquipmentSlot)
				{
					temp = _vEquipmentSlot[indexEqui]._category;
					_vEquipmentSlot[indexEqui]._category = _vEquipmentSlot[_selectedItem]._category;
					_vEquipmentSlot[_selectedItem]._category = temp;

					shuffleStack = _vEquipmentSlot[indexInven]._currentStack;
					_vEquipmentSlot[indexInven]._currentStack = _vEquipmentSlot[_selectedItem]._currentStack;
					_vEquipmentSlot[_selectedItem]._currentStack = shuffleStack;

				}

			}
			else
			{
				_selectedItem = indexEqui;
				_vEquipmentSlot[indexEqui]._draw = false;
				_inEquipmentSlot = true;
				_inInvenSlot = false;
			}

		}

		
		if (PtInRect(&_trashButton, _ptMouse) && _selectedItem != -1)
		{
			if (_inInvenSlot)
			{
				_vInvenList[_selectedItem]._draw = false;
				_vInvenList[_selectedItem]._currentStack = 1;
				_selectedItem = -1;
			}

			if (_inEquipmentSlot)
			{
				_vEquipmentSlot[_selectedItem]._draw = false;
				_selectedItem = -1;
			}

		}

		

	}
	
	
}

void Inventory::invenMold()
{
	IMAGEMANAGER->render("invenBG", getMemDC(), _invenBG.left, _invenBG.top);
	IMAGEMANAGER->render("player_bg", getMemDC(), _playerBG.left, _playerBG.top);
	IMAGEMANAGER->render("player_bg_name_banner", getMemDC(), _playerName.left, _playerName.top);
	IMAGEMANAGER->render("bg_backpack_items", getMemDC(), _itemListBG.left, _itemListBG.top);

	IMAGEMANAGER->render("icon_hp", getMemDC(), _playerStat[0].left, _playerStat[0].top);
	IMAGEMANAGER->render("icon_mana #2486870", getMemDC(), _playerStat[1].left, _playerStat[1].top);
	IMAGEMANAGER->render("icon_defense #2480984", getMemDC(), _playerStat[2].left, _playerStat[2].top);
	IMAGEMANAGER->render("icon_attack_dmg+lv_combat", getMemDC(), _playerStat[3].left, _playerStat[3].top - 1);
	IMAGEMANAGER->render("icon_magic_damage", getMemDC(), _playerStat[4].left, _playerStat[4].top - 1);

	IMAGEMANAGER->render("trash_button", getMemDC(), _trashButton.left, _trashButton.top);
	IMAGEMANAGER->render("sort_button", getMemDC(), _sortButton.left, _sortButton.top);
	IMAGEMANAGER->render("drop_button", getMemDC(), _dropButton.left, _dropButton.top);
	IMAGEMANAGER->render("x_button", getMemDC(), _xButton.left, _xButton.top);

	FONTMANAGER->textOut(getMemDC(), _playerStat[0].left + 15, _playerStat[0].top, "배달의민족 을지로체", 12, 5, "체력", strlen("체력"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[1].left + 15, _playerStat[1].top, "배달의민족 을지로체", 12, 5, "마나", strlen("마나"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[2].left + 15, _playerStat[2].top, "배달의민족 을지로체", 12, 5, "방어력", strlen("방어력"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[3].left + 15, _playerStat[3].top - 1, "배달의민족 을지로체", 12, 5, "물리 공격력", strlen("물리 공격력"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[4].left + 15, _playerStat[4].top - 1, "배달의민족 을지로체", 12, 5, "마법 공격력", strlen("마법 공격력"), RGB(255, 255, 255));


	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[0]._rc.left + 8, _vEquipmentSlot[0]._rc.top - 15, "배달의민족 을지로체", 10, 50, "장비", strlen("장비"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[5]._rc.left + 8, _vEquipmentSlot[5]._rc.top - 15, "배달의민족 을지로체", 10, 50, "외형", strlen("외형"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[10]._rc.left + 5, _vEquipmentSlot[10]._rc.top - 15, "배달의민족 을지로체", 10, 50, "기념품", strlen("기념품"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[11]._rc.left + 5, _vEquipmentSlot[11]._rc.top - 15, "배달의민족 을지로체", 10, 50, "반지1", strlen("반지1"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[12]._rc.left + 5, _vEquipmentSlot[12]._rc.top - 8, "배달의민족 을지로체", 10, 50, "목걸이", strlen("목걸이"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[13]._rc.left + 5, _vEquipmentSlot[13]._rc.top - 8, "배달의민족 을지로체", 10, 50, "반지2", strlen("반지2"), RGB(255, 255, 255));

	FONTMANAGER->textOut(getMemDC(), (_invenBG.right + _invenBG.left) / 2, _invenBG.top + 15, "배달의민족 을지로체", 15, 50, "가방", strlen("가방"), RGB(241, 224, 109));

}

void Inventory::invenSlot()
{
	int _index;
	//인벤칸
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			if (_vInvenList[i * 8 + j]._draw)
			{
				
				switch (_vInvenList[i * 8 + j]._category[0])
				{
				case '0':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					if (DATAMANAGER->getToolInfo(_index)->grade == "커먼")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getToolInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					break;

				case '1':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					if (DATAMANAGER->getWeaponInfo(_index)->grade == "커먼")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getWeaponInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					break;
					//
				case '2':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					if (DATAMANAGER->getArmorInfo(_index)->grade == "커먼")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getArmorInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					break;

				case '3':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					if (DATAMANAGER->getAccessoryInfo(_index)->grade == "커먼")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getAccessoryInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					break;

				case '4':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					if (DATAMANAGER->getIngredientInfo(_index)->name[0] == '아')
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);		
					}
					else
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getIngredientInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					char showStack[2000];
					sprintf_s(showStack, "%d", (_vInvenList[i * 8 + j]._currentStack));
					FONTMANAGER->textOut(getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top, "배달의민족 을지로체", 15, 5, showStack, strlen(showStack), RGB(0, 0, 0));
					break;

				case '5':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					
					IMAGEMANAGER->render(DATAMANAGER->getConsumableInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					char showStack2[2000];
					sprintf_s(showStack2, "%d", (_vInvenList[i * 8 + j]._currentStack));
					FONTMANAGER->textOut(getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top, "배달의민족 을지로체", 15, 5, showStack2, strlen(showStack2), RGB(0, 0, 0));
					break;

				}
	
			}
			else
			{
				IMAGEMANAGER->render("item_bg", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
			}

			

		}
	}
}

void Inventory::equipment_Slot()
{
	int _index;
	//장비칸
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_vEquipmentSlot[i * 5 + j]._draw)
			{
				
				// 인덱스가 5 부터 헬멧 / 상의 / 하의/ 장갑 
				switch (_vEquipmentSlot[i * 5 + j]._category[0])
				{
				
				case '2':
					_index = (int)_vEquipmentSlot[i * 5 + j]._category[2] - 48;
					if (DATAMANAGER->getArmorInfo(_index)->grade == "커먼")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getArmorInfo(_index)->name.c_str(), getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					break;

				case '3':
					_index = (int)_vEquipmentSlot[i * 5 + j]._category[2] - 48;
					if (DATAMANAGER->getAccessoryInfo(_index)->grade == "커먼")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getAccessoryInfo(_index)->name.c_str(), getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					break;
				
				}
			}
			else
			{
				if (i < 2)
				{
					if (i == 0)
					{
						IMAGEMANAGER->render(("equipment_slot" + to_string(j + 1)).c_str(), getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}

					if (i == 1)
					{
						IMAGEMANAGER->render(("cosmetics_slot" + to_string(j + 1)).c_str(), getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}
				}
				else
				{
					if (j == 0)
					{
						IMAGEMANAGER->render("player_slot1_keepsake", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);
					}

					if (j == 1)
					{
						IMAGEMANAGER->render("player_slot2_ring1", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top);

					}

					if (j == 2)
					{
						IMAGEMANAGER->render("player_slot3_amulet", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top + 4);

					}

					if (j == 3)
					{
						IMAGEMANAGER->render("player_slot4_ring2", getMemDC(), _vEquipmentSlot[i * 5 + j]._rc.left, _vEquipmentSlot[i * 5 + j]._rc.top + 4);

					}

					if (j == 4)
					{
						break;
					}
				}
			}

			//itemInfoPopup(i * 5 + j);

		}
	}
}

void Inventory::moveItemRender()
{
	int _index;
	if (_selectedItem != -1)
	{
		if (_inInvenSlot)
		{
			
			switch (_vInvenList[_selectedItem]._category[0])
			{
			case '0':
				_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getToolInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getToolInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;

			case '1':
				_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getWeaponInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getWeaponInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;

			case '2':
				_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getArmorInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getArmorInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;

			case '3':
				_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getAccessoryInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getAccessoryInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;

			case '4':
				_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getIngredientInfo(_index)->name[0] == '아')
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getIngredientInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				char showStack3[2000];
				sprintf_s(showStack3, "%d", (_vInvenList[_selectedItem]._currentStack));
				FONTMANAGER->textOut(getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16, "배달의민족 을지로체", 15, 5, showStack3, strlen(showStack3), RGB(0, 0, 0));
				break;

			case '5':
				_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
				IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				IMAGEMANAGER->render(DATAMANAGER->getConsumableInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				char showStack4[2000];
				sprintf_s(showStack4, "%d", (_vInvenList[_selectedItem]._currentStack));
				FONTMANAGER->textOut(getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16, "배달의민족 을지로체", 15, 5, showStack4, strlen(showStack4), RGB(0, 0, 0));
				break;

			}
		}
		
		if (_inEquipmentSlot)
		{
			
			switch (_vEquipmentSlot[_selectedItem]._category[0])
			{
			case '0':
				_index = (int)_vEquipmentSlot[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getToolInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getToolInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;

			case '1':
				_index = (int)_vEquipmentSlot[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getWeaponInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getWeaponInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;
			
			case '2':
				_index = (int)_vEquipmentSlot[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getArmorInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getArmorInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				
				break;

			case '3':
				_index = (int)_vEquipmentSlot[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getAccessoryInfo(_index)->grade == "커먼")
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getAccessoryInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				break;

			case '4':
				_index = (int)_vEquipmentSlot[_selectedItem]._category[2] - 48;
				if (DATAMANAGER->getIngredientInfo(_index)->name[0] == '아')
				{
					IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				else
				{
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				}
				IMAGEMANAGER->render(DATAMANAGER->getIngredientInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				char showStack5[2000];
				sprintf_s(showStack5, "%d", (_vEquipmentSlot[_selectedItem]._currentStack));
				FONTMANAGER->textOut(getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16, "배달의민족 을지로체", 15, 5, showStack5, strlen(showStack5), RGB(0, 0, 0));

				break;

			case '5':
				_index = (int)_vEquipmentSlot[_selectedItem]._category[2] - 48;
				IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				IMAGEMANAGER->render(DATAMANAGER->getConsumableInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
				char showStack6[2000];
				sprintf_s(showStack5, "%d", (_vEquipmentSlot[_selectedItem]._currentStack));
				FONTMANAGER->textOut(getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16, "배달의민족 을지로체", 15, 5, showStack5, strlen(showStack5), RGB(0, 0, 0));
				break;
			}
		}

		
	}
}

void Inventory::popupItem()
{
	DWORD currentTime = GetTickCount64();
	if (currentTime - _lastItemTime < 3000) // 3초 동안만 출력
	{
		
	}
}

void Inventory::putItem()
{
	if (_seeInven)
	{

		// 빈칸에 해당하는 인덱스를 찾음
		int indexInven = -1;
		int indexEqui = -1;
		int shuffleStack = 0;
		//인벤칸
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, _ptMouse) && !_vInvenList[i]._draw)
			{
				indexInven = i;
				break;
			}

		}

		//장비칸
		for (int j = 0; j < _vEquipmentSlot.size() - 1; j++)
		{
			if (PtInRect(&_vEquipmentSlot[j]._rc, _ptMouse) && !_vEquipmentSlot[j]._draw)
			{
				indexEqui = j;
				break;
			}

		}

		// 인덱스가 유효하고 _selectedItem 값이 유효하면 아이템을 놓음
		
		if (indexInven != -1 && _selectedItem != -1)
		{
			if (_inInvenSlot)
			{
				_vInvenList[indexInven]._category = _vInvenList[_selectedItem]._category;
				_vInvenList[indexInven]._currentStack = _vInvenList[_selectedItem]._currentStack;
				_vInvenList[indexInven]._draw = true;
			}

			if (_inEquipmentSlot)
			{
				_vInvenList[indexInven]._category = _vEquipmentSlot[_selectedItem]._category;
				_vInvenList[indexInven]._currentStack = _vEquipmentSlot[_selectedItem]._currentStack;
				_vInvenList[indexInven]._draw = true;
			}
			
			
			_selectedItem = -1;
			

		}


		// 인덱스가 유효하고 _selectedItem 값이 유효하면 아이템을 놓음

		if (indexEqui != -1 && _selectedItem != -1)
		{
			
			if (_inInvenSlot && _vInvenList[_selectedItem]._category[0] == '2' || _inInvenSlot && _vInvenList[_selectedItem]._category[0] == '3')
			{
				_vEquipmentSlot[indexEqui]._category = _vInvenList[_selectedItem]._category;
				_vEquipmentSlot[indexEqui]._draw = true;
				
			}
			else if (_vInvenList[_selectedItem]._category[0] != '2' || _vInvenList[_selectedItem]._category[0] != '3')
			{
				if (_inInvenSlot)
				{
					_vInvenList[_selectedItem]._draw = true;
				}
				
			}

			if (_inEquipmentSlot)
			{
				_vEquipmentSlot[indexEqui]._category = _vEquipmentSlot[_selectedItem]._category;
				_vEquipmentSlot[indexEqui]._draw = true;
						
			}
			
			_selectedItem = -1;
			

		}

	}
}

void Inventory::invenXButton()
{
	if ((PtInRect(&_xButton, _ptMouse) || KEYMANAGER->isOnceKeyDown('I')))
	{
		_seeInven = false;
	}
}

void Inventory::setCurrentSlot(enum eTools player)
{
	IMAGEMANAGER->render("selection_hover-click-selected_0", getMemDC(), _vItemUseSlot[player]._rc.left, _vItemUseSlot[player]._rc.top);
}

void Inventory::itemInfoPopup(int index)
{
	if (PtInRect(&_vInvenList[index]._rc, _ptMouse) && _vInvenList[index]._draw)
	{
		if (index < 8)
		{
			
			IMAGEMANAGER->render("tooltip_bg_flipped", getMemDC(), _ptMouse.x, _ptMouse.y );
		}
		else
		{
			
			IMAGEMANAGER->render("tooltip_bg", getMemDC(), _ptMouse.x, _ptMouse.y - 87);
		}
	}

	if (index < 15)
	{
		if (PtInRect(&_vEquipmentSlot[index]._rc, _ptMouse) && _vEquipmentSlot[index]._draw)
		{
			if (index == 0)
			{
				IMAGEMANAGER->render("tooltip_bg_flipped", getMemDC(), _ptMouse.x, _ptMouse.y);

			}
			else
			{
				IMAGEMANAGER->render("tooltip_bg", getMemDC(), _ptMouse.x, _ptMouse.y - 87);
			}
		}
	}
	
}

void Inventory::sellItem()
{
	
	if (PtInRect(&_dropButton, _ptMouse) && _selectedItem != -1)
	{
		if (_inInvenSlot)
		{
			_vInvenList[_selectedItem]._draw = false;
			_vInvenList[_selectedItem]._currentStack = 1;
			switch (_vInvenList[_selectedItem]._category[0])
			{
			case '0':
				_sellGold += DATAMANAGER->getToolInfo((int)_vInvenList[_selectedItem]._category[2] - 48)->sellGold;

				break;

			case '1':
				_sellGold += DATAMANAGER->getWeaponInfo((int)_vInvenList[_selectedItem]._category[2] - 48)->sellGold;

				break;

			case '2':
				_sellGold += DATAMANAGER->getArmorInfo((int)_vInvenList[_selectedItem]._category[2] - 48)->sellGold;

				break;

			case '3':
				_sellGold += DATAMANAGER->getAccessoryInfo((int)_vInvenList[_selectedItem]._category[2] - 48)->sellGold;

				break;

			case '4':
				_sellGold += DATAMANAGER->getIngredientInfo((int)_vInvenList[_selectedItem]._category[2] - 48)->sellGold;

				break;

			case '5':
				_sellGold += DATAMANAGER->getConsumableInfo((int)_vInvenList[_selectedItem]._category[2] - 48)->sellGold;

				break;
			}
			_selectedItem = -1;
		}

		if (_inEquipmentSlot)
		{
			_vEquipmentSlot[_selectedItem]._draw = false;
			_selectedItem = -1;
		}
	}
	else
	{
		_sellGold = 0;
	}
}




