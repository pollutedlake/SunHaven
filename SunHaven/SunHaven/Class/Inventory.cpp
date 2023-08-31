#include "Stdafx.h"
#include "Inventory.h"







HRESULT Inventory::init(void)
{
	_invenBG = RectMake(WINSIZE_X / 4, WINSIZE_Y / 4, WINSIZE_X / 2, WINSIZE_Y / 2);
	_playerBG = RectMake(_invenBG.left + 30, _invenBG.top + 50, WINSIZE_X / 6, WINSIZE_Y / 2 - 80);
	_playerName = RectMake(_playerBG.left, _playerBG.top - 20, 202, 20);
	_itemListBG = RectMake(_playerBG.right + 30, _playerBG.top, WINSIZE_X / 4, WINSIZE_Y / 2 - 80);


	return S_OK;
}

void Inventory::release(void)
{

}

void Inventory::update(void)
{
	
}

void Inventory::render(void)
{
	if (KEYMANAGER->isToggleKey('I'))
	{
		IMAGEMANAGER->render("invenBG", getMemDC(), _invenBG.left, _invenBG.top);
		IMAGEMANAGER->render("player_bg", getMemDC(), _playerBG.left, _playerBG.top);
		IMAGEMANAGER->render("player_bg_name_banner", getMemDC(), _playerName.left, _playerName.top);
		IMAGEMANAGER->render("bg_backpack_items", getMemDC(), _itemListBG.left, _itemListBG.top);
		
	}
	
}
