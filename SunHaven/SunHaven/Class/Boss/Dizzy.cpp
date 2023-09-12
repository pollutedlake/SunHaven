#include "Stdafx.h"
#include "Dizzy.h"
#include "../../Player/Player.h"

HRESULT Dizzy::init(void)
{
	_state = EDizzyState::SLEEP;

	_wakeImg = IMAGEMANAGER->addFrameImage("DizzyWake", "Resources/Images/Boss/Dizzy/Dizzy_Wake.bmp",
		1218, 320, 7, 2, true, RGB(255, 0, 255));
	_idleImg = IMAGEMANAGER->addFrameImage("DizzyIdle", "Resources/Images/Boss/Dizzy/Dizzy_Idle.bmp",
		1218, 320, 8, 2, true, RGB(255, 0, 255));
	_spinImg = IMAGEMANAGER->addFrameImage("DizzySpin", "Resources/Images/Boss/Dizzy/Dizzy_Spin.bmp",
		1740, 320, 10, 2, true, RGB(255, 0, 255));
	_groggyImg = IMAGEMANAGER->addFrameImage("DizzyGroggy", "Resources/Images/Boss/Dizzy/Dizzy_Groggy.bmp",
		1392, 320, 8, 2, true, RGB(255, 0, 255));
	_rangeImg = IMAGEMANAGER->addFrameImage("DizzyRange", "Resources/Images/Boss/Dizzy/Dizzy_Range.bmp",
		4176, 320, 24, 2, true, RGB(255, 0, 255));

	_x = CENTER_X;
	_y = CENTER_Y - 100;

	_rcDizzy = RectMakeCenter(_x, _y, _wakeImg->getFrameWidth(), _wakeImg->getFrameHeight());

	_hpBar = new ProgressBar;
	_hpBar->init("", "ProgressBarBGW", "ProgressBarW", CENTER_X + 15, CENTER_Y + 257, 92 * 4 + 25, 14);

	_hp = 5000.0f;
	_maxHp = 5000.0f;

	_isWake = false;
	_isLeft = false;

	_worldTimeCount = GetTickCount();

	_currentFrameX = 0;
	_currentFrameY = 0;

	_bullet = new Bullet;



	return S_OK;
}

void Dizzy::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);

	_bullet->release();
	SAFE_DELETE(_bullet);

}

void Dizzy::update(void)
{
	_hpBar->update();
	_hpBar->setGauge(_hp, _maxHp);

	cout << (int)_state << endl;

	/*if (_x > _player->getPlayerPosition().x)
	{
		_isLeft = false;
	}

	else
	{
		_isLeft = true;
	}*/

	switch (_state)
	{
	case EDizzyState::SLEEP:
		if (_isWake)
		{
			_state = EDizzyState::IDLE;
		}

		break;

	case EDizzyState::IDLE:
		if (_idleImg->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;

			_state = EDizzyState::SPIN;
		}

		break;

	case EDizzyState::SPIN:
		spin();

		break;

	case EDizzyState::GROGGY:


		break;

	case EDizzyState::RANGE:


		break;

	case EDizzyState::DEATH:


		break;
	}
}

void Dizzy::render(void)
{
	draw();
	animation();

	_hpBar->render();

	char bossHpRate[128];

	sprintf_s(bossHpRate, "%d %s %d", static_cast<int>(_hp), "/", static_cast<int>(_maxHp));

	FONTMANAGER->textOut(getMemDC(), CENTER_X - 10, CENTER_Y + 230, "배달의민족 을지로체",
		20, 500, "디지", strlen("디지"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), CENTER_X - 30, CENTER_Y + 250, "배달의민족 을지로체",
		15, 400, bossHpRate, strlen(bossHpRate), RGB(255, 255, 255));

	IMAGEMANAGER->render("DizzyHpBarBorder", getMemDC(), CENTER_X - 210, CENTER_Y + 223);
}

void Dizzy::draw(void)
{
	switch (_state)
	{
	case EDizzyState::SLEEP:
		_wakeImg->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);

		break;

	case EDizzyState::IDLE:
		_idleImg->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);

		break;

	case EDizzyState::SPIN:
		_spinImg->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);

		break;

	case EDizzyState::GROGGY:


		break;

	case EDizzyState::RANGE:


		break;

	case EDizzyState::DEATH:


		break;
	}
}

void Dizzy::animation(void)
{
	if (_isWake)
	{
		if (!_isLeft)	// 오른쪽
		{
			_wakeImg->setFrameY(0);

			if (130 + _worldTimeCount <= GetTickCount())
			{
				_worldTimeCount = GetTickCount();
				_currentFrameX++;

				if (_wakeImg->getMaxFrameX() < _currentFrameX)
				{
					_currentFrameX = 0;
				}
			}
		}
	}

	if (!_isLeft)	// 오른쪽
	{
		_idleImg->setFrameY(0);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;

			if (_idleImg->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;

				_state = EDizzyState::SPIN;
			}
		}
	}

	else
	{
		_idleImg->setFrameY(1);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX--;

			if (0 > _currentFrameX)
			{
				_currentFrameX = _idleImg->getMaxFrameX();

				_state = EDizzyState::SPIN;
			}
		}
	}

	if (!_isLeft)	// 오른쪽
	{
		_spinImg->setFrameY(0);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;

			if (_spinImg->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;

				_state = EDizzyState::SPIN;
			}
		}
	}

	else
	{
		_spinImg->setFrameY(1);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX--;

			if (0 > _currentFrameX)
			{
				_currentFrameX = _spinImg->getMaxFrameX();

				_state = EDizzyState::SPIN;
			}
		}
	}
}

void Dizzy::spin(void)
{
	if (!_isLeft)
	{
		if (_currentFrameX >= 2 && _currentFrameX <= 6)
		{
			_x += cosf(getAngle(_x, _y, _player->getPlayerPosition().x, _player->getPlayerPosition().y));
			_y += -sinf(getAngle(_x, _y, _player->getPlayerPosition().x, _player->getPlayerPosition().y));
		}
	}

	else
	{
		if (_currentFrameX >= 3 && _currentFrameX <= 7)
		{
			_x += cosf(getAngle(_x, _y, _player->getPlayerPosition().x, _player->getPlayerPosition().y));
			_y += -sinf(getAngle(_x, _y, _player->getPlayerPosition().x, _player->getPlayerPosition().y));
		}
	}

}
