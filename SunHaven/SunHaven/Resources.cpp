#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// Ÿ��Ʋ
	IMAGEMANAGER->addImage("TITLE", "Resources/Images/Title/Title.bmp",
		1280, 720);	// ���

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 2, 40 * 1,
		true, RGB(255, 0, 255));	// �޴�

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 1, 40 * 1,
		true, RGB(255, 0, 255));	// �޴� Ŭ��



	return S_OK;
}

void Resources::release(void)
{
}
