#include "stdafx.h"
#include "Bullets.h"
//#include "Rocket.h"

//HRESULT Bullets::init(int bulletMax, float range)
//{
//	
//
//	return S_OK;
//}
//
//void Bullets::release(void)
//{
//}
//
//void Bullets::update(void)
//{
//	move();
//}
//
//void Bullets::render(void)
//{
//	draw();
//}
//
//void Bullets::fire(float x, float y)
//{
//}
//
//void Bullets::draw(void)
//{
//}
//
//void Bullets::move(void)
//{
//}

//HRESULT GuidedMissile::init(int bulletMax, float range)
//{
//	_range = range;
//	_bulletMax = bulletMax;
//
//	return S_OK;
//}
//
//void GuidedMissile::release(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		SAFE_DELETE(_viBullet->img);
//	}
//
//	_vBullet.clear();
//}
//
//void GuidedMissile::update(void)
//{
//	move();
//}
//
//void GuidedMissile::render(void)
//{
//	draw();
//}
//
//void GuidedMissile::fire(float x, float y)
//{
//	if (_bulletMax <= _vBullet.size()) return;
//
//	tagBullet bullet;
//	ZeroMemory(&bullet, sizeof(tagBullet));
//
//	bullet.img = new GImage;
//	bullet.img->init("Resource/Images/Object/Missile.bmp", 0.0f, 0.0f,
//		416, 64,
//		13, 1,
//		true, RGB(255, 0, 255));
//	bullet.speed = 5.0f;
//	bullet.x = bullet.fireX = x;
//	bullet.y = bullet.fireY = y;
//	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
//		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
//	bullet.fire = true;
//	bullet.angle = DEGREE_RADIAN(45.0f);
//	_vBullet.push_back(bullet);
//}
//
//void GuidedMissile::draw(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
//
//		_viBullet->count++;
//
//		if (_viBullet->count % 5 == 0)
//		{
//			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
//
//			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
//			{
//				_viBullet->img->setFrameX(0);
//			}
//
//			_viBullet->count = 0;
//		}
//	}
//}
//
//void GuidedMissile::move(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (_viBullet->fire)
//		{
//			
//				//float distance = MY_UTIL::getDistance(_viBullet->x, _viBullet->y, enemy->_x, enemy->_y);
//			
//
//			_viBullet->x += _viBullet->speed;
//			_viBullet->y += _viBullet->speed;
//
//			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
//				_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
//		}
//	}
//}

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void Beam::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Beam::update(void)
{
	move();
}

void Beam::render(void)
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	//tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new GImage;
	bullet.img->init("Resource/Images/Effect/Beam.bmp", 0.0f, 0.0f,
		412, 801,
		4, 1,
		true, RGB(255, 0, 255));
	bullet.speed = 0.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	bullet.fire = true;
	bullet.angle = DEGREE_RADIAN(45.0f);
	_vBullet.push_back(bullet);
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//DrawRectMake(getMemDC(), _viBullet->rc);
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	
}

HRESULT Bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Bullet::release(void)
{

	_vBullet.clear();
}

void Bullet::update(void)
{
	move();
}

void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{


		_viBullet->pImg->GPFrameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 1,
			IMAGEMANAGER->findGPImage("DynusOrb")->getFrameX(), IMAGEMANAGER->findGPImage("DynusOrb")->getFrameY(),
			InterpolationModeNearestNeighbor, 0);
	}
}

void Bullet::move(void)
{
	//for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	//{
	//	_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
	//	_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

	//	_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
	//		_viBullet->img->getWidth(), _viBullet->img->getHeight());

	//	if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
	//		_viBullet->x, _viBullet->y))
	//	{
	//		// SAFE_DELETE(_viBullet->img); -> findimage를 사용해서 이미지 원본이 삭제되어 터진다
	//		_viBullet = _vBullet.erase(_viBullet);
	//	}

	//	else
	//	{
	//		++_viBullet;
	//	}
	//}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
