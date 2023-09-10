#include "Stdafx.h"
#include "MiningSkill.h"

void MiningSkill::init(string index, string name, string type, int tier, string description, float value1[], float value2[], const char* filePath, int width, int height)
{
	_index = index;
	_type = type;
	_tier = tier;
	_description = description;

	for (int i = 0; i < 3; i++)
	{
		_value1[i] = value1[i];
		_value2[i] = value2[i];
	}

	_filePath = filePath;
}

HRESULT MiningSkill::init()
{
	_image.skillIcon =
		IMAGEMANAGER->addImage("채광스킬아이콘",
			"Resources/Images/Skill/mining/mining_skill_tree_icons.bmp"
			, 421, 147, true, RGB(255, 0, 255));

	_image.rc = RectMakeCenter(CENTER_X, CENTER_Y, 421, 147);


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			/*_image[10 * i + j].rc = RectMakeCenter(200 + (17 * j), 200 + (17 * i),
				IMAGEMANAGER->findImage(imgKey)->getWidth(),
				IMAGEMANAGER->findImage(imgKey)->getHeight());*/
		}
	}

	return S_OK;
}

void MiningSkill::release()
{
}

void MiningSkill::update()
{
}

void MiningSkill::render()
{
	_image.skillIcon->render(getMemDC(), _image.rc.left, _image.rc.top);
}
