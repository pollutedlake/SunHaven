#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// ====================TitleScene====================
	// Image
	IMAGEMANAGER->addGPFrameImage("TitleLogo", "Resources/Images/UI/TitleLogo.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);   // 타이틀 로고
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGround/TitleBG.bmp",
		873 * 2, 360 * 2);	// 배경
	IMAGEMANAGER->addImage("TitleMenu", "Resources/Images/UI/TitleMenu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// 메뉴
	IMAGEMANAGER->addGPFrameImage("TitleButton", "Resources/Images/UI/TitleButton.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// 메뉴 위에 마우스 포인터 위치 시
	IMAGEMANAGER->addImage("Cursor", "Resources/Images/UI/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));	// 커서
	// Sound

	// ====================MapToolScene====================
	// Image
	IMAGEMANAGER->addImage("Tile1", "Resources/Images/Tile/Tile1.bmp",
		24, 24,
		true, RGB(255, 0, 255));
	// Sound

	// ====================DynusScene====================
	// Image

	// Sound

	// ====================FarmScene====================
	// Image

	// Sound

	// ====================ShopScene====================
	// invenImage
	IMAGEMANAGER->addImage("invenBG", "Resources/Images/Inventory/invenBG.png", 405, 290);
	IMAGEMANAGER->addImage("player_bg", "Resources/Images/Inventory/player_bg.png", 184, 224);
	/*IMAGEMANAGER->addImage("bg_backpack_items", "Resources/Images/Inventory/bg_backpack_items.png", 379, 226);
	IMAGEMANAGER->addImage("player_bg_name_banner", "Resources/Images/Inventory/player_bg_name_banner.bmp", 405, 290,true,RGB(255,0,255));*/
	// shopImage

	// Sound

	return S_OK;
}

void Resources::release(void)
{
}
