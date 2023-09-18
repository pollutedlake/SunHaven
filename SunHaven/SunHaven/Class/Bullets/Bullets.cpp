#include "stdafx.h"
#include "Bullets.h"

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
	_sourX3 = 0;

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

	bullet.pImg = new GPImage;
	bullet.pImg->init("Resources/Images/Boss/DynusBeam.png", 0, 0,
		1, 1,
		false, NULL, RotateNoneFlipNone);
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		0, bullet.pImg->getHeight());
	
	bullet.fire = true;
	_vBullet.push_back(bullet);
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->pImg->GPRender(getMemDC(), CAMERA->worldToCameraX(_viBullet->rc.left),
			CAMERA->worldToCameraY(_viBullet->rc.top), 1, 1,
			_sourX, 0, _viBullet->pImg->getWidth() - _sourX, _viBullet->pImg->getHeight(),
			InterpolationModeNearestNeighbor, 0);
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->speed > 0)
		{
			if ((_viBullet->rc.right - _viBullet->rc.left) < 1280)
			{
				_viBullet->rc.right += _viBullet->speed;
			}

			else
			{
				_viBullet->rc.left += _viBullet->speed;
				_viBullet->rc.right += _viBullet->speed;
			}

			_sourX = _viBullet->pImg->getWidth() - (_viBullet->rc.right - _viBullet->rc.left);
		}

		if (_viBullet->speed < 0)
		{
			if ((_viBullet->rc.right - _viBullet->rc.left) < 1280)
			{
				_viBullet->rc.left += _viBullet->speed;
			}

			else
			{

				_viBullet->rc.left += _viBullet->speed;
				_viBullet->rc.right += _viBullet->speed;
			}

			_sourX = _viBullet->pImg->getWidth() - (_viBullet->rc.right - _viBullet->rc.left);
		}

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
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

	_spawnTime = 1.0f;
	_spawnWorldTime = TIMEMANAGER->getWorldTime();
	_isSpawn = false;

	return S_OK;
}

void Bullet::release(void)
{

	_vBullet.clear();
}

void Bullet::update(void)
{
	if (spawningTime())
	{
		_isSpawn = true;
	}

	if (_isSpawn)
	{
		move();
	}
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

	bullet.pImg = IMAGEMANAGER->findGPImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.pImg->getFrameWidth(), bullet.pImg->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->pImg->GPFrameRender(getMemDC(), CAMERA->worldToCameraX(_viBullet->rc.left), CAMERA->worldToCameraY(_viBullet->rc.top), 1.5, 1.5,
			_viBullet->pImg->getFrameX(), _viBullet->pImg->getFrameY(),
			InterpolationModeNearestNeighbor, 0);
	}
}

void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->pImg->getFrameWidth(), _viBullet->pImg->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}

		else
		{
			++_viBullet;
		}
	}
}

bool Bullet::spawningTime(void)
{
	if (_spawnTime + _spawnWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_spawnWorldTime = TIMEMANAGER->getWorldTime();
		_spawnTime = 1.0f;

		return true;
	}

	return false;
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT Meteor::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Meteor::release(void)
{
	_vBullet.clear();
}

void Meteor::update(void)
{
	move();
}

void Meteor::render(void)
{
	draw();
}

void Meteor::fire(float x, float y, float angle, float speed)
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

void Meteor::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), 
			CAMERA->worldToCameraX(_viBullet->x), CAMERA->worldToCameraY(_viBullet->y));

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

void Meteor::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}

		else
		{
			++_viBullet;
		}
	}
}

void Meteor::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT Gems::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Gems::release(void)
{
	_vBullet.clear();
}

void Gems::update(void)
{
	move();
}

void Gems::render(void)
{
	draw();
}

void Gems::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.speed = speed;

	char gemImg[128];
	int rndGemImg = RND->getInt(GEM_TYPE);
	wsprintf(gemImg, "Gem%d", rndGemImg);

	bullet.img = IMAGEMANAGER->findImage(gemImg);
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());
	bullet.fire = true;
	_vBullet.push_back(bullet);
}

void Gems::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), CAMERA->worldToCameraX(_viBullet->x), 
			CAMERA->worldToCameraY(_viBullet->y));
	}
}

void Gems::move(void)
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
			_viBullet = _vBullet.erase(_viBullet);
		}

		else
		{
			++_viBullet;
		}
	}
}

void Gems::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}


//===================================================//


HRESULT Fireball::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	


	return S_OK;
}

void Fireball::release(void)
{
	for (_viBullet = _vBullet.begin();
		_viBullet != _vBullet.end();
		++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Fireball::update(float x, float y)
{
	move(x, y);
}

void Fireball::render(void)
{
	draw();
}

void Fireball::fire(float x, float y, bool isLeft)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;

	bullet.img->init("Resources/Images/Player/Fireball.bmp",
		288, 40, 6, 2, true, RGB(255, 0, 255));
	bullet.speed = 10.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.isUpDown = false;
	bullet.isLeft = isLeft;

	_isUpDown = false;

	if (bullet.isLeft)
	{
		bullet.img->setFrameX(bullet.img->getMaxFrameX());
		bullet.img->setFrameY(1);
	}
	else 
	{
		bullet.img->setFrameX(0);
		bullet.img->setFrameY(0);
	}
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Fireball::fireUpDown(float x, float y, bool isUp)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;

	bullet.img->init("Resources/Images/Player/FireballUpDown.bmp",
		40, 288, 2, 6, true, RGB(255, 0, 255));
	bullet.speed = 10.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.isUp = isUp;

	bullet.isUpDown = true;

	if (bullet.isUp)
	{
		bullet.img->setFrameX(0);
		bullet.img->setFrameY(0);
	}
	else
	{
		bullet.img->setFrameX(1);
		bullet.img->setFrameY(bullet.img->getMaxFrameY());
	}
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Fireball::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top, _viBullet->img->getFrameX(),
			_viBullet->img->getFrameY());
		_viBullet->count++;


		if (_viBullet->count % 4 == 0)
		{
			if (_viBullet->isUpDown)
			{
				if (_viBullet->isUp)
				{
					_viBullet->img->setFrameY(_viBullet->img->getFrameY() + 1);

					if (_viBullet->img->getFrameY() >= _viBullet->img->getMaxFrameY())
					{
						_viBullet->img->setFrameY(0);
					}

					_viBullet->count = 0;
				}
				else
				{
					_viBullet->img->setFrameY(_viBullet->img->getFrameY() - 1);

					if (_viBullet->img->getFrameY() <= 0)
					{
						_viBullet->img->setFrameY(_viBullet->img->getMaxFrameY());
					}

					_viBullet->count = 0;
				}
			}
			else
			{
				if (_viBullet->isLeft)
				{
					_viBullet->img->setFrameX(_viBullet->img->getFrameX() - 1);

					if (_viBullet->img->getFrameX() <= 0)
					{
						_viBullet->img->setFrameX(_viBullet->img->getMaxFrameX());
					}

					_viBullet->count = 0;
				}
				else
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
	}
}

void Fireball::move(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->isUpDown)
		{
			if (_viBullet->isUp) _viBullet->y -= _viBullet->speed;
			else _viBullet->y += _viBullet->speed;
		}
		else
		{
			if (_viBullet->isLeft) _viBullet->x -= _viBullet->speed;
			else _viBullet->x += _viBullet->speed;
		}

		_viBullet->rc =
			RectMakeCenter(WINSIZE_X / 2 - (x - _viBullet->x),
				WINSIZE_Y / 2 - (y - _viBullet->y),
				_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void Fireball::RemoveBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT EnemyFireBall::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void EnemyFireBall::release(void)
{
	_vBullet.clear();
}

void EnemyFireBall::update(void)
{
	move();
}

void EnemyFireBall::render(void)
{
	draw();
}

void EnemyFireBall::fire(float x, float y, float angle, float speed)
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

void EnemyFireBall::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), CAMERA->worldToCameraX(_viBullet->x - _viBullet->img->getFrameWidth() / 2),
			CAMERA->worldToCameraY(_viBullet->y - _viBullet->img->getFrameHeight() / 2));

		_viBullet->img->setFrameY(0);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;
			if (_viBullet->img->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;
			}
		}
	}
}

void EnemyFireBall::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}

		else
		{
			++_viBullet;
		}
	}
}

void EnemyFireBall::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
