#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	// ====================TitleScene====================
	// Image
	IMAGEMANAGER->addGPFrameImage("TitleLogo", "Resources/Images/UI/TitleLogoTest.png",
		0, 0,
		1, 1,
		false, NULL, NULL, RotateNoneFlipNone);   // Ÿ��Ʋ �ΰ�
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGround/TitleBG.bmp",
		873 * 2, 360 * 2);	// ���
	IMAGEMANAGER->addImage("TitleMenu", "Resources/Images/UI/TitleMenu.bmp",
		145 * 2, 40,
		true, RGB(255, 0, 255));	// �޴�
	IMAGEMANAGER->addGPFrameImage("TitleButton", "Resources/Images/UI/TitleButton.png",
		0, 0,
		1, 1,
		false, NULL, NULL, RotateNoneFlipNone);	// �޴� ���� ���콺 ������ ��ġ ��
	IMAGEMANAGER->addImage("Cursor", "Resources/Images/UI/Cursor.bmp",
		32, 32,
		true, RGB(255, 0, 255));	// Ŀ��
	IMAGEMANAGER->addGPFrameImage("FrameDropTest", "Resources/Images/FrameDropTest.png",
		0, 0,
		35, 1,
		true, RGB(0, 0, 0), RGB(128, 128, 128), RotateNoneFlipNone);   // Ÿ��Ʋ �ΰ�
	// Sound

	// ====================MapToolScene====================
	// Image
	char key[64];
	char fileName[64];
	for (int i = 1; i <= 100; i++)
	{
		wsprintf(key, "Tile%d", i);
		wsprintf(fileName, "Resources/Images/Tile/Tile%d.bmp", i);
		IMAGEMANAGER->addImage(key, fileName,
			24, 24);
	}
	IMAGEMANAGER->addImage("FarmLayer", "Resources/Images/Tile/FarmLayer.bmp", 2184, 1800);
	IMAGEMANAGER->addFrameImage("ScrollUpButton", "Resources/Images/UI/ScrollUpButton.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ScrollDownButton", "Resources/Images/UI/ScrollUpButton.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ScrollBar", "Resources/Images/UI/ScrollBar.bmp", 15, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ScrollBarTrack", "Resources/Images/UI/ScrollBarTrack.bmp", 10, 232, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LeftButton", "Resources/Images/UI/LeftButton.bmp", 60, 20, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RightButton", "Resources/Images/UI/RightButton.bmp", 20, 20, true, RGB(255, 0, 255));
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
