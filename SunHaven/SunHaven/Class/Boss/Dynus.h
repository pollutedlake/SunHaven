#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"
//#include "../Enemy/Enemy.h"
//#include "../Enemy/EnemyManager.h"

// 1������ ���� ���� ��ġ ����
#define PA1_STARTPOS_NUM_1	7
#define PA1_STARTPOS_NUM_2	4

#define PA2_STARTPOS_NUM_1	4 
#define PA2_STARTPOS_NUM_2	16
 
#define PA3_STARTPOS_NUM	3 

class Player_Temp;
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
	Player_Temp* _player;
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

	float _bulletFireCount;	// ����1
	float _fireCount;		// ����1 ź�� ���� ����
	int _bulletCount;		// ����1 1ȸ�� ź�� �߻� Ƚ��
	float _turnCount;		// ����1,2 ���� ����
	float _bulletTurnCount;	// ����2
	float _beamFireCount;	// ����3 1ȸ�� ź�� �߻� Ƚ��
	int _beamCount;			// ����3 ź�� ���� ����
	float _beamTurnCount;	// ����3 

	float _worldTimeCount;
	int _timeCount;

	int _pa1StartPosIdx;
	int _pa2StartPosIdx;
	int _pa3StartPosIdx;

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
	bool turnCountFire(void);
	bool beamCountFire(void);

	RECT getRcDynus(void) { return _rcDynus; }
	//vector<Enemy*> getEnemys(void) { return _vEnemy; }
	Bullet* getBullet(void) { return _bullet; }

	void setPlayerMemoryAddress(Player_Temp* player) { _player = player; }
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }

	Dynus() {}
	~Dynus() {}
};

