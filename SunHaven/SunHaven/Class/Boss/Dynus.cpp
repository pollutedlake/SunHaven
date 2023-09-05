#include "Stdafx.h"
#include "Dynus.h"
#include "../Enemy/Player_Temp.h"
//#include "../Enemy/Shadeclaw.h"
#include "../Enemy/EnemyManager.h"

HRESULT Dynus::init(void)
{
	//_state = EDynusState::BREATHE;
	_phase = EDynusPhase::FIRST;
	//_spell = EDynusSpell::SPREAD_X;

	_x = CENTER_X - 317;
	_y = 0;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_worldTimeCount = GetTickCount();
	_fireCount = 0.0f;
	_bulletCount = 0;
	_turnCount = TIMEMANAGER->getWorldTime();
	_bulletTurnCount = 3.0f;
	_beamCount = 0.0f;
	_beamFireCount = 0.0f;
	_beamTurnCount = TIMEMANAGER->getWorldTime();

	_timeCount = 100;

	//_dynusImg = IMAGEMANAGER->findImage("DynusBreathe");

	_breatheImg = IMAGEMANAGER->addImage("DynusBreathe", "Resources/Images/Boss/DynusBreathe.bmp",
		2536, 594, true, RGB(255, 0, 255));

	_breatheAni = new Animation;
	_breatheAni->init(_breatheImg->getWidth(), _breatheImg->getHeight(), 634, 297);
	_breatheAni->setDefPlayFrame(false, true);
	_breatheAni->setFPS(12);

	_spellImg = IMAGEMANAGER->addImage("DynusSpell", "Resources/Images/Boss/DynusSpell.bmp",
		3804, 3564, true, RGB(255, 0, 255));

	_spellAni = new Animation;
	_spellAni->init(_spellImg->getWidth(), _spellImg->getHeight(), 634, 297);
	_spellAni->setDefPlayFrame(false, true);
	_spellAni->setFPS(12);

	_bullet = new Bullet;
	_bullet->init("DynusOrb2", 100, 1500.0f);

	_beam = new Beam;
	_beam->init(100, 1500.0f);

	_rcDynus = RectMakeCenter(_x, _y,
		_breatheImg->getFrameWidth(), _breatheImg->getFrameHeight());

	for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			_rcPa1Start[i][j] =
				RectMakeCenter(CENTER_X - 50 + cos(DEGREE_RADIAN(i * 30)) * 400 + 15 * j,
					CENTER_Y - sin(DEGREE_RADIAN(i * 30)) * 400, 50, 50);
		}
	}

	for (int i = 0; i < PA2_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
		{
			float angle = static_cast<float>(j) / PA2_STARTPOS_NUM_2 * 360.0f;

			float xOffset = cos(DEGREE_RADIAN(angle)) * 20;
			float yOffset = sin(DEGREE_RADIAN(angle)) * 15;

			_rcPa2Start[i][j] = RectMakeCenter(CENTER_X - 50 + cos(DEGREE_RADIAN(i * 60)) * 400 + xOffset,
				CENTER_Y + sin(DEGREE_RADIAN(i * 60)) * 200 + yOffset, 50, 50);
		}
	}
	
	_rcPa3Start[0] = RectMakeCenter(CENTER_X - 500, 300, 50, 50);
	_rcPa3Start[1] = RectMakeCenter(CENTER_X + 500, 410, 50, 50);
	_rcPa3Start[2] = RectMakeCenter(CENTER_X - 500, 520, 50, 50);

	_pa1StartPosIdx = 6;
	_pa2StartPosIdx = 3;
	_pa3StartPosIdx = 2;

	_em->spawnShadeclaw();

	return S_OK;
}

HRESULT Dynus::init(const char* imageName, POINT position)
{
	//_x = position.x;
	//_y = position.y;

	//_worldTimeCount = GetTickCount();
	//_rndTimeCount = RND->getFromFloatTo(50, 150);

	//_dynusImg = IMAGEMANAGER->findImage(imageName);
	//_rcDynus = RectMakeCenter(_x, _y,
	//	_dynusImg->getFrameWidth(), _dynusImg->getFrameHeight());

	//_dynusImg = IMAGEMANAGER->addImage("DynusBreathe", "Resources/Images/Dynus/DynusBreathe.bmp",
	//	2536, 594, true, RGB(255, 0, 255));
	///*_dynusImg = IMAGEMANAGER->addImage("DynusSpell", "Resources/Images/Dynus/DynusSpell.bmp",
	//	3804, 3564, true, RGB(255, 0, 255));*/
	//_dynusAni = new Animation;
	//_dynusAni->init(_dynusImg->getWidth(), _dynusImg->getHeight(), 634, 297);
	//_dynusAni->setDefPlayFrame(false, true);
	//_dynusAni->setFPS(12);

	return S_OK;
}

void Dynus::release(void)
{
	_breatheAni->release();
	SAFE_DELETE(_breatheAni);

	_spellAni->release();
	SAFE_DELETE(_spellAni);

	_bullet->release();
	SAFE_DELETE(_bullet);

	_beam->release();
	SAFE_DELETE(_beam);

	_em->release();
	SAFE_DELETE(_em);

	/*for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();

		SAFE_DELETE(*_viEnemy);
	}*/
}

void Dynus::update(void)
{
	switch (_state)
	{
	case EDynusState::BREATHE:
		//_breatheAni->AniStart();

		break;

	case EDynusState::GRUNT:

		break;

	case EDynusState::HAIR:

		break;

	case EDynusState::LAUGHING:

		break;

	case EDynusState::SPELL:
		//_spellAni->AniStart();

		switch (_phase)
		{
		case EDynusPhase::FIRST:
			switch (_spell)
			{
			case EDynusSpell::SPREAD_X:
				bulletFire();
				//beamFire();
				if (_pa1StartPosIdx < 0)
				{
					_spell = EDynusSpell::SPREAD_ELLIPSE;
				}

				break;

			case EDynusSpell::SPREAD_ELLIPSE:
				spreadEllipse();

				if (_pa2StartPosIdx < 0)
				{
					_spell = EDynusSpell::BEAM;
				}

				break;

			case EDynusSpell::BEAM:
				beamFire();

				/*if (_pa3StartPosIdx < 0)
				{
					_spell = EDynusSpell::SPREAD_X;
				}*/

				if (_pa3StartPosIdx < 0)
				{
					_phase = EDynusPhase::SECOND;
				}

				break;
			}

			break;

		case EDynusPhase::SECOND:
			switch (_spell)
			{
			case EDynusSpell::SPAWN:
				//spawnEnemy();
				_em->spawnShadeclaw();
				_spell = EDynusSpell::SPREAD_X;

				break;

			case EDynusSpell::SPREAD_X:
				bulletFire();

				if (_pa1StartPosIdx < 0)
				{
					_spell = EDynusSpell::SPAWN;
				}

				break;
			}

			break;

		case EDynusPhase::THIRD:

			break;
		}

		break;
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		_state = EDynusState::SPELL;

		switch (_spell)
		{
		case EDynusSpell::SPREAD_X:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::SPREAD_ELLIPSE:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::BEAM:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::SPAWN:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;
		}
	}

	_breatheAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_spellAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	_bullet->update();
	_beam->update();
	/*for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}*/
}

void Dynus::render(void)
{
	draw();

	_bullet->render();
	_beam->render();
	/*for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}*/
}

void Dynus::move(void)
{

}

void Dynus::draw(void)
{
	IMAGEMANAGER->render("DynusWing", getMemDC(), _x + 210, _y + 10);
	_breatheImg->aniRender(getMemDC(), _x, _y, _breatheAni);
	_spellImg->aniRender(getMemDC(), _x, _y, _spellAni);

	if (KEYMANAGER->isToggleKey('G'))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
		{
			for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
			{
				DrawRectMake(getMemDC(), _rcPa1Start[i][j]);
			}
		}

		for (int i = 0; i < PA2_STARTPOS_NUM_1; i++)
		{
			for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
			{
				DrawRectMake(getMemDC(), _rcPa2Start[i][j]);
			}
		}

		for (int i = 0; i < PA3_STARTPOS_NUM; i++)
		{
			DrawRectMake(getMemDC(), _rcPa3Start[i]);
		}

		DrawRectMake(getMemDC(), _player->getRect());

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);
	}
}

void Dynus::bulletFire()
{
	if (_bulletCount < 3 && bulletCountFire())
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			float xOffset = j * 10.0f;

			_bullet->fire((_rcPa1Start[_pa1StartPosIdx][j].left + _rcPa1Start[_pa1StartPosIdx][j].right) / 2,
				(_rcPa1Start[_pa1StartPosIdx][j].bottom + _rcPa1Start[_pa1StartPosIdx][j].top) / 2,
				getAngle((_rcPa1Start[_pa1StartPosIdx][j].left + _rcPa1Start[_pa1StartPosIdx][j].right) / 2,
					(_rcPa1Start[_pa1StartPosIdx][j].bottom + _rcPa1Start[_pa1StartPosIdx][j].top) / 2,
					_player->getPosition().x, _player->getPosition().y) + xOffset * 0.01f, 2.0f);
		}
		
		_bulletCount++;
	}

	if (_bulletCount == 3 && turnCountFire() && _pa1StartPosIdx > -1)
	{
		_pa1StartPosIdx--;

		_bulletCount = 0;
	}	
}

void Dynus::spreadEllipse(void)
{
	if (turnCountFire())
	{
		for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
		{
			_bullet->fire((_rcPa2Start[_pa2StartPosIdx][j].left + _rcPa2Start[_pa2StartPosIdx][j].right) / 2,
				(_rcPa2Start[_pa2StartPosIdx][j].bottom + _rcPa2Start[_pa2StartPosIdx][j].top) / 2,
				DEGREE_RADIAN(j * 22.5f), 2.0f);
		}

		if (_pa2StartPosIdx > -1)
		{
			_pa2StartPosIdx--;
		}
	}
}

void Dynus::beamFire(void)
{
	float speed = 10.0f;

	if ((_pa3StartPosIdx == 0 || _pa3StartPosIdx == 2))
	{
		speed = 10.0f;
	}

	else
	{
		speed = -10.0f;
	}

	if (_beamCount < 9 && bulletCountFire())
	{
		_beam->fire((_rcPa3Start[_pa3StartPosIdx].left + _rcPa3Start[_pa3StartPosIdx].right) / 2,
			(_rcPa3Start[_pa3StartPosIdx].bottom + _rcPa3Start[_pa3StartPosIdx].top) / 2, speed);

		/*_beam->fire((_rcPa3Start[0].left + _rcPa3Start[0].right) / 2,
			(_rcPa3Start[0].bottom + _rcPa3Start[0].top) / 2);*/

		_beamCount++;
	}

	if (_beamCount == 9 && turnCountFire() && _pa3StartPosIdx > 0)
	{
		_pa3StartPosIdx--;

		_beamCount = 0;
	}
}

//void Dynus::spawnEnemy(void)
//{
//	for (int i = 0; i < 2; i++)
//	{
//		Enemy* shadeclaw;
//		shadeclaw = new Shadeclaw;
//		shadeclaw->init("Shadeclow_Idle", PointMake(500 + i * 100, 300), 200, 200);
//		_vEnemy.push_back(shadeclaw);
//
//		RECT rcTemp1;
//
//		if (IntersectRect(&rcTemp1, &shadeclaw->getRcDetect(), &_player->getRect()))
//		{
//			/*shadeclaw->setX(shadeclaw->getPosition().x + cosf(getAngle((shadeclaw->getRect().left + shadeclaw->getRect().right) / 2,
//				(shadeclaw->getRect().bottom + shadeclaw->getRect().top) / 2,
//				_player->getPosition().x,
//				_player->getPosition().y)) * 2.0f);
//
//			shadeclaw->setY(shadeclaw->getPosition().y - sinf(getAngle((shadeclaw->getRect().left + shadeclaw->getRect().right) / 2,
//				(shadeclaw->getRect().bottom + shadeclaw->getRect().top) / 2,
//				_player->getPosition().x,
//				_player->getPosition().y)) * 2.0f);*/
//		}
//	}
//
//}

bool Dynus::bulletCountFire(void)
{
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = 0.3f;

		return true;
	}

	return false;
}

bool Dynus::turnCountFire(void)
{
	if (_bulletTurnCount + _turnCount <= TIMEMANAGER->getWorldTime())
	{
		_turnCount = TIMEMANAGER->getWorldTime();
		_bulletTurnCount = 3.0f;

		return true;
	}

	return false;
}

bool Dynus::beamCountFire(void)
{
	if (_beamCount + _beamTurnCount <= TIMEMANAGER->getWorldTime())
	{
		_beamTurnCount = TIMEMANAGER->getWorldTime();
		_beamCount = 0.1f;

		return true;
	}

	return false;
}