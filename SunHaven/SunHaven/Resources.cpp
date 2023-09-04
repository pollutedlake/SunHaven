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
	IMAGEMANAGER->addImage("Tile1", "Resources/Images/Tile/Tile1.bmp",
		24, 24,
		true, RGB(255, 0, 255));
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
	// Image

	// Sound

	return S_OK;
}

void Resources::release(void)
{
}
