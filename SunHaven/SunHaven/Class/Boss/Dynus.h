#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"
//#include "../Enemy/Enemy.h"
//#include "../Enemy/EnemyManager.h"

// 1페이즈 패턴 시작 위치 갯수
#define PA1_STARTPOS_NUM_1	7
#define PA1_STARTPOS_NUM_2	4

#define PA2_STARTPOS_NUM_1	4 
#define PA2_STARTPOS_NUM_2	16
 
#define PA3_STARTPOS_NUM	3 

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

enum class EDynusSpell
{
	SPREAD_X,
	SPREAD_ELLIPSE,
	BEAM,
	SPAWN
};

class Dynus : public GameNode
{
//private:
//	typedef vector<Enemy*> vEnemy;
//	typedef vector<Enemy*>::iterator viEnemy;
//
//private:
//	vEnemy _vEnemy;
//	viEnemy _viEnemy;

private:
	Player* _player;
	EnemyManager* _em;

	EDynusState _state;
	EDynusPhase _phase;
	EDynusSpell _spell;

	GImage* _breatheImg;
	GImage* _spellImg;

	Animation* _breatheAni;
	Animation* _spellAni;

	Bullet* _bullet;
	Beam* _beam;

	RECT _rcDynus;

	RECT _rcPa1Start[PA1_STARTPOS_NUM_1][PA1_STARTPOS_NUM_2];
	RECT _rcPa2Start[PA2_STARTPOS_NUM_1][PA2_STARTPOS_NUM_2];
	RECT _rcPa3Start[PA3_STARTPOS_NUM];

	float _x, _y;

	float _bulletFireCount;	// 패턴1
	float _fireCount;		// 패턴1 탄알 사이 간격
	int _bulletCount;		// 패턴1 1회당 탄알 발사 횟수
	float _turnCount1;		// 패턴1 사이 간격
	float _turnCount2;		// 패턴2 사이 간격
	float _bulletTurnCount1;	// 패턴1 한 번 공격 당 간격
	float _bulletTurnCount2;	// 패턴2 한 번 공격 당 간격
	float _beamFireCount;	// 패턴3 1회당 탄알 발사 횟수
	int _beamCount;			// 패턴3 탄알 사이 간격
	float _beamTurnCount;	// 패턴3 
	float _spawnAtferTime;
	float _spawnWorldTime;

	float _worldTimeCount;
	int _timeCount;

	int _pa1StartPosIdx;
	int _pa2StartPosIdx;
	int _pa3StartPosIdx;

	int _rndPattern;
	
	//int _nextPaIdx;		// 페이즈마다 다른 패턴 간격(카운트로 관리)

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	void draw(void);

	void bulletFire(void);
	void spreadEllipse(void);
	void beamFire(void);
	//void spawnEnemy(void);
	

	bool bulletCountFire(void);
	bool turnCountFire1(void);
	bool turnCountFire2(void);
	bool beamCountFire(void);
	bool spawnAfterTime(void);

	RECT getRcDynus(void) { return _rcDynus; }
	//vector<Enemy*> getEnemys(void) { return _vEnemy; }
	Bullet* getBullet(void) { return _bullet; }

	void setPlayerMemoryAddress(Player* player) { _player = player; }
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }

	Dynus() {}
	~Dynus() {}
};

