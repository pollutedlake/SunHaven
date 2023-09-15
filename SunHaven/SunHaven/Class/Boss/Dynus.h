#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"
#include "../UI/ProgressBar.h"
//#include "../Enemy/Enemy.h"
//#include "../Enemy/EnemyManager.h"

// 1������ ���� ���� ��ġ ����
#define PA1_STARTPOS_NUM_1	7
#define PA1_STARTPOS_NUM_2	4

#define PA2_STARTPOS_NUM_1	4 
#define PA2_STARTPOS_NUM_2	16
 
#define PA3_STARTPOS_NUM	3 

#define PLATFORM_NUM		7

class Player;
class EnemyManager;

enum class EDynusState
{
	BREATHE,
	GRUNT,
	HAIR,
	LAUGHING,
	SPELL
};

enum class EDynusPhase
{
	FIRST,
	SECOND,
	STAR,
	THIRD
};

enum class EFirstPhase
{
	SPREAD_X,
	SPREAD_ELLIPSE,
	BEAM1,
	BEAM2,
};

enum class ESecondPhase
{
	SPAWN,
	SPREAD_X
};

enum class EStarPhase
{
	STAR,
	SPREAD_X
};

enum class EThirdPhase
{
	RANDOM_PATTERN
};

class Dynus : public GameNode
{
private:
	Player* _player;
	EnemyManager* _em;

	EDynusState _state;
	EDynusPhase _phase;
	EFirstPhase _firstP;
	ESecondPhase _secondP;
	EStarPhase _starP;
	EThirdPhase _thirdP;

	GImage* _curImg;
	GImage* _breatheImg;
	GImage* _spellImg;

	Animation* _breatheAni;
	Animation* _spellAni;
	Animation* _curAni;

	ProgressBar* _hpBar;

	Bullet* _bullet;
	Beam* _beam;

	RECT _rcDynus;

	RECT _rcPa1Start[PA1_STARTPOS_NUM_1][PA1_STARTPOS_NUM_2];
	RECT _rcPa2Start[PA2_STARTPOS_NUM_1][PA2_STARTPOS_NUM_2];
	RECT _rcPa3Start[PA3_STARTPOS_NUM];
	RECT _rcPlatform[PLATFORM_NUM];
	float _platformMove;
	bool _isPlatformUp;
	RECT _rcGuardMine1;
	RECT _rcGuardMine2;
	bool _isGM1Remove;
	bool _isGM2Remove;

	//RECT _rcHpBar;
	float _hp;
	float _maxHp;

	float _x, _y;

	float _bulletFireCount;	// ����1
	float _fireCount;		// ����1 ź�� ���� ����
	int _bulletCount;		// ����1 1ȸ�� ź�� �߻� Ƚ��
	float _turnCount1;		// ����1 ���� ����
	float _turnCount2;		// ����2 ���� ����
	float _turnCount3;		// ����2 ���� ����
	float _bulletTurnCount1;	// ����1 �� �� ���� �� ����
	float _bulletTurnCount2;	// ����2 �� �� ���� �� ����
	float _bulletTurnCount3;	// ����2 �� �� ���� �� ����
	float _beamFireCount;	// ����3 1ȸ�� ź�� �߻� Ƚ��
	int _beamCount;			// ����3 ź�� ���� ����
	float _beamTurnCount;	// ����3 
	float _spawnAtferTime;
	float _spawnWorldTime;

	float _worldTimeCount;
	int _timeCount;

	int _pa1StartPosIdx;
	int _pa2StartPosIdx;
	int _pa3StartPosIdx;

	int _rndPattern;
	
	//int _nextPaIdx;		// ������� �ٸ� ���� ����(ī��Ʈ�� ����)

	float _hpTime;
	float _hpTurnCount;

	float _spawnBulletTime;
	float _spawnBulletWorldTime;

	bool _isSpawn;
	bool _isSpawnEnemy;
	bool _isSpawnAfter;

	float _k;

	float _bgAlpha;

	int _afterSpawnCount;
	int _aftetKCount;

	float _invincibilityTime;
	bool _isDamaged;

public:
	bool hpMinusTemp(void);

	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);

	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void drawPlatform(void);
	void drawGuardMine(void);

	void bulletFire(void);
	void spreadEllipse(void);
	void beamFire(void);
	bool spawningTime(void);


	bool bulletCountFire(void);
	bool turnCountFire1(void);
	bool turnCountFire2(void);
	bool turnCountFire3(void);
	bool beamCountFire(void);
	bool spawnAfterTime(void);

	void collision(void);

	inline void hitDamage(float damage)
	{
		if (_invincibilityTime == 0.0f)
		{
			_isDamaged = true;
			_hp -= damage;
		}

		if (_hp <= 0)
		{
			_hp = 0;
		}
	}

	RECT getRcDynus(void) { return _rcDynus; }
	Bullet* getBullet(void) { return _bullet; }

	RECT getRcGuardMine1(void) { return _rcGuardMine1; }
	RECT getRcGuardMine2(void) { return _rcGuardMine2; }

	void setIsGM1Remove(bool isGM1Remove) { _isGM1Remove = isGM1Remove; }
	void setIsGM2Remove(bool isGM2Remove) { _isGM2Remove = isGM2Remove; }

	float getBgAlpha(void) { return _bgAlpha; }

	void setPlayerMemoryAddress(Player* player) { _player = player; }
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }

	Dynus() {}
	~Dynus() {}
};

