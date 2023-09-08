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
	SOUNDMANAGER->addSound("Main_Menu_Final", "Resources/Sound/Main_Menu_Final.wav", true, true);
	SOUNDMANAGER->addSound("E_titleButton", "Resources/Sound/E_titleButton.wav", false, false);
	SOUNDMANAGER->addSound("E_titleButtonClick", "Resources/Sound/E_titleButtonClick.wav", false, false);


	// ====================MapToolScene====================
	// Image
	char key[64];
	char fileName[64];
	for(int j = 1; j <= 10; j++)
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
	IMAGEMANAGER->addImage("Object4", "Resources/Images/Object/Tree2.bmp", 82, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object5", "Resources/Images/Object/Stone1.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object6", "Resources/Images/Object/Stone2.bmp", 24, 24, true, RGB(255, 0, 255));
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

	IMAGEMANAGER->addImage("DynusJumpPlatform", "Resources/Images/Boss/DynusJumpPlatform.bmp",
		38 * 2, 54 * 2,
		true, RGB(255, 0, 255));	// 다이너스 점프 플랫폼

	IMAGEMANAGER->addImage("DynusHpBar", "Resources/Images/UI/DynusHpBar.bmp",
		425, 58,
		true, RGB(255, 0, 255));	// 다이너스 HpBar

	IMAGEMANAGER->addImage("ProgressBarW", "Resources/Images/UI/ProgressBarW.bmp",
		92, 14,
		true, RGB(255, 0, 255));	// 프로그래스 바 가로

	//IMAGEMANAGER->addImage("DynusJumpPlatform", "Resources/Images/Boss/DynusJumpPlatform.bmp",
	//	38 * 2, 54 * 2,
	//	true, RGB(255, 0, 255));	// 다이너스 점프 플랫폼

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

	IMAGEMANAGER->addImage("cosmetics_slot1", "Resources/Images/Inventory/cosmetics_slot1.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cosmetics_slot2", "Resources/Images/Inventory/cosmetics_slot2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cosmetics_slot3", "Resources/Images/Inventory/cosmetics_slot3.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cosmetics_slot4", "Resources/Images/Inventory/cosmetics_slot4.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cosmetics_slot5", "Resources/Images/Inventory/cosmetics_slot5.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equipment_slot1", "Resources/Images/Inventory/equipment_slot1.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equipment_slot2", "Resources/Images/Inventory/equipment_slot2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equipment_slot3", "Resources/Images/Inventory/equipment_slot3.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equipment_slot4", "Resources/Images/Inventory/equipment_slot4.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equipment_slot5", "Resources/Images/Inventory/equipment_slot5.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_slot1_keepsake", "Resources/Images/Inventory/player_slot1_keepsake.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_slot2_ring1", "Resources/Images/Inventory/player_slot2_ring1.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_slot3_amulet", "Resources/Images/Inventory/player_slot3_amulet.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player_slot4_ring2", "Resources/Images/Inventory/player_slot4_ring2.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("icon_attack_dmg+lv_combat", "Resources/Images/Inventory/icon_attack_dmg+lv_combat.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon_defense #2480984", "Resources/Images/Inventory/icon_defense #2480984.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon_hp", "Resources/Images/Inventory/icon_hp.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon_magic_damage", "Resources/Images/Inventory/icon_magic_damage.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon_mana #2486870", "Resources/Images/Inventory/icon_mana #2486870.bmp", 10, 10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("trash_button", "Resources/Images/Inventory/trash_button.bmp", 26, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sort_button", "Resources/Images/Inventory/sort_button.bmp", 26, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("drop_button", "Resources/Images/Inventory/drop_button.bmp", 26, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x_button", "Resources/Images/Inventory/x_button.bmp", 27, 28, true, RGB(255, 0, 255));

	//CraftingImage



	// shopImage

	// Sound

	// ====================
	// Image
	IMAGEMANAGER->addImage("ClockUI", "Resources/Images/UI/Clock.bmp", 69, 65, true, RGB(255, 0, 255));
	IMAGEMANAGER->addGPFrameImage("DateBar", "Resources/Images/UI/DateBar.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	IMAGEMANAGER->addGPFrameImage("TimeBar", "Resources/Images/UI/TimeBar.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	IMAGEMANAGER->addGPFrameImage("UpperRightBar", "Resources/Images/UI/UpperRightBar.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	IMAGEMANAGER->addImage("GoldIcon", "Resources/Images/UI/GoldIcon.bmp", 10, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TicketIcon", "Resources/Images/UI/TicketIcon.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("OrbIcon", "Resources/Images/UI/OrbIcon.bmp", 11, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("QuestBookIcon", "Resources/Images/UI/QuestBookIcon.bmp", 18, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SkillTreeIcon", "Resources/Images/UI/SkillTreeIcon.bmp", 23, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BarnAnimalsIcon", "Resources/Images/UI/BarnAnimalsIcon.bmp", 24, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("FishingNetIcon", "Resources/Images/UI/FishingNetIcon.bmp", 16, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addGPFrameImage("ProgressBarBottom", "Resources/Images/UI/ProgressBarBottom.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	IMAGEMANAGER->addImage("ProgressBarTop", "Resources/Images/UI/ProgressBarTop.bmp", 26, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ProgressBarFill", "Resources/Images/UI/ProgressBarFill.bmp", 24, 5);
	//Sound
	return S_OK;
}

void Resources::release(void)
{
}
