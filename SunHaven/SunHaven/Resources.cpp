#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
<<<<<<< HEAD
	// Ÿ��Ʋ
	IMAGEMANAGER->addImage("TITLE", "Resources/Images/Title/Title.bmp",
		873 * 2, 360 * 2);	// ���

	IMAGEMANAGER->addGPFrameImage("TITLE_LOGO", "Resources/Images/Title/TitleLogo.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// Ÿ��Ʋ �ΰ�

	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// �޴�

//<<<<<<< HEAD
	IMAGEMANAGER->addGPFrameImage("TITLE_BUTTON", "Resources/Images/Title/Title_Button.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// �޴� ���� ���콺 ������ ��ġ ��

//=======
	IMAGEMANAGER->addImage("TITLE_MENU", "Resources/Images/Title/Title_Menu.bmp",
		145 * 1, 40 * 1,
		true, RGB(255, 0, 255));	// �޴� Ŭ��
=======
	// ====================TitleScene====================
	// Image
	IMAGEMANAGER->addGPFrameImage("TitleLogo", "Resources/Images/UI/TitleLogo.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);   // Ÿ��Ʋ �ΰ�
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGround/TitleBG.bmp",
		873 * 2, 360 * 2);	// ���
	IMAGEMANAGER->addImage("TitleMenu", "Resources/Images/UI/TitleMenu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// �޴�
	IMAGEMANAGER->addGPFrameImage("TitleButton", "Resources/Images/UI/TitleButton.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);	// �޴� ���� ���콺 ������ ��ġ ��
>>>>>>> main
	IMAGEMANAGER->addImage("Cursor", "Resources/Images/UI/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));	// Ŀ��
	// Sound

	// ====================MapToolScene====================
	// Image
	IMAGEMANAGER->addImage("Tile1", "Resources/Images/Tile/Tile1.bmp",
		24, 24,
		true, RGB(255, 0, 255));
	// Sound

<<<<<<< HEAD
//>>>>>>> PSH
=======
	// ====================DynusScene====================
	// Image

	// Sound

	// ====================FarmScene====================
	// Image

	// Sound

	// ====================ShopScene====================
	// Image

	// Sound
>>>>>>> main

	return S_OK;
}

void Resources::release(void)
{
}
