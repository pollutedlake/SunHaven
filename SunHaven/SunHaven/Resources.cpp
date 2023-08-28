#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// 타이틀
	IMAGEMANAGER->addImage("TITLE", "Resources/Images/Title/Title.bmp",
		873 * 2, 360 * 2);	// 배경

	IMAGEMANAGER->addGPFrameImage("TITLE_LOGO", "Resources/Images/Title/TitleLogo.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// 타이틀 로고

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// 메뉴

//<<<<<<< HEAD
	IMAGEMANAGER->addGPFrameImage("TITLE_BUTTON", "Resources/Images/Title/Title_Button.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// 메뉴 위에 마우스 포인터 위치 시

//=======
	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 1, 40 * 1,
		true, RGB(255, 0, 255));	// 메뉴 클릭
	IMAGEMANAGER->addImage("Cursor", "Resources/Images/UI/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("Tile1", "Resources/Images/Tile/Tile1.bmp",
		24, 24,
		true, RGB(255, 0, 255));

//>>>>>>> PSH

	return S_OK;
}

void Resources::release(void)
{
}
