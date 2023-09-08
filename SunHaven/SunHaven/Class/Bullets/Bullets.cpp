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
	_sourX = 0;
	_sourX2 = 0;

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

void Beam::fire(float x, float y, float speed, int index)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.pImg = new GPImage;
	bullet.pImg->init("Resources/Images/Boss/DynusBeam.png", 0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);

	bullet.pImg2 = new GPImage;
	bullet.pImg2->init("Resources/Images/Boss/DynusBeam.png", 0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);

	//_sourX = bullet.pImg->getWidth();
	/*bullet.img = new GImage;
	bullet.img->init("Resources/Images/Boss/DynusBeam.bmp",
		144, 42,
		true, RGB(255, 0, 255));*/
	_index = index;
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		0, bullet.pImg->getHeight());

	

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
		DrawRectMake(getMemDC(), _viBullet->rc);

		//_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		//_viBullet->img->loopRender(getMemDC(), &_viBullet->rc, _viBullet->rc.right, _viBullet->rc.top);

		/*_viBullet->pImg->GPFrameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 1,
			_viBullet->pImg->getFrameX(), _viBullet->pImg->getFrameY(),
			InterpolationModeNearestNeighbor, 0);*/

		if (_index == 0 || _index == 2)
		{
			_viBullet->pImg->GPRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 1,
				_sourX, 0, _viBullet->pImg->getWidth() - _sourX, _viBullet->pImg->getHeight(),
				InterpolationModeNearestNeighbor, 0);
		}

		else
		{
			_viBullet->pImg2->GPRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 1,
				_sourX2, 0, _sourX2 + _viBullet->pImg2->getWidth(), _viBullet->pImg2->getHeight(),
				InterpolationModeNearestNeighbor, 0);
		}

		/*if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;

			if (_viBullet->pImg->getMaxFrameX() < _currentFrameX)
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
		if (_index == 0 || _index == 2)
		{
			if ((_viBullet->rc.right - _viBullet->rc.left) < 1280)
			{
				_viBullet->rc.right += _viBullet->speed;
			}

			else
			{

				_viBullet->rc.left += _viBullet->speed;
				_viBullet->rc.right += _viBullet->speed;

				//_viBullet->rc.right = _viBullet->rc.left + 1280;

				//_viBullet->x += _viBullet->speed;
			}

			_sourX = _viBullet->pImg->getWidth() - (_viBullet->rc.right - _viBullet->rc.left);
		}

		else
		{
			if ((_viBullet->rc.right - _viBullet->rc.left) < 1280)
			{
				_viBullet->rc.left -= _viBullet->speed;
			}

			else
			{

				_viBullet->rc.left -= _viBullet->speed;
				_viBullet->rc.right -= _viBullet->speed;

				//_viBullet->rc.right = _viBullet->rc.left + 1280;

				//_viBullet->x += _viBullet->speed;
			}

			_sourX2 = 0 - (_viBullet->rc.left + _viBullet->rc.right);
		}

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
