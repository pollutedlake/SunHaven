#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// 타이틀
	IMAGEMANAGER->addImage("TITLE", "Resources/Images/Title/Title.bmp",
		1280, 720);	// 배경

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// 메뉴

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 1, 40 * 1,
		true, RGB(255, 0, 255));	// 메뉴 클릭
	IMAGEMANAGER->addImage("Cursor", "Resources/Images/UI/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("Tile1", "Resources/Images/Tile/Tile1.bmp",
		24, 24,
		true, RGB(255, 0, 255));


	return S_OK;
}

void Resources::release(void)
{
}
