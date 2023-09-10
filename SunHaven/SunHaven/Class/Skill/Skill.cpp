#include "Stdafx.h"
#include "Skill.h"

void Skill::init(string index, string name, string type, int tier, string description, float value1[], float value2[], const char* filePath, int width, int height)
{
	
}

HRESULT Skill::init()
{
	_image.skillIcon =
		IMAGEMANAGER->addImage("채광스킬아이콘",
			"Resources/Images/Skill/mining/mining_skill_tree_icons.bmp"
			, 429, 147, true, RGB(255, 0, 255));
	_image.skillFrame =
		IMAGEMANAGER->addImage("채광스킬프레임",
			"Resources/Images/Skill/miningSkillFrame.bmp"
			, 452, 203, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("농사스킬아이콘",
		"Resources/Images/Skill/farming/farming_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("농사스킬프레임",
		"Resources/Images/Skill/farmingSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("탐험스킬아이콘",
		"Resources/Images/Skill/exploration/exploration_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("탐험스킬프레임",
		"Resources/Images/Skill/explorationSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("전투스킬아이콘",
		"Resources/Images/Skill/combat/combat_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("전투스킬프레임",
		"Resources/Images/Skill/combatSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("낚시스킬아이콘",
		"Resources/Images/Skill/fishing/fishing_skill_tree_icons.bmp"
		, 429, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("낚시스킬프레임",
		"Resources/Images/Skill/fishingSkillFrame.bmp"
		, 452, 203, true, RGB(255, 0, 255));









	_image.rc = RectMakeCenter(CENTER_X-1, CENTER_Y+18, 429, 147);
	_image.frameRC = RectMakeCenter(CENTER_X, CENTER_Y, 452, 203);



	
	IMAGEMANAGER->addImage("테두리0", "Resources/Images/Skill/skills_border_0of3.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("테두리1", "Resources/Images/Skill/skills_border_1of3.bmp", 34, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("테두리2", "Resources/Images/Skill/skills_border_2of3.bmp", 34, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("테두리3", "Resources/Images/Skill/skills_border_3of3.bmp", 40, 40, true, RGB(255, 0, 255));
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_img[10 * i + j].maxSkillLV = 3;
			_img[10 * i + j].skillLV = 0;

			_img[10 * i + j].borderImg =IMAGEMANAGER->findImage("테두리0");

			_img[10 * i + j].iconRC = RectMakeCenter(437 + (45 * j), 317 + (41 * i),
				24, 24);
			_img[10 * i + j].borderRC = RectMakeCenter(437 + (45 * j), 317 + (41 * i),
				_img[10 * i + j].borderImg->getWidth(), _img[10 * i + j].borderImg->getHeight());
		}
	}

	return S_OK;
}

void Skill::release()
{
}

void Skill::update()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_image.skillIcon =
			IMAGEMANAGER->findImage("탐험스킬아이콘");
		_image.skillFrame =
			IMAGEMANAGER->findImage("탐험스킬프레임");
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_image.skillIcon =
			IMAGEMANAGER->findImage("농사스킬아이콘");
		_image.skillFrame =
			IMAGEMANAGER->findImage("농사스킬프레임");
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_image.skillIcon =
			IMAGEMANAGER->findImage("채광스킬아이콘");
		_image.skillFrame =
			IMAGEMANAGER->findImage("채광스킬프레임");
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_image.skillIcon =
			IMAGEMANAGER->findImage("전투스킬아이콘");
		_image.skillFrame =
			IMAGEMANAGER->findImage("전투스킬프레임");
	}
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_image.skillIcon =
			IMAGEMANAGER->findImage("낚시스킬아이콘");
		_image.skillFrame =
			IMAGEMANAGER->findImage("낚시스킬프레임");
	}


	for (int i = 0; i < 40; i++)
	{
		if (PtInRect(&_img[i].iconRC, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				cout << i << endl;
				_img[i].skillLV--;

				if (_img[i].skillLV < 0)
					_img[i].skillLV = 0;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				cout << i << endl;
				_img[i].skillLV++;

				if (_img[i].skillLV > _img[i].maxSkillLV)
					_img[i].skillLV = _img[i].maxSkillLV;
			}

			wsprintf(str, "테두리%d", _img[i].skillLV);
			_img[i].borderImg = IMAGEMANAGER->findImage(str);

			_img[i].borderRC =
				RectMakeCenter(_img[i].iconRC.left + (_img[i].iconRC.right - _img[i].iconRC.left) / 2,
					_img[i].iconRC.top + (_img[i].iconRC.bottom - _img[i].iconRC.top) / 2,
					_img[i].borderImg->getWidth(), _img[i].borderImg->getHeight());
		}
	}
}

void Skill::render()
{
	_image.skillFrame->render(getMemDC(), _image.frameRC.left, _image.frameRC.top);
	_image.skillIcon->render(getMemDC(),_image.rc.left,_image.rc.top);


	for (int i = 0; i < 40; i++)
	{
		_img[i].borderImg->render(getMemDC(), _img[i].borderRC.left, _img[i].borderRC.top);
	}
}
