#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"
#include "../UI/ProgressBar.h"

#define GEMFIRE_COUNT 4

enum class EDizzyState
{
	SLEEP,
	WAKE,
	IDLE,
	SPIN,
	GROGGY,
	RANGE,
	DEATH
};

class Player;
class Dizzy : public GameNode
{
private:
	EDizzyState _state;

	GImage* _wakeImg;
	GImage* _idleImg;
	GImage* _spinImg;
	GImage* _rangeImg;

	GImage* _curImg;

	GImage* _collisionMap;

	bool _isCollisionLeft;
	bool _isCollisionRight;
	bool _isCollisionTop;
	bool _isCollisionBottom;

	Animation* _wakeAni;
	Animation* _idleAni;
	Animation* _spinAni;
	Animation* _rangeAni;

	Animation* _curAni;

	float _x, _y;

	RECT _rcDizzy;
	RECT _rcSpinAtk;

	ProgressBar* _hpBar;
	float _hp;
	float _maxHp;

	bool _isWake;
	bool _isLeft;
	float _worldTimeCount;

	Player* _player;

	float _spinStartX, _spinStartY;
	int _spinCount;

	Meteor* _meteor;
	Gems* _gem;

	char _gemImg[128];
	int _rndGemImg;

	float _meteorFireX, _meteorFireY;

	int _meteorIdx;

	int _meteorCount;
	float _fireCount;
	float _meteorFireCount;
	float _meteorTurnCount;
	float _turnCount;

	int _aftetMeteorCount;

	float _gemFireX, _gemFireY;

	int _gemIdx;

	int _gemCount;
	float _fireCount2;
	float _gemFireCount;
	float _gemTurnCount;
	float _turnCount2;

	int _aftetGemCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RECT _rcColl[4];

	//void move(void);
	void draw(void);
	void animation(void);

	void spin(void);
	void meteorFire(void);
	bool meteorCountFire(void);
	bool turnCountFire(void);
	void gemFire(void);
	bool gemCountFire(void);
	bool turnCountFire2(void);

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	Dizzy() {}
	~Dizzy() {}
};

