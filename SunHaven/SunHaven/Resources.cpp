#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// ====================TitleScene====================
	// Image
	IMAGEMANAGER->addGPFrameImage("TitleLogo", "Resources/Images/UI/TitleLogo.png",
		0, 0,
		1, 1,
		false, NULL, NULL, RotateNoneFlipNone);   // 타이틀 로고
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGround/TitleBG.bmp",
		873 * 2, 360 * 2);	// 배경
	IMAGEMANAGER->addImage("TitleMenu", "Resources/Images/UI/TitleMenu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// 메뉴
	IMAGEMANAGER->addGPFrameImage("TitleButton", "Resources/Images/UI/TitleButton.png",
		0, 0,
		1, 1,
		false, NULL, NULL, RotateNoneFlipNone);	// 메뉴 위에 마우스 포인터 위치 시
	IMAGEMANAGER->addImage("Cursor", "Resources/Images/UI/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));	// 커서
	IMAGEMANAGER->addGPFrameImage("FrameDropTest", "Resources/Images/FrameDropTest.png",
		0, 0,
		35, 1,
		true, RGB(0, 0, 0), RGB(128, 128, 128), RotateNoneFlipNone);   // 타이틀 로고
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
	// Image

	// Sound

	return S_OK;
}

void Resources::release(void)
{
}
