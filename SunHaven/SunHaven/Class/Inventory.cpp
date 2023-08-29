#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_invenBG = RectMake(WINSIZE_X / 4, WINSIZE_Y / 4, WINSIZE_X / 2, WINSIZE_Y / 2);
	_playerBG = RectMake(_invenBG.left + 30, _invenBG.top + 50, WINSIZE_X / 6, WINSIZE_Y / 2 - 80);
	_playerName = RectMake(_invenBG.left,_playerBG.)
	// _itemListBG;


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
	
	IMAGEMANAGER->render("invenBG", getMemDC(), _invenBG.left, _invenBG.top);
	IMAGEMANAGER->render("player_bg", getMemDC(), _playerBG.left, _playerBG.top);
}
