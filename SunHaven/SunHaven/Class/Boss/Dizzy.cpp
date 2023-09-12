#include "Stdafx.h"
#include "Dizzy.h"
#include "../../Player/Player.h"

HRESULT Dizzy::init(void)
{
	_state = EDizzyState::SLEEP;

	_wakeImg = IMAGEMANAGER->addFrameImage("DizzyWake", "Resources/Images/Boss/Dizzy/Dizzy_Wake.bmp",
		1218, 160, 7, 1, true, RGB(255, 0, 255));
	_idleImg = IMAGEMANAGER->addFrameImage("DizzyIdle", "Resources/Images/Boss/Dizzy/Dizzy_Idle.bmp",
		1218, 160, 8, 1, true, RGB(255, 0, 255));
	_spinImg = IMAGEMANAGER->addFrameImage("DizzySpin", "Resources/Images/Boss/Dizzy/Dizzy_Spin.bmp",
		4872, 160, 28, 1, true, RGB(255, 0, 255));
	_rangeImg = IMAGEMANAGER->addFrameImage("DizzyRange", "Resources/Images/Boss/Dizzy/Dizzy_Range.bmp",
		4176, 160, 24, 1, true, RGB(255, 0, 255));

	_wakeAni = new Animation;
	_wakeAni->init(_wakeImg->getFrameWidth(), _wakeImg->getFrameHeight(), 174, 160);
	_wakeAni->setDefPlayFrame(false, true);
	_wakeAni->setFPS(12);

	_idleAni = new Animation;
	_idleAni->init(_idleImg->getFrameWidth(), _idleImg->getFrameHeight(), 174, 160);
	_idleAni->setDefPlayFrame(false, true);
	_idleAni->setFPS(12);

	_spinAni = new Animation;
	_spinAni->init(_spinImg->getFrameWidth(), _spinImg->getFrameHeight(), 174, 160);
	_spinAni->setDefPlayFrame(false, true);
	_spinAni->setFPS(12);

	_rangeAni = new Animation;
	_rangeAni->init(_rangeImg->getFrameWidth(), _rangeImg->getFrameHeight(), 174, 160);
	_rangeAni->setDefPlayFrame(false, true);
	_rangeAni->setFPS(12);

	_curImg = _wakeImg;
	_curAni = _wakeAni;
	//_curAni->AniStart();

	_x = CENTER_X;
	_y = CENTER_Y - 100;

	_rcDizzy = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());

	_hpBar = new ProgressBar;
	_hpBar->init("", "ProgressBarBGW", "ProgressBarW", CENTER_X + 15, CENTER_Y + 257, 92 * 4 + 25, 14);

	_hp = 5000.0f;
	_maxHp = 5000.0f;

	_isWake = false;
	_worldTimeCount = GetTickCount();

	//_bullet = new Bullet;

	return S_OK;
}

void Dizzy::release(void)
{
	_curAni->release();
	SAFE_DELETE(_curAni);

	_wakeAni->release();
	SAFE_DELETE(_wakeAni);

	_idleAni->release();
	SAFE_DELETE(_idleAni);

	_spinAni->release();
	SAFE_DELETE(_spinAni);

	_rangeAni->release();
	SAFE_DELETE(_rangeAni);

	_hpBar->release();
	SAFE_DELETE(_hpBar);

	/*_bullet->release();
	SAFE_DELETE(_bullet);*/

}

void Dizzy::update(void)
{
	_hpBar->update();
	_hpBar->setGauge(_hp, _maxHp);

	_rcDizzy = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		cout << "isWake" << endl;

		_isWake = true;
	}

	cout << "현재 State: " << (int)_state << endl;

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
			_state = EDizzyState::WAKE;
		}

		break;

	case EDizzyState::WAKE:
			_curAni->setPlayFrame(0, _curImg->getMaxFrameX(), false, false);
			_curAni->AniStart();

			if (_curAni->getNowPlayIdx() >= 6)
			{
				_state = EDizzyState::IDLE;
			}

		break;

	case EDizzyState::IDLE:
			//_state = EDizzyState::SPIN;

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

	_curImg->aniRender(getMemDC(), _x, _y, _curAni);

	
}

void Dizzy::animation(void)
{
	
}

void Dizzy::spin(void)
{
	_x += cosf(getAngle(_x, _y, _player->getPlayerPosition().x, _player->getPlayerPosition().y)) * 2.0f;
	_y += -sinf(getAngle(_x, _y, _player->getPlayerPosition().x, _player->getPlayerPosition().y)) * 2.0f;
}
