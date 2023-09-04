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
	// Sound

	// ====================MapToolScene====================
	// Image
	char key[64];
	char fileName[64];
	for(int j = 1; j <= 5; j++)
	{
		for (int i = 1; i <= 100; i++)
		{
			wsprintf(key, "Tile%d-%d", j, i);
			wsprintf(fileName, "Resources/Images/Tile/Tile%d-%d.bmp", j, i);
			IMAGEMANAGER->addImage(key, fileName,
				24, 24, true, RGB(255, 255, 255));
		}
	}
	IMAGEMANAGER->addImage("FarmLayer2", "Resources/Images/Tile/FarmLayer2.bmp", 2184, 2400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("FarmLayer3", "Resources/Images/Tile/FarmLayer3.bmp", 2184, 2400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("FarmLayer4", "Resources/Images/Tile/FarmLayer4.bmp", 2184, 2400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("FarmLayer5", "Resources/Images/Tile/FarmLayer5.bmp", 2184, 2400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ScrollUpButton", "Resources/Images/UI/ScrollUpButton.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ScrollDownButton", "Resources/Images/UI/ScrollUpButton.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ScrollBar", "Resources/Images/UI/ScrollBar.bmp", 15, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ScrollBarTrack", "Resources/Images/UI/ScrollBarTrack.bmp", 10, 232, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LeftButton", "Resources/Images/UI/LeftButton.bmp", 60, 20, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RightButton", "Resources/Images/UI/RightButton.bmp", 60, 20, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Button1", "Resources/Images/UI/Button1.bmp", 300, 22, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LayerShowButton", "Resources/Images/UI/LayerShowButton.bmp", 54, 17, 2, 1, true, RGB(255, 0, 255));
	// Sound

	// ====================DynusScene====================
	// Image

	// Sound

	// ====================FarmScene====================
	// Image

	// Sound

	// ====================ShopScene====================
	// invenImage
	IMAGEMANAGER->addImage("invenBG", "Resources/Images/Inventory/invenBG.bmp", WINSIZE_X/2, WINSIZE_Y/2);
	IMAGEMANAGER->addImage("player_bg", "Resources/Images/Inventory/player_bg.bmp", WINSIZE_X / 6, WINSIZE_Y / 2 - 80);
	IMAGEMANAGER->addImage("bg_backpack_items", "Resources/Images/Inventory/bg_backpack_items.bmp", WINSIZE_X/4 + 20, WINSIZE_Y/2 - 80);
	IMAGEMANAGER->addImage("player_bg_name_banner", "Resources/Images/Inventory/player_bg_name_banner.bmp", WINSIZE_X/6, 20,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("item_bg", "Resources/Images/Inventory/item_bg.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ironBoots", "Resources/Images/Inventory/ironBoots.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ironChestPlate", "Resources/Images/Inventory/ironChestPlate.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ironGloves", "Resources/Images/Inventory/ironGloves.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ironSword", "Resources/Images/Inventory/ironSword.bmp", 32, 32, true, RGB(255, 0, 255));
	// shopImage

	// Sound

	return S_OK;
}

void Resources::release(void)
{
}
