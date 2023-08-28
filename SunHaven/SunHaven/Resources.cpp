#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// Ÿ��Ʋ
	IMAGEMANAGER->addImage("TITLE", "Resources/Images/Title/Title.bmp",
		1280, 720);	// ���

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// �޴�

	IMAGEMANAGER->addGPFrameImage("TITLE_BUTTON", "Resources/Images/Title/Title_Button.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// �޴� ���� ���콺 ������ ��ġ ��

	// Ŀ��
	IMAGEMANAGER->addImage("CURSOR", "Resources/Images/Title/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));

	return S_OK;
}

void Resources::release(void)
{
}
