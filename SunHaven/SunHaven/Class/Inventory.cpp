#include "Stdafx.h"
#include "Inventory.h"
#include <string>


HRESULT Inventory::init(void)
{
	/*_ID = new ItemData;
	_ID->init();*/

	_seeInven = false;
	
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

	inventoryList  temp;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ZeroMemory(&temp, sizeof(inventoryList));

			temp._rc = RectMake(_itemListBG.left + j * 42 + 7, _itemListBG.top + 10 + i * 42, 32, 32);
			temp._draw = false;
			temp._category = "";
		
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
				temp2._category = "";

				_vEquipmentSlot.push_back(temp2);
			}
			else
			{
				if (j == 0)
				{
					temp2._rc = RectMake(_playerBG.left + 13, _playerBG.bottom - 95, 32, 32);
					temp2._draw = false;
					temp2._category = "";

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 1)
				{
					temp2._rc = RectMake(_playerBG.left + 60, _playerBG.bottom - 95, 32, 32);
					temp2._draw = false;
					temp2._category = "";

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 2)
				{
					temp2._rc = RectMake(_playerBG.left + 13, _playerBG.bottom - 50, 32, 32);
					temp2._draw = false;
					temp2._category = "";

					_vEquipmentSlot.push_back(temp2);
				}

				if (j == 3)
				{
					temp2._rc = RectMake(_playerBG.left + 60, _playerBG.bottom - 50, 32, 32);
					temp2._draw = false;
					temp2._category = "";

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

	
	_selectedItem = -1;


	return S_OK;
}

void Inventory::release(void)
{
	
}

void Inventory::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		getItem("2-0");
	}
	
	
	itemMove();

	if (KEYMANAGER->isOnceKeyDown('I') && !_seeInven)
	{
		_seeInven = true;

	}
	
}

void Inventory::render(void)
{
	
	if (_seeInven)
	{
		invenMold();

		invenSlot();

		equipment_Slot();

		moveItemRender();

		if ((PtInRect(&_xButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) || KEYMANAGER->isOnceKeyDown('I'))
		{
			_seeInven = false;
		}

	}
	
	popupItem();
	
}

void Inventory::getItem(string index)
{
	for (int i = 0; i < _vInvenList.size(); i++)
	{

		if (!_vInvenList[i]._draw)
		{
			_vInvenList[i]._category = index;

			_vInvenList[i]._draw = true;

			_lastItemTime = GetTickCount64();

			return;
		}

	}
}

void Inventory::itemMove()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//�κ�ĭ
		// �ش��ϴ� �ε����� ã��
		int indexInven = -1;
		int indexEqui = -1;
		string temp = "";
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, _ptMouse))
			{
				indexInven = i;
				break;
			}
		}

		//���ĭ
		for (int j = 0; j < _vEquipmentSlot.size() - 1; j++)
		{
			if (PtInRect(&_vEquipmentSlot[j]._rc, _ptMouse))
			{
				indexEqui = j;
				break;
			}
		}


		// �ε����� ��ȿ�ϰ� �������� ������ _selectedItem�� ����
		if (indexInven != -1 && _vInvenList[indexInven]._draw)
		{
			if (_selectedItem != -1)
			{

				temp = _vInvenList[indexInven]._category;
				_vInvenList[indexInven]._category = _vInvenList[_selectedItem]._category;
				_vInvenList[_selectedItem]._category = temp;

			}
			else
			{
				_selectedItem = indexInven;
				_vInvenList[indexInven]._draw = false;
			}

		}

		
		if (indexEqui != -1 && _vEquipmentSlot[indexEqui]._draw)
		{
			if (_selectedItem != -1)
			{

				temp = _vEquipmentSlot[indexEqui]._category;
				_vEquipmentSlot[indexEqui]._category = _vEquipmentSlot[_selectedItem]._category;
				_vEquipmentSlot[_selectedItem]._category = temp;

			}
			else
			{
				_selectedItem = indexEqui;
				_vEquipmentSlot[indexEqui]._draw = false;
			}

		}


		//���������� ��������
		if (PtInRect(&_trashButton, _ptMouse)&& _selectedItem != -1)
		{
			_vInvenList[_selectedItem]._draw = false;
			_selectedItem = -1;
		}

		//�Ǹŷ� ��������
		if (PtInRect(&_dropButton, _ptMouse) && _selectedItem != -1)
		{
			_vInvenList[_selectedItem]._draw = false;
			_selectedItem = -1;
		}

	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		
		// ��ĭ�� �ش��ϴ� �ε����� ã��
		int indexInven = -1;
		int indexEqui = -1;
		//�κ�ĭ
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, _ptMouse) && !_vInvenList[i]._draw)
			{
				indexInven = i;
				break;
			}

		}

		// �ε����� ��ȿ�ϰ� _selectedItem ���� ��ȿ�ϸ� �������� ����

		if (indexInven != -1 && _selectedItem != -1)
		{
			_vInvenList[indexInven]._category = _vInvenList[_selectedItem]._category;
			_vInvenList[indexInven]._draw = true;

			_selectedItem = -1;

		}

		//���ĭ
		for (int i = 0; i < _vEquipmentSlot.size() - 1; i++)
		{
			if (PtInRect(&_vEquipmentSlot[i]._rc, _ptMouse) && !_vEquipmentSlot[i]._draw)
			{
				indexEqui = i;
				break;
			}

		}

		// �ε����� ��ȿ�ϰ� _selectedItem ���� ��ȿ�ϸ� �������� ����

		if (indexEqui != -1 && _selectedItem != -1)
		{
			_vEquipmentSlot[indexEqui]._category = _vEquipmentSlot[_selectedItem]._category;
			_vEquipmentSlot[indexEqui]._draw = true;

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

	FONTMANAGER->textOut(getMemDC(), _playerStat[0].left + 15, _playerStat[0].top, "����ǹ��� ������ü", 12, 5, "ü��", strlen("ü��"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[1].left + 15, _playerStat[1].top, "����ǹ��� ������ü", 12, 5, "����", strlen("����"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[2].left + 15, _playerStat[2].top, "����ǹ��� ������ü", 12, 5, "����", strlen("����"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[3].left + 15, _playerStat[3].top - 1, "����ǹ��� ������ü", 12, 5, "���� ���ݷ�", strlen("���� ���ݷ�"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _playerStat[4].left + 15, _playerStat[4].top - 1, "����ǹ��� ������ü", 12, 5, "���� ���ݷ�", strlen("���� ���ݷ�"), RGB(255, 255, 255));


	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[0]._rc.left + 8, _vEquipmentSlot[0]._rc.top - 15, "����ǹ��� ������ü", 10, 50, "���", strlen("���"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[5]._rc.left + 8, _vEquipmentSlot[5]._rc.top - 15, "����ǹ��� ������ü", 10, 50, "����", strlen("����"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[10]._rc.left + 5, _vEquipmentSlot[10]._rc.top - 15, "����ǹ��� ������ü", 10, 50, "���ǰ", strlen("���ǰ"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[11]._rc.left + 5, _vEquipmentSlot[11]._rc.top - 15, "����ǹ��� ������ü", 10, 50, "����1", strlen("����1"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[12]._rc.left + 5, _vEquipmentSlot[12]._rc.top - 8, "����ǹ��� ������ü", 10, 50, "�����", strlen("�����"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), _vEquipmentSlot[13]._rc.left + 5, _vEquipmentSlot[13]._rc.top - 8, "����ǹ��� ������ü", 10, 50, "����2", strlen("����2"), RGB(255, 255, 255));

	FONTMANAGER->textOut(getMemDC(), (_invenBG.right + _invenBG.left) / 2, _invenBG.top + 15, "����ǹ��� ������ü", 15, 50, "����", strlen("����"), RGB(241, 224, 109));

}

void Inventory::invenSlot()
{
	int _index;
	//�κ�ĭ
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
					if (DATAMANAGER->getToolInfo(_index)->grade == "Ŀ��")
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
					if (DATAMANAGER->getWeaponInfo(_index)->grade == "Ŀ��")
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					else
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getWeaponInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					break;

				case '2':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					if (DATAMANAGER->getArmorInfo(_index)->grade == "Ŀ��")
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
					if (DATAMANAGER->getAccessoryInfo(_index)->grade == "Ŀ��")
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
					if (DATAMANAGER->getIngredientInfo(_index)->name[0] == '��')
					{
						IMAGEMANAGER->render("item_bg_rare", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);		
					}
					else
					{
						IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					}
					IMAGEMANAGER->render(DATAMANAGER->getIngredientInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					break;

				case '5':
					_index = (int)_vInvenList[i * 8 + j]._category[2] - 48;
					
					IMAGEMANAGER->render("item_bg_common", getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
					
					IMAGEMANAGER->render(DATAMANAGER->getConsumableInfo(_index)->name.c_str(), getMemDC(), _vInvenList[i * 8 + j]._rc.left, _vInvenList[i * 8 + j]._rc.top);
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
	//���ĭ
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_vEquipmentSlot[i * 5 + j]._draw)
			{
				// �ε����� 5 ���� ��� / ���� / ����/ �尩 
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
	int _index;
	if (_selectedItem != -1)
	{
		switch (_vInvenList[_selectedItem]._category[0])
		{
		case '0':
			_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
			if (DATAMANAGER->getToolInfo(_index)->grade == "Ŀ��")
			{
				IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			}
			else
			{
				IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			}
			IMAGEMANAGER->render(DATAMANAGER->getToolInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y -16);
			break;

		case '1':
			_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
			if (DATAMANAGER->getWeaponInfo(_index)->grade == "Ŀ��")
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
			if (DATAMANAGER->getArmorInfo(_index)->grade == "Ŀ��")
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
			if (DATAMANAGER->getAccessoryInfo(_index)->grade == "Ŀ��")
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
			if (DATAMANAGER->getIngredientInfo(_index)->name[0] == '��')
			{
				IMAGEMANAGER->render("item_bg_rare", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			}
			else
			{
				IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			}
			IMAGEMANAGER->render(DATAMANAGER->getIngredientInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			break;

		case '5':
			_index = (int)_vInvenList[_selectedItem]._category[2] - 48;
			IMAGEMANAGER->render("item_bg_common", getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			IMAGEMANAGER->render(DATAMANAGER->getConsumableInfo(_index)->name.c_str(), getMemDC(), _ptMouse.x - 16, _ptMouse.y - 16);
			break;

		}
		
	}
}

void Inventory::popupItem()
{
	DWORD currentTime = GetTickCount64();
	if (currentTime - _lastItemTime < 3000) // 3�� ���ȸ� ���
	{
		/*switch (_getItem)
		{
		case 1:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "���� �������� Bold", 35, 600, "ö ������ ������ϴ�.", strlen("ö ������ ������ϴ�."), RGB(0, 0, 0));
			break;
		case 2:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "���� �������� Bold", 35, 600, "ö ������ ������ϴ�.", strlen("ö ������ ������ϴ�."), RGB(0, 0, 0));
			break;
		case 3:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "���� �������� Bold", 35, 600, "ö �尩�� ������ϴ�.", strlen("ö �尩�� ������ϴ�."), RGB(0, 0, 0));
			break;
		case 4:
			FONTMANAGER->textOut(getMemDC(), 10, WINSIZE_Y - 35, "���� �������� Bold", 35, 600, "ö ���� ������ϴ�.", strlen("ö ���� ������ϴ�."), RGB(0, 0, 0));
			break;
		}*/
	}
}


