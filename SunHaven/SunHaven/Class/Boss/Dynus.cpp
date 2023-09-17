#include "Stdafx.h"
#include "Dynus.h"
#include "../../Player/Player.h"
#include "../Enemy/EnemyManager.h"

HRESULT Dynus::init(void)
{
	_phase = EDynusPhase::FIRST;

	_hp = 10000.0f;
	_maxHp = 10000.0f;

	_hpBar = new ProgressBar;
	_hpBar->init("", "ProgressBarBGW", "ProgressBarW", CENTER_X + 15, CENTER_Y + 257, 92 * 4 + 25, 14);

	_x = CENTER_X - 317;
	_y = 0;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_worldTimeCount = GetTickCount();
	_fireCount = 0.0f;
	_bulletCount = 0;
	_turnCount1 = TIMEMANAGER->getWorldTime();
	_turnCount2 = TIMEMANAGER->getWorldTime();
	_turnCount3 = TIMEMANAGER->getWorldTime();
	_bulletTurnCount1 = 2.0f;
	_bulletTurnCount2 = 2.0f;
	_bulletTurnCount3 = 2.0f;
	_beamCount = 0.0f;
	_beamFireCount = 0.0f;
	_beamTurnCount = TIMEMANAGER->getWorldTime();
	_spawnAtferTime = 0.0f;
	_spawnWorldTime = TIMEMANAGER->getWorldTime();

	_hpTime = 1.0f;
	_hpTurnCount = TIMEMANAGER->getWorldTime();

	_timeCount = 100;

	_breatheImg = IMAGEMANAGER->addFrameImage("DynusBreathe", "Resources/Images/Boss/DynusBreathe.bmp",
		2536, 594, 4, 2, true, RGB(255, 0, 255));

	_breatheAni = new Animation;
	_breatheAni->init(_breatheImg->getWidth(), _breatheImg->getHeight(), 634, 297);
	_breatheAni->setDefPlayFrame(false, true);
	_breatheAni->setFPS(12);

	_spellImg = IMAGEMANAGER->addFrameImage("DynusSpell", "Resources/Images/Boss/DynusSpell.bmp",
		3804, 3564, 6, 12, true, RGB(255, 0, 255));

	_spellAni = new Animation;
	_spellAni->init(_spellImg->getWidth(), _spellImg->getHeight(), 634, 297);
	_spellAni->setDefPlayFrame(false, true);
	_spellAni->setFPS(20);
	
	_gruntImg = IMAGEMANAGER->addFrameImage("DynusGrunt", "Resources/Images/Boss/DynusGrunt.bmp",
		5072, 594, 8, 2, true, RGB(255, 0, 255));

	_gruntAni = new Animation;
	_gruntAni->init(_gruntImg->getWidth(), _gruntImg->getHeight(), 634, 297);
	_gruntAni->setDefPlayFrame(false, true);
	_gruntAni->setFPS(10);

	_curImg = _breatheImg;
	_curAni = _breatheAni;
	_curAni->AniStart();

	_bullet = new Bullet;
	_bullet->init("DynusOrb", 100, 1500.0f);

	_spawnBulletTime = 1.0f;
	_spawnBulletWorldTime = TIMEMANAGER->getWorldTime();

	_beam = new Beam;
	_beam->init(50, 1500.0f);

	_rcDynus = RectMakeCenter(_x + 300, _y + 120,
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

	_platformMove = 0.0f;

	_isPlatform = false;
	_isMoveCenter = false;
	_isPlatformUp = false;

	for (int i = 0; i < 7; i++)
	{
		_rcPlatform[i] = { NULL, NULL, NULL, NULL };
	}

	_rcGuardMine1 = { NULL, NULL, NULL, NULL };
	_rcGuardMine2 = { NULL, NULL, NULL, NULL };

	_isGM1Remove = false;
	_isGM2Remove = false;

	_pa1StartPosIdx = 6;
	_pa2StartPosIdx = 3;
	_pa3StartPosIdx = 2;

	_rndPattern = 0;

	_isSpawn = false;
	_isSpawnEnemy = false;
	_isSpawnAfter = false;

	_hpRegenCount = 0;

	_p1PotalSize = 0.0f;
	_p2PotalSize = 0.0f;

	_bgAlpha = 255.0f;

	_afterSpawnCount = 0;
	_aftetKCount = 0;

	_isDie = false;

	return S_OK;
}

void Dynus::release(void)
{
	_breatheAni->release();
	SAFE_DELETE(_breatheAni);

	_spellAni->release();
	SAFE_DELETE(_spellAni);

	_curAni->release();
	SAFE_DELETE(_curAni);

	_bullet->release();
	SAFE_DELETE(_bullet);

	_beam->release();
	SAFE_DELETE(_beam);

	_em->release();
	SAFE_DELETE(_em);

	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void Dynus::update(void)
{
	if (_hp <= 7000 && _hp > 4000)
	{
		_phase = EDynusPhase::SECOND;
	}

	else if (_hp <= 4000 && _hp > 3000)
	{
		_isStar = true;
	}

	else if (_hp <= 1000)
	{
		_isDie = true;

		_phase = EDynusPhase::DEATH;

		_curAni->AniStop();
		_curImg = _gruntImg;
		_curAni = _gruntAni;
		_curAni->setPlayFrame(0, 15, false, false);
		_curAni->AniStart();
	}

	if (_isStar)
	{
		_phase = EDynusPhase::STAR;

		_hpRegenCount++;
		if (_hpRegenCount > 50)
		{
			if (_hp <= 9990)
			{
				_hp += 10;
			}

			_hpRegenCount = 0;
		}
	}

	if (_isGM1Remove && _isGM2Remove)
	{
		_bgAlpha += 9.0f;

		if (_bgAlpha > 255)
		{
			_bgAlpha = 255.0f;
		}

		_phase = EDynusPhase::THIRD;
		_thirdP = EThirdPhase::RANDOM_PATTERN;
	}

	if (_isMoveCenter)
	{
		POINT position;
		position.x = CENTER_X;
		position.y = CENTER_Y + 50;
		_player->setPlayerPosition(position);
	}

	if (!_isDie)
	{
		_hpBar->update();
		_hpBar->setGauge(_hp, _maxHp);
		_bullet->update();
		_beam->update();
		collision();
	}
	
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	switch (_state)
	{
	case EDynusState::BREATHE:
			
		break;

	case EDynusState::SPELL:
		
		switch (_phase)
		{
		case EDynusPhase::FIRST:
			switch (_firstP)
			{
			case EFirstPhase::SPREAD_X:
				//if (_curAni->getNowPlayIdx() == 20)
				//{
				//	// SD: 캐스팅
				//}
				_pa2StartPosIdx = 3;
				_pa3StartPosIdx = 2;
				if (spawningTime())
				{
					_isSpawn = true;
				}

				if (_isSpawn)
				{
					bulletFire();
				}

				if (_pa1StartPosIdx < 0)
				{
						_firstP = EFirstPhase::SPREAD_ELLIPSE;
						_curAni->AniStop();
						_curImg = _spellImg;
						_curAni = _spellAni;
						_curAni->setPlayFrame(0, 69, false, false);
						_curAni->AniStart();
						_pa1StartPosIdx = 6;

						_pa2StartPosIdx = 3;
						_bulletCount = 0;
				}

				break;

			case EFirstPhase::SPREAD_ELLIPSE:
				//if (_curAni->getNowPlayIdx() == 20)
				//{
				//	// SD: 캐스팅
				//}

				spreadEllipse();
				_bulletCount = 0;
				_pa1StartPosIdx = 6;
				_pa3StartPosIdx = 2;
				if (_pa2StartPosIdx < 0)
				{
					_firstP = EFirstPhase::BEAM1;
					_curAni->AniStop();
					_curImg = _spellImg;
					_curAni = _spellAni;
					_curAni->setPlayFrame(0, 69, false, false);
					_curAni->AniStart();
		
					_pa1StartPosIdx = 6;
					_pa3StartPosIdx = 2;
					_bulletCount = 0;

				}

				break;

			case EFirstPhase::BEAM1:
				//if (_curAni->getNowPlayIdx() == 20)
				//{
				//	// SD: 캐스팅
				//}
				_bulletCount = 0;
				_pa1StartPosIdx = 6;
				_pa2StartPosIdx = 3;
				beamFire();

				if (_pa3StartPosIdx < 0)
				{
					_firstP = EFirstPhase::BEAM2;
					/*_curAni->AniStop();
					_curImg = _spellImg;
					_curAni = _spellAni;
					_curAni->setPlayFrame(0, 69, false, false);
					_curAni->AniStart();*/
					_pa1StartPosIdx = 6;

					_pa3StartPosIdx = 2;
					_bulletCount = 0;

				}

				break;

			case EFirstPhase::BEAM2:
				//if (_curAni->getNowPlayIdx() == 20)
				//{
				//	// SD: 캐스팅
				//}
				_bulletCount = 0;
				_pa1StartPosIdx = 6;
				_pa2StartPosIdx = 3;
				beamFire();

				if (_pa3StartPosIdx < 0)
				{
					_firstP = EFirstPhase::SPREAD_X;
					_curAni->AniStop();
					_curImg = _spellImg;
					_curAni = _spellAni;
					_curAni->setPlayFrame(0, 69, false, false);
					_curAni->AniStart();
					_pa1StartPosIdx = 6;
					_bulletCount = 0;

				}

				break;
			}

			break;

		case EDynusPhase::SECOND:
			switch (_secondP)
			{
			case ESecondPhase::SPAWN:
				//if (_curAni->getNowPlayIdx() == 20)
				//{
				//	// SD: 캐스팅
				//}
				_bulletCount = 0;
				_pa1StartPosIdx = 6;

				if (!_isSpawnEnemy)
				{
					int rndSpawn = RND->getInt(2);

					if (rndSpawn == 0)
					{
						_em->spawnShadeclaw();
					}
					
					else
					{
						_em->spawnRootwalker();
					}

					_isSpawnEnemy = true;
				}

				else
				{
					_afterSpawnCount++;

					if (_afterSpawnCount > 400)
					{
						_pa1StartPosIdx = 6;
						_bulletCount = 0;
						_secondP = ESecondPhase::SPREAD_X;
						_curAni->AniStop();
						_curImg = _spellImg;
						_curAni = _spellAni;
						_curAni->setPlayFrame(0, 69, false, false);
						_curAni->AniStart();
						_afterSpawnCount = 0;
					}
				}
				
				break;

			case ESecondPhase::SPREAD_X:
				//if (_curAni->getNowPlayIdx() == 20)
				//{
				//	// SD: 캐스팅
				//}
				bulletFire();
				_pa2StartPosIdx = 3;
				_pa3StartPosIdx = 2;
				_isSpawnEnemy = false;

				if (_pa1StartPosIdx < 0)
				{
					_isSpawn = false;
					_secondP = ESecondPhase::SPAWN;
					_curAni->AniStop();
					_curImg = _spellImg;
					_curAni = _spellAni;
					_curAni->setPlayFrame(0, 69, false, false);
					_curAni->AniStart();
				}

				break;
			}

			break;
			
		case EDynusPhase::STAR:
			switch (_starP)
			{
			case EStarPhase::STAR:
				if (!_isGM1Remove)
				{
					_rcGuardMine1 = RectMakeCenter(CENTER_X - 530, CENTER_Y + 60, 47, 44);
				}

				else
				{
					_rcGuardMine1 = RectMakeCenter(0, 0, 0, 0);
				}

				if (!_isGM2Remove)
				{
					_rcGuardMine2 = RectMakeCenter(CENTER_X + 530, CENTER_Y, 47, 44);
				}

				else
				{
					_rcGuardMine2 = RectMakeCenter(0, 0, 0, 0);
				}

				_isPlatform = true;
				_isMoveCenter = true;
				platformUp();

				if (_isPlatformUp)
				{
					_bgAlpha -= 9.0f;

					if (_bgAlpha <= 0)
					{
						_bgAlpha = 0.0f;

						bulletFire();
						_isMoveCenter = false;
						if (_isGM1Remove && _isGM2Remove)
						{
							_phase = EDynusPhase::THIRD;
							_isPlatformUp = false;
							_isPlatform = false;
						}
					}
				}

					break;
				}

				break;

		case EDynusPhase::THIRD:
			switch (_thirdP)
			{
			case EThirdPhase::RANDOM_PATTERN:
				_bulletTurnCount1 = 1.5f;
				_bulletTurnCount2 = 1.5f;
				_bulletTurnCount3 = 1.5f;
				_isStar = false;
				_isMoveCenter = true;
				_isCenterCount++;
				if (_isCenterCount > 50)
				{
					_isMoveCenter = false;
				}

				switch (_rndPattern)
				{
				case 0:
					//if (_curAni->getNowPlayIdx() == 20)
					//{
					//	// SD: 캐스팅
					//}
					bulletFire();
					
					if (_pa1StartPosIdx < 0)
					{
						_curAni->AniStop();
						_curImg = _spellImg;
						_curAni = _spellAni;
						_curAni->setPlayFrame(0, 69, false, false);
						_curAni->AniStart();

						_pa1StartPosIdx = 6;
						_pa2StartPosIdx = 3;
						_pa3StartPosIdx = 2;
						_isSpawnEnemy = false;
						if (_rndPattern == 0)
						{
							_rndPattern = RND->getFromIntTo(1, 3);
						}
					}

					break;

				case 1:
					//if (_curAni->getNowPlayIdx() == 20)
					//{
					//	// SD: 캐스팅
					//}
					spreadEllipse();

					if (_pa2StartPosIdx < 0)
					{
						_curAni->AniStop();
						_curImg = _spellImg;
						_curAni = _spellAni;
						_curAni->setPlayFrame(0, 69, false, false);
						_curAni->AniStart();
						_bulletCount = 0;
						_pa1StartPosIdx = 6;
						_pa2StartPosIdx = 3;
						_pa3StartPosIdx = 2;
						_isSpawnEnemy = false;
						_rndPattern = RND->getFromIntTo(0, 3);
					
						if (_rndPattern == 1)
						{
							_rndPattern = RND->getFromIntTo(2, 3);
						}
					}

					break;

				case 2:
					//if (_curAni->getNowPlayIdx() == 20)
					//{
					//	// SD: 캐스팅
					//}
					beamFire();

					if (_pa3StartPosIdx < 0)
					{
						_curAni->AniStop();
						_curImg = _spellImg;
						_curAni = _spellAni;
						_curAni->setPlayFrame(0, 69, false, false);
						_curAni->AniStart();
						_bulletCount = 0;
						_pa1StartPosIdx = 6;
						_pa2StartPosIdx = 3;
						_pa3StartPosIdx = 2;
						_isSpawnEnemy = false;

						_rndPattern = RND->getFromIntTo(0, 3);

						if (_rndPattern == 2)
						{
							_rndPattern = RND->getFromIntTo(0, 1);
						}
					}

					break;

				case 3:
					// SD: 캐스팅
					if (!_isSpawnEnemy)
					{
						_em->spawnShadeclaw();

						_isSpawnEnemy = true;
					}

					else
					{
						_afterSpawnCount++;

						if (_afterSpawnCount > 400)
						{
							_curAni->AniStop();
							_curImg = _spellImg;
							_curAni = _spellAni;
							_curAni->setPlayFrame(0, 69, false, false);
							_curAni->AniStart();
							_bulletCount = 0;
							_pa1StartPosIdx = 6;
							_pa2StartPosIdx = 3;
							_pa3StartPosIdx = 2;

							_rndPattern = RND->getFromIntTo(0, 3);

							if (_rndPattern == 3)
							{
								_rndPattern = RND->getFromIntTo(0, 2);
							}

							_afterSpawnCount = 0;

						}
					}

					break;
				}

				break;
			}

			case EDynusPhase::DEATH:

				break;
		}

		case EDynusState::DEATH:

			break;

		break;
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		SOUNDMANAGER->play("dynus_battle_v7", 0.3f);
		_state = EDynusState::SPELL;
		_curAni->AniStop();
		_curImg = _spellImg;
		_curAni = _spellAni;
		_curAni->setPlayFrame(0, 69, false, false);
		_curAni->AniStart();
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_hp -= 1000;
	}

	if (_isDamaged)
	{
		_invincibilityTime += TIMEMANAGER->getElapsedTime();

		if (_invincibilityTime > 0.4f)
		{
			_isDamaged = false;
			_invincibilityTime = 0.0f;
		}
	}

	if (_curAni->getNowPlayIdx() == 69)
	{
		_curAni->AniStop();
		_curImg = _breatheImg;
		_curAni = _breatheAni;
		_curAni->setPlayFrame(0, 7, false, true);
		_curAni->AniStart();
	}
}

void Dynus::render(void)
{
	draw();

	if (!_isDie)
	{
		_bullet->render();
		_beam->render();

		_hpBar->render();

		char bossHpRate[128];

		sprintf_s(bossHpRate, "%d %s %d", static_cast<int>(_hp), "/", static_cast<int>(_maxHp));

		FONTMANAGER->textOut(getMemDC(), CENTER_X - 10, CENTER_Y + 230, "배달의민족 을지로체",
			20, 500, "다이너스", strlen("다이너스"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), CENTER_X - 30, CENTER_Y + 250, "배달의민족 을지로체",
			15, 400, bossHpRate, strlen(bossHpRate), RGB(255, 255, 255));

		IMAGEMANAGER->render("DynusHpBarBorder", getMemDC(), CENTER_X - 210, CENTER_Y + 220);
	}
}

void Dynus::move(void)
{

}

void Dynus::draw(void)
{
	IMAGEMANAGER->render("DynusWing", getMemDC(),
		CAMERA->worldToCameraX(_x + 210), CAMERA->worldToCameraY(_y + 10));

	_curImg->aniRender(getMemDC(), CAMERA->worldToCameraX(_x),
		CAMERA->worldToCameraY(_y), _curAni);
	
	for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			if (i == _pa1StartPosIdx)
			{
				if (_state == EDynusState::SPELL && (_firstP == EFirstPhase::SPREAD_X || _starP == EStarPhase::SPREAD_X || _rndPattern == 0))
				{
					if (_p1PotalSize < 1.5f)
					{
						_p1PotalSize += 0.01f;
					}

					if (!_isDie)
					{
						IMAGEMANAGER->render("DynusBulletPortal", getMemDC(),
							CAMERA->worldToCameraX(_rcPa1Start[i][j].left + 7),
							CAMERA->worldToCameraY(_rcPa1Start[i][j].top + 7),
							IMAGEMANAGER->findImage("DynusBulletPortal")->getWidth() * _p1PotalSize,
							IMAGEMANAGER->findImage("DynusBulletPortal")->getHeight() * _p1PotalSize,
							0, 0, 22, 26);
					}

					_aftetKCount++;
				}
			}
		}
	}

	for (int i = 0; i < PA2_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
		{
			if ((i - 1) == _pa2StartPosIdx)
			{
				if (_state == EDynusState::SPELL && (_firstP == EFirstPhase::SPREAD_ELLIPSE || _rndPattern == 1))
				{
					if (_p2PotalSize < 1.5f)
					{
						_p2PotalSize += 0.005f;
					}

					if (!_isDie)
					{
						IMAGEMANAGER->render("DynusBulletPortal", getMemDC(),
							CAMERA->worldToCameraX(_rcPa2Start[i][j].left + 15),
							CAMERA->worldToCameraY(_rcPa2Start[i][j].top + 9),
							IMAGEMANAGER->findImage("DynusBulletPortal")->getWidth() * _p2PotalSize,
							IMAGEMANAGER->findImage("DynusBulletPortal")->getHeight() * _p2PotalSize,
							0, 0, 22, 26);
					}
				}
			}
		}
	}

	if (KEYMANAGER->isToggleKey('G'))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
		{
			for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
			{
				DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcPa1Start[i][j]));
			}
		}

		for (int i = 0; i < PA2_STARTPOS_NUM_1; i++)
		{
			for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
			{
				DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcPa2Start[i][j]));
			}
		}

		for (int i = 0; i < PA3_STARTPOS_NUM; i++)
		{
			DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcPa3Start[i]));
		}

		DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_player->getPlayerRC()));

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);
	}
}

void Dynus::drawPlatform(void)
{
	if (_phase == EDynusPhase::STAR)
	{
		if (_starP == EStarPhase::STAR)
		{
			switch (_starP)
			{
			case EStarPhase::STAR:

				drawGuardMine();
				
				for (int i = 0; i < 7; i++)
				{
					if (_rcPlatform[i].left == NULL)
					{
						continue;
					}

					IMAGEMANAGER->render("DynusJumpPlatform", getMemDC(),
						CAMERA->worldToCameraX(_rcPlatform[i].left),
						CAMERA->worldToCameraY(_rcPlatform[i].top));
				}
			}
		}
	}

	if (_isGM1Remove && _isGM2Remove)
	{
		_isPlatform = false;
	}
}

void Dynus::drawGuardMine(void)
{
	if (!_isGM1Remove)
	{
		//DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcGuardMine1));
		IMAGEMANAGER->render("GuardMine", getMemDC(), CAMERA->worldToCameraX(_rcGuardMine1.left),
			CAMERA->worldToCameraY(_rcGuardMine1.top));
	}

	if (!_isGM2Remove)
	{
		//DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcGuardMine2));
		IMAGEMANAGER->render("GuardMine", getMemDC(), CAMERA->worldToCameraX(_rcGuardMine2.left),
			CAMERA->worldToCameraY(_rcGuardMine2.top));
	}
}

void Dynus::bulletFire()
{
	if (_bulletCount < 3 && bulletCountFire())
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			_bullet->fire((_rcPa1Start[_pa1StartPosIdx][j].left + _rcPa1Start[_pa1StartPosIdx][j].right) / 2,
				(_rcPa1Start[_pa1StartPosIdx][j].bottom + _rcPa1Start[_pa1StartPosIdx][j].top) / 2,
				getAngle((_rcPa1Start[_pa1StartPosIdx][j].left + _rcPa1Start[_pa1StartPosIdx][j].right) / 2,
					(_rcPa1Start[_pa1StartPosIdx][j].bottom + _rcPa1Start[_pa1StartPosIdx][j].top) / 2,
					_player->getPlayerPosition().x, _player->getPlayerPosition().y) + j * 15.0f * 0.01f, 4.0f);
		}
		
		_bulletCount++;

		if (_p1PotalSize > 0)
		{
			_p1PotalSize -= 0.01f;
		}
	}

	if (_bulletCount == 3 && turnCountFire1() && _pa1StartPosIdx > -1)
	{
		_pa1StartPosIdx--;

		_bulletCount = 0;

		_p1PotalSize = 0.0f;
	}	
}

void Dynus::spreadEllipse(void)
{
	if (turnCountFire2())
	{
		for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
		{
			_bullet->fire((_rcPa2Start[_pa2StartPosIdx][j].left + _rcPa2Start[_pa2StartPosIdx][j].right) / 2,
				(_rcPa2Start[_pa2StartPosIdx][j].bottom + _rcPa2Start[_pa2StartPosIdx][j].top) / 2,
				DEGREE_RADIAN(j * 22.5f), 4.0f);
		}

		if (_pa2StartPosIdx > -1)
		{
			_pa2StartPosIdx--;

			_p2PotalSize = 0.0f;
		}
	}
}

void Dynus::beamFire(void)
{
	_p1PotalSize = 0.0f;
	_p2PotalSize = 0.0f;

	float speed = 25.0f;

	if ((_pa3StartPosIdx == 0 || _pa3StartPosIdx == 2))
	{
		speed = 25.0f;
	}

	else
	{
		speed = -25.0f;
	}

	if (turnCountFire3() && _pa3StartPosIdx > -1)
	{
		_beam->fire((_rcPa3Start[_pa3StartPosIdx].left + _rcPa3Start[_pa3StartPosIdx].right) / 2,
			(_rcPa3Start[_pa3StartPosIdx].bottom + _rcPa3Start[_pa3StartPosIdx].top) / 2, speed);

		_pa3StartPosIdx--;
	}
}

bool Dynus::spawningTime(void)
{
	if (_spawnBulletTime + _spawnBulletWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_spawnBulletWorldTime = TIMEMANAGER->getWorldTime();
		_spawnBulletTime = 1.0f;

		return true;
	}

	return false;
}

void Dynus::platformUp(void)
{
	if (_isPlatform)
	{
		if (_platformMove > -290)
		{
			_platformMove -= 1.7f;

			if (_platformMove >= -50)
			{
				_rcPlatform[0] = RectMakeCenter(CENTER_X, CENTER_Y + _platformMove + 100, 76, 76);
			}

			if (_platformMove >= -90 && _platformMove <= -40)
			{
				_rcPlatform[1] = RectMakeCenter(CENTER_X - 140, CENTER_Y + _platformMove + 190, 76, 76);
			}

			if (_platformMove >= -130 && _platformMove <= -80)
			{
				_rcPlatform[2] = RectMakeCenter(CENTER_X - 260, CENTER_Y + _platformMove + 170, 76, 76);
			}

			if (_platformMove >= -170 && _platformMove <= -120)
			{
				_rcPlatform[3] = RectMakeCenter(CENTER_X - 400, CENTER_Y + _platformMove + 260, 76, 76);
			}

			if (_platformMove >= -210 && _platformMove <= -160)
			{
				_rcPlatform[4] = RectMakeCenter(CENTER_X + 140, CENTER_Y + _platformMove + 320, 76, 76);
			}

			if (_platformMove >= -250 && _platformMove <= -200)
			{
				_rcPlatform[5] = RectMakeCenter(CENTER_X + 280, CENTER_Y + _platformMove + 330, 76, 76);
			}

			if (_platformMove >= -290 && _platformMove <= -240)
			{
				_rcPlatform[6] = RectMakeCenter(CENTER_X + 400, CENTER_Y + _platformMove + 320, 76, 76);

				_isPlatformUp = true;
			}
		}
	}
}

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

bool Dynus::turnCountFire1(void)
{
	if (_bulletTurnCount1 + _turnCount1 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount1 = TIMEMANAGER->getWorldTime();

		if (_phase != EDynusPhase::THIRD)
		{
			_bulletTurnCount1 = 2.0f;
		}

		else
		{
			_bulletTurnCount1 = 1.5f;
		}

		return true;
	}

	return false;
}

bool Dynus::turnCountFire2(void)
{
	if (_bulletTurnCount2 + _turnCount2 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount2 = TIMEMANAGER->getWorldTime();
		if (_phase != EDynusPhase::THIRD)
		{
			_bulletTurnCount1 = 2.0f;
		}

		else
		{
			_bulletTurnCount1 = 1.5f;
		}

		return true;
	}

	return false;
}

bool Dynus::turnCountFire3(void)
{
	if (_bulletTurnCount3 + _turnCount3 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount3 = TIMEMANAGER->getWorldTime();
		if (_phase != EDynusPhase::THIRD)
		{
			_bulletTurnCount1 = 2.0f;
		}

		else
		{
			_bulletTurnCount1 = 1.5f;
		}

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

bool Dynus::spawnAfterTime(void)
{
	if (_spawnAtferTime + _spawnWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_spawnWorldTime = TIMEMANAGER->getWorldTime();
		_spawnAtferTime = 5.0f;

		return true;
	}

	return false;
}

void Dynus::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;

		if (IntersectRect(&rc, &CollisionAreaResizing(_bullet->getBullet()[i].rc, 15, 15),
			&_player->getPlayerRC()))
		{
			_bullet->removeBullet(i);
			_player->hitDamage(5.0f);
		}
	}

	for (int i = 0; i < _beam->getBullet().size(); i++)
	{
		RECT rc;

		if (IntersectRect(&rc, &_beam->getBullet()[i].rc, &_player->getPlayerRC()))
		{
			_player->hitDamage(10.0f);
		}
	}
}
