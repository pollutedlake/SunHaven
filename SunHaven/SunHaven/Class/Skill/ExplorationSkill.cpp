#include "Stdafx.h"
#include "ExplorationSkill.h"

void ExplorationSkill::init(string index, string name, string type, int tier, string description,
	double value1[], double value2[])
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
}

HRESULT ExplorationSkill::init()
{
	Skill::init();

	_img.skillIcon = IMAGEMANAGER->findImage("탐험스킬아이콘");
	_img.skillFrame = IMAGEMANAGER->findImage("탐험스킬프레임");

	_img.rc = RectMakeCenter(CENTER_X - 1, CENTER_Y + 18, 429, 147);
	_img.frameRC = RectMakeCenter(CENTER_X, CENTER_Y, 452, 203);


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_borderImg[10 * i + j].maxSkillLV = 3;
			_borderImg[10 * i + j].skillLV = 0;


			_borderImg[10 * i + j].borderImg = IMAGEMANAGER->findImage("테두리0");

			_borderImg[10 * i + j].iconRC = RectMakeCenter(437 + (45 * j), 317 + (41 * i),
				IMAGEMANAGER->findImage("테두리0")->getWidth(),
				IMAGEMANAGER->findImage("테두리0")->getHeight());

			_borderImg[10 * i + j].borderRC = RectMakeCenter(437 + (45 * j), 317 + (41 * i),
				_borderImg[10 * i + j].borderImg->getWidth(), _borderImg[10 * i + j].borderImg->getHeight());
		}
	}

	return S_OK;
}

void ExplorationSkill::release()
{

}

void ExplorationSkill::update()
{
	for (int i = 0; i < 40; i++)
	{
		if (PtInRect(&_borderImg[i].iconRC, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
			{
				cout << i << endl;
				_borderImg[i].skillLV--;

				if (_borderImg[i].skillLV < 0)
					_borderImg[i].skillLV = 0;
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				cout << i << endl;
				_borderImg[i].skillLV++;

				if (_borderImg[i].skillLV > _borderImg[i].maxSkillLV)
					_borderImg[i].skillLV = _borderImg[i].maxSkillLV;
			}

			wsprintf(str, "테두리%d", _borderImg[i].skillLV);
			_borderImg[i].borderImg = IMAGEMANAGER->findImage(str);

			_borderImg[i].borderRC =
				RectMakeCenter(_borderImg[i].iconRC.left + (_borderImg[i].iconRC.right - _borderImg[i].iconRC.left) / 2,
					_borderImg[i].iconRC.top + (_borderImg[i].iconRC.bottom - _borderImg[i].iconRC.top) / 2,
					_borderImg[i].borderImg->getWidth(), _borderImg[i].borderImg->getHeight());
		}
	}
}

void ExplorationSkill::render()
{
	_img.skillFrame->render(getMemDC(), _img.frameRC.left, _img.frameRC.top);
	_img.skillIcon->render(getMemDC(), _img.rc.left, _img.rc.top);

	for (int i = 0; i < 40; i++)
	{
		_borderImg[i].borderImg->render(getMemDC(), _borderImg[i].borderRC.left, _borderImg[i].borderRC.top);
	}
}

