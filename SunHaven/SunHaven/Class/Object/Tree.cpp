#include "Stdafx.h"
#include "Tree.h"

HRESULT Tree::init(void)
{
	return S_OK;
}

HRESULT Tree::init(LivingObjectType type, POINT tilePos)
{
	_type = type;
	char str[64];
	wsprintf(str, "Object%d", (int)type + 1);
	_image = IMAGEMANAGER->findImage(str);
	_tilePos = tilePos;
	_halfTrans = false;
	switch (_type)
	{
	case TREE1:
		_offsetX = -3;
		_offsetY = -48;
		_maxHp = 100;
		_dropItemList.push("4-0");
		break;
	case TREE2:
		_offsetX = 3;
		_offsetY = -42;
		_maxHp = 120;
		_dropItemList.push("4-2");
		break;
	}
	_curHp = _maxHp;
	_hpBar = new ProgressBar;
	_hpBar->init("ObjectHpBarTop", "", "ObjectHpBarFill", NULL, NULL, 36, 7);
	_hpBarOffsetX = 1;
	_hpBarOffsetY = 30;
	_beforeHitRC = {NULL, NULL, NULL, NULL};
	_hitRC = {NULL, NULL, NULL, NULL};
	_hit = false;
	return S_OK;
}

void Tree::update(void)
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

void Tree::render(void)
{
	if(_halfTrans)
	{
		_image->alphaRender(getMemDC(), _rc.left, _rc.top, (_rc.right - _rc.left), (_rc.bottom - _rc.top), 0, 0, _image->getWidth(), _image->getHeight(), 128);
	}
	else
	{
		_image->render(getMemDC(), _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, 0, 0, _image->getWidth(), _image->getHeight());
	}
}

void Tree::release(void)
{
	
}

void Tree::setHP(int damage)
{
	_curHp -= damage;
	_hitTime = TIMEMANAGER->getWorldTime();
	_hit = true;
	if (_curHp <= 0 && _hpBarOffsetX == 1)
	{
		_maxHp /= 2;
		_curHp = _maxHp;
		_image = IMAGEMANAGER->findImage("Stump");
		_offsetX = 0;
		_offsetY = 0;
		_hpBarOffsetX = 5;
		_hpBarOffsetY = 36;
		_rc = RectMake(_cx + (_offsetX - _image->getWidth() / 2) * 1.5f, _cy + (_offsetY - _image->getHeight() / 2) * 1.5f, _image->getWidth() * 1.5, _image->getHeight() * 1.5);
	}
}
