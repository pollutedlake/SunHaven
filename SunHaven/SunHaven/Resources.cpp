#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	IMAGEMANAGER->addGPFrameImage("대시어택",
		"Resources/Images/Player/dash_slash.png",
		0, 0, 7, 2, false, NULL, RotateNoneFlipNone);
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
	IMAGEMANAGER->addImage("MineLayer3", "Resources/Images/Tile/MineLayer3.bmp", 1704, 1032, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MineLayer5", "Resources/Images/Tile/MineLayer5.bmp", 1704, 1032, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Wall", "Resources/Images/UI/Wall.bmp", 10, 81);
	IMAGEMANAGER->addFrameImage("ScrollUpButton", "Resources/Images/UI/ScrollUpButton.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ScrollDownButton", "Resources/Images/UI/ScrollUpButton.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ScrollBar", "Resources/Images/UI/ScrollBar.bmp", 15, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ScrollBarTrack", "Resources/Images/UI/ScrollBarTrack.bmp", 10, 232, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LeftButton", "Resources/Images/UI/LeftButton.bmp", 60, 20, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RightButton", "Resources/Images/UI/RightButton.bmp", 60, 20, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Button1", "Resources/Images/UI/Button1.bmp", 300, 22, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BackButton", "Resources/Images/UI/BackButton.bmp", 78, 86, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LayerShowButton", "Resources/Images/UI/LayerShowButton.bmp", 54, 17, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object1", "Resources/Images/Object/Grass1.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object2", "Resources/Images/Object/Grass2.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object3", "Resources/Images/Object/Tree1.bmp", 89, 121, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object4", "Resources/Images/Object/Tree2.bmp", 82, 108, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object5", "Resources/Images/Object/Stone1.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Object6", "Resources/Images/Object/Stone2.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addGPFrameImage("Tree1Cut", "Resources/Images/Object/Tree1Cut.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	IMAGEMANAGER->addGPFrameImage("Tree2Cut", "Resources/Images/Object/Tree2Cut.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	IMAGEMANAGER->addImage("Stump", "Resources/Images/Object/Stump.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Window","Resources/Images/UI/Window.bmp", 271, 192, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WindowHead","Resources/Images/UI/WindowHead.bmp", 271, 49, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WindowBottom","Resources/Images/UI/WindowBottom.bmp", 271, 189, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MapToolBG","Resources/Images/UI/MapToolBG.bmp", 314, 186, true, RGB(255, 0, 255));
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

	IMAGEMANAGER->addImage("DynusBulletPortal", "Resources/Images/Boss/DynusBulletPortal.bmp",
		22, 26,
		true, RGB(255, 0, 255));	// 다이너스 탄 포탈

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
		440 * 2, 80 * 2,
		11, 2,
		true, RGB(255, 0, 255));	// 다이너스 소환 몬스터 고스트

	IMAGEMANAGER->addFrameImage("Shadeclow_Die", "Resources/Images/Enemy/Ghost/Ghost_Die.bmp",
		0, 0,
		560 * 2, 80 * 2,
		14, 2,
		true, RGB(255, 0, 255));	// 다이너스 소환 몬스터 고스트

	IMAGEMANAGER->addImage("DynusJumpPlatform", "Resources/Images/Boss/DynusJumpPlatform.bmp",
		38 * 2, 54 * 2,
		true, RGB(255, 0, 255));	// 다이너스 점프 플랫폼

	IMAGEMANAGER->addImage("DynusGuardPlatformL", "Resources/Images/Boss/DynusGuardPlatformL.bmp",
		69, 117,
		true, RGB(255, 0, 255));	// 다이너스 점프 플랫폼

	IMAGEMANAGER->addImage("DynusGuardPlatformR", "Resources/Images/Boss/DynusGuardPlatformR.bmp",
		70, 119,
		true, RGB(255, 0, 255));	// 다이너스 점프 플랫폼

	IMAGEMANAGER->addImage("DynusHpBar", "Resources/Images/UI/DynusHpBar.bmp",
		425, 58,
		true, RGB(255, 0, 255));	// 다이너스 HpBar

	IMAGEMANAGER->addImage("DynusHpBarBorder", "Resources/Images/UI/DynusHpBarBorder.bmp",
		425, 58,
		true, RGB(255, 0, 255));	// 다이너스 HpBar

	IMAGEMANAGER->addImage("ProgressBarW", "Resources/Images/UI/ProgressBarW.bmp",
		92, 14,
		true, RGB(255, 0, 255));	// 프로그래스 바 가로

	IMAGEMANAGER->addImage("ProgressBarBGW", "Resources/Images/UI/ProgressBarBGW.bmp",
		92, 14,
		true, RGB(255, 0, 255));	// 프로그래스 바 배경 가로

	IMAGEMANAGER->addImage("GuardMine", "Resources/Images/Boss/GuardMine.bmp",
		47, 44,
		true, RGB(255, 0, 255));	// 프로그래스 바 배경 가로

	//IMAGEMANAGER->addImage("DynusJumpPlatform", "Resources/Images/Boss/DynusJumpPlatform.bmp",
	//	38 * 2, 54 * 2,
	//	true, RGB(255, 0, 255));	// 다이너스 점프 플랫폼

	// Sound   
	SOUNDMANAGER->addSound("dynus_battle_v7", "Resources/Sound/dynus_battle_v7.wav", true, true);
	SOUNDMANAGER->addSound("DynusCast2", "Resources/Sound/DynusCast2.wav", false, false);
	SOUNDMANAGER->addSound("RockCandyMonster1Death1", "Resources/Sound/RockCandyMonster1Death1.wav", false, false);
	SOUNDMANAGER->addSound("MonsterBookDeath1", "Resources/Sound/MonsterBookDeath1.wav", false, false);



	// ====================DizzyScene====================
	// Image

	IMAGEMANAGER->addImage("DizzyLayer", "Resources/Images/Layer/DizzyLayer.bmp",
		1464 * 1.5, 1008 * 1.5,
		true, RGB(255, 0, 255));	// 레이어

	IMAGEMANAGER->addImage("DizzyHpBarBorder", "Resources/Images/UI/DizzyHpBarBorder.bmp",
		442, 54,
		true, RGB(255, 0, 255));	// 디지 HpBar

	IMAGEMANAGER->addFrameImage("DizzyMeteor", "Resources/Images/Boss/Dizzy/DizzyMeteor.bmp",
		360, 62,
		6, 1,
		true, RGB(255, 0, 255));	// 디지 메테오

	IMAGEMANAGER->addImage("Gem0", "Resources/Images/Boss/Dizzy/Dizzy_Gems_0.bmp",
		27, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Gem1", "Resources/Images/Boss/Dizzy/Dizzy_Gems_1.bmp",
		22, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Gem2", "Resources/Images/Boss/Dizzy/Dizzy_Gems_2.bmp",
		28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Gem3", "Resources/Images/Boss/Dizzy/Dizzy_Gems_3.bmp",
		20, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Gem4", "Resources/Images/Boss/Dizzy/Dizzy_Gems_4.bmp",
		28, 30, true, RGB(255, 0, 255));


	// Sound  
	SOUNDMANAGER->addSound("DizzyConfusion1", "Resources/Sound/DizzyConfusion1.wav", false, false);
	SOUNDMANAGER->addSound("DizzyDeath1", "Resources/Sound/DizzyDeath1.wav", false, false);
	SOUNDMANAGER->addSound("DizzyRocksFalling1", "Resources/Sound/DizzyRocksFalling1.wav", false, false);
	SOUNDMANAGER->addSound("DizzyTransform1", "Resources/Sound/DizzyTransform1.wav", false, false);
	SOUNDMANAGER->addSound("DizzyWake1", "Resources/Sound/DizzyWake1.wav", false, false);
	SOUNDMANAGER->addSound("boss_music1-2", "Resources/Sound/boss_music1-2.wav", true, true);
	SOUNDMANAGER->addSound("Mines_5_OST_Final_Loop1", "Resources/Sound/Mines_5_OST_Final_Loop1.wav", true, true);
	SOUNDMANAGER->addSound("DizzyDeath1", "Resources/Sound/DizzyDeath1.wav", false, false);

	// ====================MineScene====================
	// Image
	IMAGEMANAGER->addFrameImage("FlameImp_Fireball", "Resources/Images/Enemy/FlameImp/FlameImp_Fireball.bmp",
		112, 19,
		4, 1,
		true, RGB(255, 0, 255));	// 적 파이어볼

	// Sound 
	SOUNDMANAGER->addSound("Candy_Mines_Final2", "Resources/Sound/Candy_Mines_Final2.wav", true, true);


	// ====================FarmScene====================
	// Image
	IMAGEMANAGER->addImage("경작지", "Resources/Images/Object/Farm_dirt.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("젖은 경작지", "Resources/Images/Object/Farm_wetdirt.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HitEffect", "Resources/Images/Player/HitEffect.bmp", 288, 48, 6, 1, true, RGB(255, 0, 255));

	// Sound 
	SOUNDMANAGER->addSound("Player_Farm_Var1_Final1", "Resources/Sound/Player_Farm_Var1_Final1.wav", true, true);
	SOUNDMANAGER->addSound("ScytheCuttingCrops1", "Resources/Sound/ScytheCuttingCrops1.wav", false, false);
	SOUNDMANAGER->addSound("TreeHit1", "Resources/Sound/TreeHit1.wav", false, false);
	SOUNDMANAGER->addSound("RockHit1", "Resources/Sound/RockHit1.wav", false, false);

	// ====================ShopScene====================
	
	// itemImage(슬롯x) icon_scythe2
	IMAGEMANAGER->addImage("icon_scythe2", "Resources/Images/Item/icon_scythe2.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("녹슨 곡괭이", "Resources/Images/Item/icon_rusty_pickaxe2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 곡괭이", "Resources/Images/Item/icon_adamant_pickaxe2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("녹슨 괭이", "Resources/Images/Item/icon_rusty_hoe2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 괭이", "Resources/Images/Item/icon_adamant_hoe2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("녹슨 도끼", "Resources/Images/Item/icon_rusty_axe2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 도끼", "Resources/Images/Item/icon_adamant_axe2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("녹슨 물뿌리개", "Resources/Images/Item/icon_rusty_wateringCan2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 물뿌리개", "Resources/Images/Item/icon_adamant_wateringCan2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기본 낚싯대", "Resources/Images/Item/icon_basic_fishingRod2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿠키", "Resources/Images/Item/icon_cookies2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 반지", "Resources/Images/Item/icon_adamant_accessory2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 검", "Resources/Images/Item/icon_adamant_sword2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검", "Resources/Images/Item/icon_basic_sword2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 쇠뇌", "Resources/Images/Item/icon_adamant_crossbow2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쇠뇌", "Resources/Images/Item/icon_basic_crossbow2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 헬멧", "Resources/Images/Item/icon_adamant_helmet2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 갑옷 (상의)", "Resources/Images/Item/icon_adamant_chestPlate2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 갑옷 (하의)", "Resources/Images/Item/icon_adamant_legs2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 장갑", "Resources/Images/Item/icon_adamant_gloves2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 쇠뇌", "Resources/Images/Item/icon_adamant_crossbow2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("연애 증표", "Resources/Images/Item/icon_Romance_Keepsake2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("통나무", "Resources/Images/Item/icon_log2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("돌", "Resources/Images/Item/icon_stone2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("나무 판자", "Resources/Images/Item/icon_woodplank2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("밀", "Resources/Images/Item/icon_wheat2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("밀 씨앗", "Resources/Images/Item/icon_wheat_seed_bag2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("일반 물고기", "Resources/Images/Item/icon_fish_sunhaven_10.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 광석", "Resources/Images/Item/icon_adamant_ore2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아다만트 바", "Resources/Images/Item/icon_adamant_bar2.bmp", 32, 32, true, RGB(255, 0, 255));
	
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

	IMAGEMANAGER->addImage("item_bg_common", "Resources/Images/Inventory/item_bg_common.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_bg_rare", "Resources/Images/Inventory/item_bg_rare.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("selection_hover-click-selected_0", "Resources/Images/Inventory/selection_hover-click-selected_0.bmp", 34, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tooltip_bg", "Resources/Images/Inventory/tooltip_bg.bmp", 137, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tooltip_bg_flipped", "Resources/Images/Inventory/tooltip_bg_flipped.bmp", 137, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("combat_skill_tree_icons_0", "Resources/Images/Inventory/combat_skill_tree_icons_0.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("combat_skill_tree_icons_6", "Resources/Images/Inventory/combat_skill_tree_icons_6.bmp", 32, 32, true, RGB(255, 0, 255));

	//CraftingImage
	//IMAGEMANAGER->addImage("cooking_bg1" , "Resources/Images/CraftingTable/cooking_bg1.bmp",)


	// shopImage 
	IMAGEMANAGER->addImage("Shop_Bg", "Resources/Images/Shop/Shop_Bg.bmp", WINSIZE_X, WINSIZE_Y,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("store_bg", "Resources/Images/Shop/store_bg.bmp", 522, 654, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("store_item_bg", "Resources/Images/Shop/store_item_bg.bmp", 231, 93, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("store_upper_icon_wip", "Resources/Images/Shop/store_upper_icon_wip.bmp", 56, 54, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("x1_button", "Resources/Images/Shop/x1_button.bmp", 22, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x1_button_normal", "Resources/Images/Shop/x1_button_normal.bmp", 22, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x5_button", "Resources/Images/Shop/x5_button.bmp", 23, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x5_button_normal", "Resources/Images/Shop/x5_button_normal.bmp", 23, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x20_button", "Resources/Images/Shop/x20_button.bmp", 28, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x20_button_normal", "Resources/Images/Shop/x20_button_normal.bmp", 28, 20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("UI_icon_coin", "Resources/Images/Shop/UI_icon_coin.bmp", 10, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goldbanner", "Resources/Images/Shop/goldbanner.bmp", 133, 35, true, RGB(255, 0, 255));
	// Sound
	SOUNDMANAGER->addSound("E_getItem_Sound1", "Resources/Sound/E_getItem_Sound1.wav", false, false);
	SOUNDMANAGER->addSound("Salon_Final1", "Resources/Sound/Salon_Final1.wav", true, true);

	// ====================
	// Image
	IMAGEMANAGER->addImage("ClockUI", "Resources/Images/UI/Clock.bmp", 69, 65, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrayBar", "Resources/Images/UI/GrayBar.bmp", 61, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrayBarLT", "Resources/Images/UI/GrayBarLT.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrayBarLB", "Resources/Images/UI/GrayBarLB.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrayBarRT", "Resources/Images/UI/GrayBarRT.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GrayBarRB", "Resources/Images/UI/GrayBarRB.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RedBar", "Resources/Images/UI/RedBar.bmp", 61, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RedBarLT", "Resources/Images/UI/RedBarLT.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RedBarLB", "Resources/Images/UI/RedBarLB.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RedBarRT", "Resources/Images/UI/RedBarRT.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RedBarRB", "Resources/Images/UI/RedBarRB.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BlueBar", "Resources/Images/UI/BlueBar.bmp", 61, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BlueBarLT", "Resources/Images/UI/BlueBarLT.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BlueBarLB", "Resources/Images/UI/BlueBarLB.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BlueBarRT", "Resources/Images/UI/BlueBarRT.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BlueBarRB", "Resources/Images/UI/BlueBarRB.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HpIcon", "Resources/Images/UI/HpIcon.bmp", 10, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ManaIcon", "Resources/Images/UI/ManaIcon.bmp", 16, 16, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addImage("ObjectHpBarTop", "Resources/Images/UI/ProgressBarTop.bmp", 26, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ObjectHpBarFill", "Resources/Images/UI/ProgressBarFill.bmp", 24, 5);
	//Sound

	// =======================================Intro Scene=========================
	// Image
	IMAGEMANAGER->addFrameImage("LynnMom2", "Resources/Images/Intro/LynnMom2.bmp", 364, 354, 7, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LynnMom1", "Resources/Images/Intro/LynnMom1.bmp", 936, 59, 18, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("LynnMomHouse", "Resources/Images/Intro/LynnMomHouse.bmp", 654, 462, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PlayerHouse", "Resources/Images/Tile/PlayerHouse.bmp", 251, 198, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Train1", "Resources/Images/Intro/Train1.bmp", 686, 357, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Train2", "Resources/Images/Intro/Train2.bmp", 643, 357, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LynnWalkSheet", "Resources/Images/Intro/LynnWalkSheet.bmp", 840, 104, 20, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LynnBlinkSheet", "Resources/Images/Intro/LynnBlinkSheet.bmp", 378, 52, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LynnBreathingSheet", "Resources/Images/Intro/LynnBreathingSheet.bmp", 1008, 52, 24, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LynnTrainSheet", "Resources/Images/Intro/LynnTrainSheet.bmp", 750, 104, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("DialogWindow2", "Resources/Images/Intro/DialogWindow2.bmp", 354, 146, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("DialogWindow1", "Resources/Images/Intro/DialogWindow1.bmp", 354, 146, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Dialog린", "Resources/Images/Intro/DialogLynn.bmp", 648, 197, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LynnSadSheet", "Resources/Images/Intro/LynnSadSheet.bmp", 1680, 52, 40, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Black", "Resources/Images/Intro/Black.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SelectAnswerBG", "Resources/Images/Intro/SelectAnswerBG.bmp", 350, 30);
	IMAGEMANAGER->addFrameImage("LynnSadSheet", "Resources/Images/Intro/LynnSadSheet.bmp", 1680, 52, 40, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger1", "Resources/Images/Intro/TrainPassenger01.bmp", 198, 185, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger2", "Resources/Images/Intro/TrainPassenger02.bmp", 560, 39, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger3", "Resources/Images/Intro/TrainPassenger03.bmp", 228, 215, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger4", "Resources/Images/Intro/TrainPassenger04.bmp", 232, 176, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger5", "Resources/Images/Intro/TrainPassenger05.bmp", 680, 38, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger6", "Resources/Images/Intro/TrainPassenger06.bmp", 800, 39, 32, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger7", "Resources/Images/Intro/TrainPassenger07.bmp", 256, 45, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger8", "Resources/Images/Intro/TrainPassenger08.bmp", 300, 78, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger9", "Resources/Images/Intro/TrainPassenger09.bmp", 420, 100, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger10", "Resources/Images/Intro/TrainPassenger10.bmp", 984, 104, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainPassenger11", "Resources/Images/Intro/TrainPassenger11.bmp", 192, 90, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CatSleep", "Resources/Images/Intro/CatSleep.bmp", 442, 22, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RainCloud", "Resources/Images/Intro/RainCloud.bmp", 860, 46, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainWindow1", "Resources/Images/Intro/TrainWindow1.bmp", 870, 444, 10, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TrainWindow2", "Resources/Images/Intro/TrainWindow2.bmp", 870, 444, 10, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Frog", "Resources/Images/Intro/Frog.bmp", 180, 90, 6, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addGPFrameImage("CoffeeStream", "Resources/Images/UI/CoffeeStream.png",
		0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	// Sound 
	SOUNDMANAGER->addSound("E_TextScroll3", "Resources/Sound/E_TextScroll3.wav", false, false);
	SOUNDMANAGER->addSound("인트로 린하우스", "Resources/Sound/인트로 린하우스.wav", true, true);
	SOUNDMANAGER->addSound("인트로 기차안 브금", "Resources/Sound/인트로 기차안 브금.wav", true, true);
	SOUNDMANAGER->addSound("SceneTransition1", "Resources/Sound/SceneTransition1.wav", false, false);
	SOUNDMANAGER->addSound("E_인트로 대장장이", "Resources/Sound/E_인트로 대장장이.wav", false, false);
	


	return S_OK;
}

void Resources::release(void)
{
}
