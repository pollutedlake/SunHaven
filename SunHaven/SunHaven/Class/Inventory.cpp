#include "Stdafx.h"
#include "Inventory.h"
#include <string>


HRESULT Inventory::init(void)
{
	_ID = new ItemData;
	_ID->init();


	_invenBG = RectMake(WINSIZE_X / 4, WINSIZE_Y / 4, WINSIZE_X / 2, WINSIZE_Y / 2);
	_playerBG = RectMake(_invenBG.left + 30, _invenBG.top + 50, WINSIZE_X / 6, WINSIZE_Y / 2 - 80);
	_playerName = RectMake(_playerBG.left, _playerBG.top - 20, 202, 20);
	_itemListBG = RectMake(_playerBG.right + 30, _playerBG.top, WINSIZE_X / 4 + 20, WINSIZE_Y / 2 - 80);
	_sortButton = RectMake(_itemListBG.left + 10, _itemListBG.bottom - 40, 26, 25);
	_dropButton = RectMake(_itemListBG.right - 75, _itemListBG.bottom - 40, 26, 25);
	_trashButton = RectMake(_itemListBG.right - 35, _itemListBG.bottom - 40, 26, 25);
	_xButton = RectMake(_invenBG.right - 27, _invenBG.top - 5, 27, 28);
	//_sortButton _trashButton _dropButton
	for (int i = 0; i < 5; i++)
	{
		_playerStat[i] = RectMake(_playerBG.left + 5, (_playerBG.top + 82) + 17 * i, 10, 10);
	}

	inventoryList  temp;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ZeroMemory(&temp, sizeof(inventoryList));

			temp._rc = RectMake(_itemListBG.left + j * 42 + 7, _itemListBG.top + 10 + i * 42, 32, 32);
			temp._draw = false;
			temp._category = 0;
		
			_vInvenList.push_back(temp);

		}
	}

	equipmentSlot temp2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ZeroMemory(&temp2, sizeof(equipmentSlot));

			if (i < 2)
			{
				temp2._rc = RectMake(_playerBG.right - 97 + i * 55, _playerBG.top + 40 + j * 50, 32, 32);
				temp2._draw = false;
				temp2._category = 0;

				_vEquipmentSlot.push_back(temp2);
			}
			else
			{
				if (j == 0)
				{
					temp2._rc = RectMake(_playerBG.left + 13, _playerBG.bottom - 95, 32, 32);
					temp2._draw = false;
					temp2._category = 0;

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 1)
				{
					temp2._rc = RectMake(_playerBG.left + 60, _playerBG.bottom - 95, 32, 32);
					temp2._draw = false;
					temp2._category = 0;

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 2)
				{
					temp2._rc = RectMake(_playerBG.left + 13, _playerBG.bottom - 50, 32, 32);
					temp2._draw = false;
					temp2._category = 0;

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 3)
				{
					temp2._rc = RectMake(_playerBG.left + 60, _playerBG.bottom - 50, 32, 32);
					temp2._draw = false;
					temp2._category = 0;

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 4)
				{
					temp2._rc = {};

					_vEquipmentSlot.push_back(temp2);
				}
			}


		}
	}

	_getItem = 0;
	_selectedItem = -1;

	//tagTool* temp3;

	for (int i = 0; i < 9; i++)
	{
		_vTool.push_back(_ID->getTool()->front());
		_ID->getTool()->pop();
	}

	


	return S_OK;
}

void Inventory::release(void)
{
	SAFE_DELETE(_ID);
}

void Inventory::update(void)
{
	
	getItem();

	itemMove();
	
	
}

void Inventory::render(void)
{
	if (KEYMANAGER->isToggleKey('I'))
	{

		invenMold();
		
		invenSlot();

		equipment_Slot();

		moveItemRender();

	}


	if (PtInRect(&_xButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		
	}
	
	popupItem();
	
}

void Inventory::getItem()
{
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_getItem = RND->getFromIntTo(0, 8);

		for (int i = 0; i < _vInvenList.size(); i++)
		{

			if (!_vInvenList[i]._draw)
			{
				_vInvenList[i]._category = _getItem;

				_vInvenList[i]._draw = true;

				_lastItemTime = GetTickCount64();

				return;
			}

		}

	}
}

void Inventory::itemMove()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// 마우스 좌표를 얻음
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_hWnd, &pt);

		// 해당하는 인덱스를 찾음
		int index = -1;
		int temp = 0;
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, pt))
			{
				index = i;
				break;
			}
		}

		// 인덱스가 유효하고 아이템이 있으면 _selectedItem에 저장
		if (index != -1 && _vInvenList[index]._draw)
		{
			if (_selectedItem != -1)
			{

				temp = _vInvenList[index]._category;
				_vInvenList[index]._category = _vInvenList[_selectedItem]._category;
				_vInvenList[_selectedItem]._category = temp;

			}
			else
			{
				_selectedItem = index;
				_vInvenList[index]._draw = false;
			}


		}

		//완전삭제로 수정예정
		if (PtInRect(&_trashButton, pt)&& _selectedItem != -1)
		{
			_vInvenList[_selectedItem]._draw = false;
			_selectedItem = -1;
		}


		//바닥에버리기로 수정예정
		if (PtInRect(&_dropButton, pt) && _selectedItem != -1)
		{
			_vInvenList[_selectedItem]._draw = false;
			_selectedItem = -1;
		}

	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		// 마우스 좌표를 얻음
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_hWnd, &pt);

		// 빈칸에 해당하는 인덱스를 찾음
		int index = -1;
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, pt) && !_vInvenList[i]._draw)
			{
				index = i;
				break;
			}

		}

		// 인덱스가 유효하고 _selectedItem 값이 유효하면 아이템을 놓음

		if (index != -1 && _selectedItem != -1)
		{
			_vInvenList[index]._category = _vInvenList[_selectedItem]._category;
			_vInvenList[index]._draw = true;
			//_vInvenList[_selectedItem]._draw = false;
			_selectedItem = -1;

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
	//인벤칸
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			if (_vInvenList[i * 8 + j]._draw)
			{
				switch (_vInvenList[i * 8 + j]._category)
				{
				case 0:

					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
					break;
				case 1:
					
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
					break;
				case 2:
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 3:
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 4:
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 5:

					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
					break;
				case 6:
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 7:
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 8:
					IMAGEMANAGER->render(_vTool.at(_vInvenList[i * 8 + j]._category)->name.c_str(), getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

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
	//장비칸
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_vEquipmentSlot[i * 5 + j]._draw)
			{
				switch (_vEquipmentSlot[i * 5 + j]._category)
				{
				case 1:
					//IMAGEMANAGER->render("ironBoots", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
					//_vTool[i * 8 + j]->filePath;
					break;
				case 2:
					IMAGEMANAGER->render("ironChestPlate", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 3:
					IMAGEMANAGER->render("ironGloves", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

					break;
				case 4:
					IMAGEMANAGER->render("ironSword", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);

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
		}
	}
}

void Inventory::moveItemRender()
{
	if (_selectedItem != -1)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_hWnd, &pt);

		switch (_vInvenList[_selectedItem]._category)
		{
		case 0:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 1:
			
			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 2:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 3:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 4:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 5:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 6:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 7:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		case 8:

			IMAGEMANAGER->render(_vTool.at(_vInvenList[_selectedItem]._category)->name.c_str(), getMemDC(), pt.x - 16, pt.y - 16);
			break;
		}
	}
}

void Inventory::popupItem()
{
	DWORD currentTime = GetTickCount64();
	if (currentTime - _lastItemTime < 3000) // 3초 동안만 출력
	{
		switch (_getItem)
		{
		case 1:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "한컴 말랑말랑 Bold", 35, 600, "철 부츠를 얻었습니다.", strlen("철 부츠를 얻었습니다."), RGB(0, 0, 0));
			break;
		case 2:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "한컴 말랑말랑 Bold", 35, 600, "철 갑옷을 얻었습니다.", strlen("철 갑옷을 얻었습니다."), RGB(0, 0, 0));
			break;
		case 3:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "한컴 말랑말랑 Bold", 35, 600, "철 장갑을 얻었습니다.", strlen("철 장갑을 얻었습니다."), RGB(0, 0, 0));
			break;
		case 4:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "한컴 말랑말랑 Bold", 35, 600, "철 검을 얻었습니다.", strlen("철 검을 얻었습니다."), RGB(0, 0, 0));
			break;
		}
	}
}
