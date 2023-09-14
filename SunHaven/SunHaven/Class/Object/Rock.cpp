#include "Stdafx.h"
#include "Rock.h"

HRESULT Rock::init(void)
{
	return S_OK;
}

HRESULT Rock::init(LivingObjectType type, POINT tilePos)
{
	_type = type;
	char str[64];
	wsprintf(str, "Object%d", (int)type + 1);
	_image = IMAGEMANAGER->findImage(str);
	_tilePos = tilePos;
	_halfTrans = false;
	switch (_type)
	{
	case ROCK1:
		_maxHp = 5;
		_dropItemList.push("4-1");
		break;
	case ROCK2:
		_maxHp = 10;
		_dropItemList.push("4-6");
		break;
	}
	_curHp = _maxHp;
	_hpBar = new ProgressBar;
	_hpBar->init("ObjectHpBarTop", "", "ObjectHpBarFill", NULL, NULL, 36, 7);
	_hpBarOffsetX = 4;
	_hpBarOffsetY = 36;
	_beforeHitRC = { NULL, NULL, NULL, NULL };
	_hitRC = { NULL, NULL, NULL, NULL };
	_hit = false;
	return S_OK;
}

void Rock::release(void)
{
}

void Rock::update(void)
{
	_hpBar->setX(_cx - _hpBarOffsetX);
	_hpBar->setY(_cy - _hpBarOffsetY);
	_hpBar->update();
	_hpBar->setGauge(_curHp, _maxHp);
	_collisionRC = RectMakeCenter(_cx, _cy, TILEWIDTH * 1.5f, TILEHEIGHT * 1.5f);
	if (_hitTime + 0.1f < TIMEMANAGER->getWorldTime() && _hit)
	{
		_hit = false;
	}
	if (_hit)
	{
		_hitRC = _rc;
		_hitRC.top = _rc.bottom - (_rc.bottom - _rc.top) * 0.9f;
		float width = (_rc.right - _rc.left);
		_hitRC.left = _rc.left - width * 0.05f;
		_hitRC.right = _rc.right + width * 0.05f;
		_rc = _hitRC;
	}
}

void Rock::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, 0, 0, _image->getWidth(), _image->getHeight());
}

void Rock::setHP(int damage, float playerX)
{
	_curHp -= damage;
	_hitTime = TIMEMANAGER->getWorldTime();
	_hit = true;
}
