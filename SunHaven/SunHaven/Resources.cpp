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

	IMAGEMANAGER->addGPFrameImage("TITLE_BUTTON", "Resources/Images/Title/Title_Button.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// 메뉴 위에 마우스 포인터 위치 시

	// 커서
	IMAGEMANAGER->addImage("CURSOR", "Resources/Images/Title/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));

	return S_OK;
}

void Resources::release(void)
{
}
