#include "Stdafx.h"
#include "Inventory.h"


HRESULT Inventory::init(void)
{
	_invenBG = RectMake(WINSIZE_X / 4, WINSIZE_Y / 4, WINSIZE_X / 2, WINSIZE_Y / 2);
	_playerBG = RectMake(_invenBG.left + 30, _invenBG.top + 50, WINSIZE_X / 6, WINSIZE_Y / 2 - 80);
	_playerName = RectMake(_playerBG.left, _playerBG.top - 20, 202, 20);
	_itemListBG = RectMake(_playerBG.right + 30, _playerBG.top, WINSIZE_X / 4 + 20, WINSIZE_Y / 2 - 80);

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

	_getItem = 0;
	_selectedItem = -1;
	return S_OK;
}

void Inventory::release(void)
{

}

void Inventory::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_getItem = RND->getFromIntTo(1, 4);

		for (int i = 0; i < _vInvenList.size(); i++)
		{
			
			if (!_vInvenList[i]._draw)
			{
				_vInvenList[i]._category = _getItem;

				_vInvenList[i]._draw = true;
				
				_lastItemTime = GetTickCount();
				
				return;
			}



		}
		
	}

	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// ���콺 ��ǥ�� ����
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_hWnd, &pt);

		// �ش��ϴ� �ε����� ã��
		int index = -1;
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, pt))
			{
				index = i;
				break;
			}
		}

		// �ε����� ��ȿ�ϰ� �������� ������ _selectedItem�� ����
		if (index != -1 && _vInvenList[index]._draw)
		{
			_selectedItem = index;
		}
		else
		{
			_selectedItem = -1;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		// ���콺 ��ǥ�� ����
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_hWnd, &pt);

		// ��ĭ�� �ش��ϴ� �ε����� ã��
		int index = -1;
		for (int i = 0; i < _vInvenList.size(); i++)
		{
			if (PtInRect(&_vInvenList[i]._rc, pt) && !_vInvenList[i]._draw)
			{
				index = i;
				break;
			}
		}

		// �ε����� ��ȿ�ϰ� _selectedItem ���� ��ȿ�ϸ� �������� ����
		if (index != -1 && _selectedItem != -1)
		{
			_vInvenList[index]._category = _vInvenList[_selectedItem]._category;
			_vInvenList[index]._draw = true;
			_vInvenList[_selectedItem]._draw = false;
			_selectedItem = -1;
		}
	}
}

void Inventory::render(void)
{
	if (KEYMANAGER->isToggleKey('I'))
	{
		IMAGEMANAGER->render("invenBG", getMemDC(), _invenBG.left, _invenBG.top);
		IMAGEMANAGER->render("player_bg", getMemDC(), _playerBG.left, _playerBG.top);
		IMAGEMANAGER->render("player_bg_name_banner", getMemDC(), _playerName.left, _playerName.top);
		IMAGEMANAGER->render("bg_backpack_items", getMemDC(), _itemListBG.left, _itemListBG.top);
		
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				
				if (_vInvenList[i * 8 + j]._draw)
				{
					switch (_vInvenList[i * 8 + j]._category)
					{
					case 1:
						IMAGEMANAGER->render("ironBoots", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
						
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
					IMAGEMANAGER->render("item_bg", getMemDC(), _vInvenList[i * (8) + j]._rc.left, _vInvenList[i * (8) + j]._rc.top);
				}
			
			}
		}

		if (_selectedItem != -1)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(_hWnd, &pt);

			switch (_vInvenList[_selectedItem]._category)
			{
			case 1:
				// �̹����� �߽����� �������� ����ϵ��� �����Ͽ��ٸ�, ���콺 ��ǥ���� �̹����� ���� ũ�⸸ŭ ����
				IMAGEMANAGER->render("ironBoots", getMemDC(), pt.x - 16, pt.y - 16);
				break;
			case 2:
				IMAGEMANAGER->render("ironChestPlate", getMemDC(), pt.x - 16, pt.y - 16);
				break;
			case 3:
				IMAGEMANAGER->render("ironGloves", getMemDC(), pt.x - 16, pt.y - 16);
				break;
			case 4:
				IMAGEMANAGER->render("ironSword", getMemDC(), pt.x - 16, pt.y - 16);
				break;
			}
		}


	}
	
	DWORD currentTime = GetTickCount();
	if (currentTime - _lastItemTime < 3000) // 3�� ���ȸ� ���
	{
		switch (_getItem)
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
		}
	}
	
}
