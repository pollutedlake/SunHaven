#include "Stdafx.h"
#include "Dynus.h"
#include "../../Player/Player.h"
//#include "../Enemy/Shadeclaw.h"
#include "../Enemy/EnemyManager.h"

bool Dynus::hpMinusTemp(void)
{
	if (_hpTime + _hpTurnCount <= TIMEMANAGER->getWorldTime())
	{
		_hpTurnCount = TIMEMANAGER->getWorldTime();
		_hpTime = 1.0f;

		return true;
	}

	return false;
}

HRESULT Dynus::init(void)
{
	//_state = EDynusState::BREATHE;
	_phase = EDynusPhase::FIRST;
	//_spell = EDynusSpell::SPREAD_X;

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
	_bulletTurnCount3 = 0.5f;
	_beamCount = 0.0f;
	_beamFireCount = 0.0f;
	_beamTurnCount = TIMEMANAGER->getWorldTime();
	_spawnAtferTime = 0.0f;
	_spawnWorldTime = TIMEMANAGER->getWorldTime();

	_hpTime = 1.0f;
	_hpTurnCount = TIMEMANAGER->getWorldTime();

	_timeCount = 100;

	//_dynusImg = IMAGEMANAGER->findImage("DynusBreathe");

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

	_curImg = _breatheImg;
	_curAni = _breatheAni;
	_curAni->AniStart();

	_bullet = new Bullet;
	_bullet->init("DynusOrb", 100, 1500.0f);

	_spawnBulletTime = 1.0f;
	_spawnBulletWorldTime = TIMEMANAGER->getWorldTime();

	_beam = new Beam;
	_beam->init(50, 1500.0f);

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

	_platformMove = 0.0f;

	_isPlatformUp = false;

	for (int i = 0; i < 7; i++)
	{
		_rcPlatform[i] = { NULL, NULL, NULL, NULL };
	}

	_rcGuardMine1 = { NULL, NULL, NULL, NULL };
	_rcGuardMine2 = { NULL, NULL, NULL, NULL };

	_isGM1Remove = false;
	_isGM2Remove = false;

	/*_rcPlatform[0] = RectMakeCenter(CENTER_X, CENTER_Y + _platformMove + 100, 76, 76);
	_rcPlatform[1] = RectMakeCenter(CENTER_X - 140, CENTER_Y + _platformMove + 150, 76, 76);
	_rcPlatform[2] = RectMakeCenter(CENTER_X - 260, CENTER_Y + _platformMove + 90, 76, 76);
	_rcPlatform[3] = RectMakeCenter(CENTER_X - 400, CENTER_Y + _platformMove + 140, 76, 76);
	_rcPlatform[4] = RectMakeCenter(CENTER_X + 140, CENTER_Y + _platformMove + 160, 76, 76);
	_rcPlatform[5] = RectMakeCenter(CENTER_X + 280, CENTER_Y + _platformMove + 130, 76, 76);
	_rcPlatform[6] = RectMakeCenter(CENTER_X + 400, CENTER_Y + _platformMove + 80, 76, 76);*/

	/*_rcPlatform[0] = RectMakeCenter(CENTER_X, CENTER_Y + 50, 76, 76);
	_rcPlatform[1] = RectMakeCenter(CENTER_X - 140, CENTER_Y + 100, 76, 76);
	_rcPlatform[2] = RectMakeCenter(CENTER_X - 260, CENTER_Y + 40, 76, 76);
	_rcPlatform[3] = RectMakeCenter(CENTER_X - 400, CENTER_Y + 90, 76, 76);
	_rcPlatform[4] = RectMakeCenter(CENTER_X + 140, CENTER_Y + 110, 76, 76);
	_rcPlatform[5] = RectMakeCenter(CENTER_X + 280, CENTER_Y + 80, 76, 76);
	_rcPlatform[6] = RectMakeCenter(CENTER_X + 400, CENTER_Y + 30, 76, 76);*/

	_pa1StartPosIdx = 6;
	_pa2StartPosIdx = 3;
	_pa3StartPosIdx = 2;

	_rndPattern = 0;

	_isSpawn = false;
	_isSpawnEnemy = false;
	_isSpawnAfter = false;

	_k = 0.0f;

	_bgAlpha = 255.0f;

	_afterSpawnCount = 0;
	_aftetKCount = 0;
	//_em->spawnShadeclaw();

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
		_phase = EDynusPhase::STAR;
	}

	else if (_hp <= 3000 && _hp > 0)
	{
		_phase = EDynusPhase::THIRD;
		_thirdP = EThirdPhase::RANDOM_PATTERN;
	}

	_hpBar->update();
	_hpBar->setGauge(_hp, _maxHp);


	cout << "현재 페이즈: " << (int)_phase << endl;

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
		
		switch (_phase)
		{
		case EDynusPhase::FIRST:
			switch (_firstP)
			{
			case EFirstPhase::SPREAD_X:

				//_em->spawnShadeclaw();
				//beamFire();

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
				spreadEllipse();

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
				bulletFire();
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

			cout << "star" << endl;

			if (!_isGM1Remove)
			{
				_rcGuardMine1 = RectMakeCenter(CENTER_X - 530, CENTER_Y + 60, 47, 44);
			}

			if (!_isGM2Remove)
			{
				_rcGuardMine2 = RectMakeCenter(CENTER_X + 530, CENTER_Y, 47, 44);
			}

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

				if (_isPlatformUp)
				{
					_bgAlpha -= 9.0f;
					_isGM1Remove = true;
					_isGM2Remove = true;
					_bulletCount = 0;
					_pa1StartPosIdx = 6;
					_pa2StartPosIdx = 3;
					_pa3StartPosIdx = 2;
					if (_bgAlpha <= 0)
					{
						_bgAlpha = 0.0f;

						bulletFire();
						cout << "3페이즈 시작" << endl;

						if (_isGM1Remove && _isGM2Remove)
						{
							cout << "3페이즈 시작" << endl;
							_phase = EDynusPhase::THIRD;
						}
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
				/*if (_platformMove < -50)
				{
					_platformMove += 1.7f;

					if (_platformMove >= -290 && _platformMove <= -240)
					{
						_rcPlatform[0] = RectMakeCenter(CENTER_X, CENTER_Y + _platformMove + 100, 76, 76);
					}

					if (_platformMove >= -250 && _platformMove <= -200)
					{
						_rcPlatform[1] = RectMakeCenter(CENTER_X - 140, CENTER_Y + _platformMove + 190, 76, 76);
					}

					if (_platformMove >= -210 && _platformMove <= -160)
					{
						_rcPlatform[2] = RectMakeCenter(CENTER_X - 260, CENTER_Y + _platformMove + 170, 76, 76);
					}

					if (_platformMove >= -170 && _platformMove <= -120)
					{
						_rcPlatform[3] = RectMakeCenter(CENTER_X - 400, CENTER_Y + _platformMove + 260, 76, 76);
					}

					if (_platformMove >= -130 && _platformMove <= -80)
					{
						_rcPlatform[4] = RectMakeCenter(CENTER_X + 140, CENTER_Y + _platformMove + 320, 76, 76);
					}

					if (_platformMove >= -90 && _platformMove <= -40)
					{
						_rcPlatform[5] = RectMakeCenter(CENTER_X + 280, CENTER_Y + _platformMove + 330, 76, 76);
					}

					if (_platformMove >= -50 && _platformMove <= 0)
					{
						_rcPlatform[6] = RectMakeCenter(CENTER_X + 400, CENTER_Y + _platformMove + 320, 76, 76);

						_isPlatformUp = false;
					}
				}*/

				//if (!_isPlatformUp)
				//{
				switch (_rndPattern)
				{
				case 0:
					bulletFire();
					cout << "bulletFire" << endl;

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
					spreadEllipse();
					cout << "spreadEllipse" << endl;

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
					beamFire();
					cout << "beamFire" << endl;

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
					cout << "spawnShadeclaw" << endl;
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

				//}
			}
		}

		break;
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		_state = EDynusState::SPELL;
		_curAni->AniStop();
		_curImg = _spellImg;
		_curAni = _spellAni;
		_curAni->setPlayFrame(0, 69, false, false);
		_curAni->AniStart();

		/*switch (_spell)
		{
		case EDynusSpell::SPREAD_X:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::SPREAD_ELLIPSE:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::BEAM1:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::BEAM2:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;

		case EDynusSpell::SPAWN:
			_spellAni->setPlayFrame(0, 70, false, false);
			_spellAni->AniStart();

			break;
		}*/
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_hp -= 1000;
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_phase = EDynusPhase::SECOND;
	}

	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	/*_breatheAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_spellAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);*/

	_bullet->update();
	_beam->update();
	collision();

	/*if (_state == EDynusState::SPELL && _phase == EDynusPhase::SECOND && _secondP == ESecondPhase::SPAWN)
	{
		if (_isSpawnEnemy && spawnAfterTime())
		{
			_spell = EDynusSpell::SPREAD_X;
			_pa1StartPosIdx = 6;
		}
	}*/

	cout << _curAni->getNowPlayIdx() << endl;

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

void Dynus::move(void)
{

}

void Dynus::draw(void)
{
	IMAGEMANAGER->render("DynusWing", getMemDC(), _x + 210, _y + 10);

	_curImg->aniRender(getMemDC(), _x, _y, _curAni);
	
	for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			if (i == _pa1StartPosIdx)
			{
				if (_state == EDynusState::SPELL && (_firstP == EFirstPhase::SPREAD_X || _starP == EStarPhase::SPREAD_X || _rndPattern == 0))
				{
					if (_k < 1.5f)
					{
						_k += 0.01f;
					}

					IMAGEMANAGER->render("DynusBulletPortal", getMemDC(),
						_rcPa1Start[i][j].left + 7, _rcPa1Start[i][j].top + 7,
						IMAGEMANAGER->findImage("DynusBulletPortal")->getWidth() * _k,
						IMAGEMANAGER->findImage("DynusBulletPortal")->getHeight() * _k,
						0, 0,
						22, 26);

					_aftetKCount++;

					if (_aftetKCount > 10)
					{
						if (_k > 0.0f)
						{
							_k -= 0.01f;
						}

						IMAGEMANAGER->render("DynusBulletPortal", getMemDC(),
							_rcPa1Start[i][j].left + 7, _rcPa1Start[i][j].top + 7,
							IMAGEMANAGER->findImage("DynusBulletPortal")->getWidth() * _k,
							IMAGEMANAGER->findImage("DynusBulletPortal")->getHeight() * _k,
							0, 0,
							22, 26);

						_aftetKCount = 0;
					}
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
					if (_k < 1.5f)
					{
						_k += 0.01f;
					}

					IMAGEMANAGER->render("DynusBulletPortal", getMemDC(),
						_rcPa2Start[i][j].left + 15, _rcPa2Start[i][j].top + 9,
						IMAGEMANAGER->findImage("DynusBulletPortal")->getWidth() * _k,
						IMAGEMANAGER->findImage("DynusBulletPortal")->getHeight() * _k,
						0, 0,
						22, 26);
				}
			}
		}
	}

	/*for (int i = 0; i < PA2_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA2_STARTPOS_NUM_2; j++)
		{
			DrawRectMake(getMemDC(), _rcPa2Start[i][j]);
		}
	}

	for (int i = 0; i < PA3_STARTPOS_NUM; i++)
	{
		DrawRectMake(getMemDC(), _rcPa3Start[i]);
	}*/

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

void Dynus::drawPlatform(void)
{
	if (_phase == EDynusPhase::STAR)
	{
		if (_starP == EStarPhase::STAR)
		{
			switch (_starP)
			{
			case EStarPhase::STAR:

				cout << "star" << endl;

				drawGuardMine();

				for (int i = 0; i < 7; i++)
				{
					if (_rcPlatform[i].left == NULL)
					{
						continue;
					}

					IMAGEMANAGER->render("DynusJumpPlatform", getMemDC(), _rcPlatform[i].left, _rcPlatform[i].top);
				}
			}
		}
	}
}

void Dynus::drawGuardMine(void)
{
	IMAGEMANAGER->render("GuardMine", getMemDC(), _rcGuardMine1.left, _rcGuardMine1.top);
	IMAGEMANAGER->render("GuardMine", getMemDC(), _rcGuardMine2.left, _rcGuardMine2.top);
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

		if (_k > 0)
		{
			_k -= 0.01f;
		}
	}

	if (_bulletCount == 3 && turnCountFire1() && _pa1StartPosIdx > -1)
	{
		_pa1StartPosIdx--;

		_bulletCount = 0;

		_k = 0.0f;
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

			_k = 0.0f;
		}
	}
}

void Dynus::beamFire(void)
{
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

bool Dynus::turnCountFire1(void)
{
	if (_bulletTurnCount1 + _turnCount1 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount1 = TIMEMANAGER->getWorldTime();

		_bulletTurnCount1 = 1.5f;

		return true;
	}

	return false;
}

bool Dynus::turnCountFire2(void)
{
	if (_bulletTurnCount2 + _turnCount2 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount2 = TIMEMANAGER->getWorldTime();
		_bulletTurnCount2 = 1.5f;

		return true;
	}

	return false;
}

bool Dynus::turnCountFire3(void)
{
	if (_bulletTurnCount3 + _turnCount3 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount3 = TIMEMANAGER->getWorldTime();
		_bulletTurnCount3 = 0.5f;

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
			//_player->hitDamage(2.0f);
		}
	}
}
