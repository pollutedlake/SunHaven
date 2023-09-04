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
	IMAGEMANAGER->addImage("DynusLayer0", "Resources/Images/Layer/DynusLayer0.bmp",
		1320, 816,
		true, RGB(255, 0, 255));	// ���̾�

	IMAGEMANAGER->addImage("StarShader", "Resources/Images/Layer/StarShader.bmp",
		960, 400);	// �� ��� �׽�Ʈ

	IMAGEMANAGER->addImage("StarShaderTest", "Resources/Images/Layer/StarShaderTest.bmp",
		960, 720,
		true, RGB(255, 0, 255));	// �� ��� �׽�Ʈ

	IMAGEMANAGER->addImage("BlueStarFill", "Resources/Images/Layer/BlueStarFill.bmp",
		402, 402);	// �Ķ� ��

	IMAGEMANAGER->addImage("DynusWing", "Resources/Images/Boss/DynusWing.bmp",
		257, 169,
		true, RGB(255, 0, 255));	// ���̳ʽ� ����

	IMAGEMANAGER->addGPFrameImage("DynusOrb", "Resources/Images/Boss/DynusOrb.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);   // ���̳ʽ� ź

	IMAGEMANAGER->addImage("DynusOrb2", "Resources/Images/Boss/DynusOrb.bmp",
		10 * 2, 10 * 2,
		true, RGB(255, 0, 255));	// ���̳ʽ� ź (���� X)

	IMAGEMANAGER->addGPFrameImage("DynusBeam", "Resources/Images/Boss/DynusBeam.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);   // ���̳ʽ� ��

	IMAGEMANAGER->addFrameImage("Shadeclow_Idle", "Resources/Images/Enemy/Ghost/Ghost_Idle.bmp",
		0, 0,
		160 * 2, 80 * 2,
		4, 2,
		true, RGB(255, 0, 255));	// ���̳ʽ� ��ȯ ���� ��Ʈ

	IMAGEMANAGER->addFrameImage("Shadeclow_Attack", "Resources/Images/Enemy/Ghost/Ghost_Attack.bmp",
		0, 0,
		440, 80,
		11, 2,
		true, RGB(255, 0, 255));	// ���̳ʽ� ��ȯ ���� ��Ʈ

	IMAGEMANAGER->addFrameImage("Shadeclow_Die", "Resources/Images/Enemy/Ghost/Ghost_Die.bmp",
		0, 0,
		560, 80,
		14, 2,
		true, RGB(255, 0, 255));	// ���̳ʽ� ��ȯ ���� ��Ʈ

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
