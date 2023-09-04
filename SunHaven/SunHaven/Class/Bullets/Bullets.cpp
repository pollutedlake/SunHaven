#include "stdafx.h"
#include "Bullets.h"
//#include "Rocket.h"

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	_isLeft = false;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_worldTimeCount = GetTickCount();

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

void Beam::fire(float x, float y, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	/*bullet.pImg = new GPImage;
	bullet.pImg->init("Resources/Images/Boss/DynusBeam.png", bullet.rc.left, bullet.rc.top,
		9, 1,
		false, NULL, RotateNoneFlipNone);*/

	bullet.img = new GImage;
	bullet.img->init("Resources/Images/Boss/DynusBeam.bmp", 0.0f, 0.0f,
		216, 42,
		9, 1,
		true, RGB(255, 0, 255));

	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	bullet.fire = true;
	_vBullet.push_back(bullet);

	/*if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);*/
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//DrawRectMake(getMemDC(), _viBullet->rc);

		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		/*_viBullet->pImg->GPFrameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 1,
			_viBullet->pImg->getFrameX(), _viBullet->pImg->getFrameY(),
			InterpolationModeNearestNeighbor, 0);*/

		/*if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;

			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;
			}
		}*/

		//if (!_isLeft)	// 오른쪽
		//{
		//	bullet.pImg->setFrameY(0);

		//	if (130 + _worldTimeCount <= GetTickCount())
		//	{
		//		_worldTimeCount = GetTickCount();
		//		_currentFrameX++;

		//		if (bullet.pImg->getMaxFrameX() < _currentFrameX)
		//		{
		//			_currentFrameX = 0;
		//		}
		//	}
		//}

		//else	// 왼쪽
		//{
		//	bullet.pImg->setFrameY(1);

		//	if (130 + _worldTimeCount <= GetTickCount())
		//	{
		//		_worldTimeCount = GetTickCount();
		//		_currentFrameX--;

		//		if (0 > _currentFrameX)
		//		{
		//			_currentFrameX = bullet.pImg->getMaxFrameX();
		//		}
		//	}
		//}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		//_viBullet->rc.right += _viBullet->speed;
		_viBullet->x += _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img); // findimage를 사용하면 이미지 원본이 삭제되어 터진다
			_viBullet = _vBullet.erase(_viBullet);
		}

		else
		{
			++_viBullet;
		}
	}
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
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//DrawRectMake(getMemDC(), _viBullet->rc);

		/*_viBullet->pImg->GPFrameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 1,
			_viBullet->pImg->getFrameX(), _viBullet->pImg->getFrameY(),
			InterpolationModeNearestNeighbor, 0);*/

		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

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

void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			// SAFE_DELETE(_viBullet->img); -> findimage를 사용해서 이미지 원본이 삭제되어 터진다
			_viBullet = _vBullet.erase(_viBullet);
		}

		else
		{
			++_viBullet;
		}
	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
