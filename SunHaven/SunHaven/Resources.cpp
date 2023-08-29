#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
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
