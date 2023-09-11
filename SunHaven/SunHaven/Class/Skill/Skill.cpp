#include "Stdafx.h"
#include "Skill.h"

void Skill::init(string index, string name, string type, int tier, string description,
	double value1[], double value2[])
{
	
}

HRESULT Skill::init()
{
	_image.skillIcon =
		IMAGEMANAGER->addImage("ä����ų������",
			"Resources/Images/Skill/mining/mining_skill_tree_icons.bmp"
			, 429, 147, true, RGB(255, 0, 255));
	_image.skillFrame =
		IMAGEMANAGER->addImage("ä����ų������",
			"Resources/Images/Skill/miningSkillFrame.bmp"
			, 452, 203, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("��罺ų������",
		"Resources/Images/Skill/farming/farming_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��罺ų������",
		"Resources/Images/Skill/farmingSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Ž�轺ų������",
		"Resources/Images/Skill/exploration/exploration_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ž�轺ų������",
		"Resources/Images/Skill/explorationSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������ų������",
		"Resources/Images/Skill/combat/combat_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ų������",
		"Resources/Images/Skill/combatSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���ý�ų������",
		"Resources/Images/Skill/fishing/fishing_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ý�ų������",
		"Resources/Images/Skill/fishingSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�׵θ�0", "Resources/Images/Skill/skills_border_0of3.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׵θ�1", "Resources/Images/Skill/skills_border_1of3.bmp", 34, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׵θ�2", "Resources/Images/Skill/skills_border_2of3.bmp", 34, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׵θ�3", "Resources/Images/Skill/skills_border_3of3.bmp", 40, 40, true, RGB(255, 0, 255));





	_image.rc = RectMakeCenter(CENTER_X-1, CENTER_Y+18, 429, 147);
	_image.frameRC = RectMakeCenter(CENTER_X, CENTER_Y, 452, 203);
	_descriptionRC = RectMake(_ptMouse.x, _ptMouse.y, 500, 300);


	
	

	return S_OK;
}

void Skill::release()
{
	// ! Do Nothing
}

void Skill::update()
{
	// ! Do Nothing
}

void Skill::render()
{
	// ! Do Nothing
}
