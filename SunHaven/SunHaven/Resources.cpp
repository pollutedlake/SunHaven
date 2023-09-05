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
	IMAGEMANAGER->addImage("Object1", "Resources/Images/Object/Grass1.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object2", "Resources/Images/Object/Grass2.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object3", "Resources/Images/Object/Tree1.bmp", 89, 121, true, RGB(255, 0, 255));
	// Sound

	// ====================DynusScene====================
	// Image
	IMAGEMANAGER->addImage("DynusLayer0", "Resources/Images/Layer/DynusLayer0.bmp",
		1320, 816,
		true, RGB(255, 0, 255));	// 레이어

	IMAGEMANAGER->addImage("StarShader", "Resources/Images/Layer/StarShader.bmp",
		960, 400);	// 별 배경 테스트

	IMAGEMANAGER->addImage("StarShaderTest", "Resources/Images/Layer/StarShaderTest.bmp",
		960, 720,
		true, RGB(255, 0, 255));	// 별 배경 테스트

	IMAGEMANAGER->addImage("BlueStarFill", "Resources/Images/Layer/BlueStarFill.bmp",
		402, 402);	// 파란 별

	IMAGEMANAGER->addImage("DynusWing", "Resources/Images/Boss/DynusWing.bmp",
		257, 169,
		true, RGB(255, 0, 255));	// 다이너스 날개

	IMAGEMANAGER->addGPFrameImage("DynusOrb", "Resources/Images/Boss/DynusOrb.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);   // 다이너스 탄

	IMAGEMANAGER->addImage("DynusOrb2", "Resources/Images/Boss/DynusOrb.bmp",
		10 * 2, 10 * 2,
		true, RGB(255, 0, 255));	// 다이너스 탄 (알파 X)

	IMAGEMANAGER->addGPFrameImage("DynusBeam", "Resources/Images/Boss/DynusBeam.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);   // 다이너스 빔

	IMAGEMANAGER->addFrameImage("Shadeclow_Idle", "Resources/Images/Enemy/Ghost/Ghost_Idle.bmp",
		0, 0,
		160 * 2, 80 * 2,
		4, 2,
		true, RGB(255, 0, 255));	// 다이너스 소환 몬스터 고스트

	IMAGEMANAGER->addFrameImage("Shadeclow_Attack", "Resources/Images/Enemy/Ghost/Ghost_Attack.bmp",
		0, 0,
		440, 80,
		11, 2,
		true, RGB(255, 0, 255));	// 다이너스 소환 몬스터 고스트

	IMAGEMANAGER->addFrameImage("Shadeclow_Die", "Resources/Images/Enemy/Ghost/Ghost_Die.bmp",
		0, 0,
		560, 80,
		14, 2,
		true, RGB(255, 0, 255));	// 다이너스 소환 몬스터 고스트

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
