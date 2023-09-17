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
	GImage* _deathImg;

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
	Animation* _deathAni;

	Animation* _curAni;

	float _x, _y;

	RECT _rcDizzy;
	RECT _rcSpinAtk;

	ProgressBar* _hpBar;
	float _hp;
	float _maxHp;

	bool _isWake;
	bool _isDie;
	bool _isLeft;
	float _worldTimeCount;

	Player* _player;

	float _spinFromX, _spinFromY;
	float _spinToX, _spinToY;
	int _spinCount;

	Meteor* _meteor;
	Gems* _gem;

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
	int soundTime;
	int _afterDeathTime;
	
	float _afterDeathWorldTime;
	float _invincibilityTime;
	bool _isDamaged;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void draw(void);

	void spin(void);
	void meteorFire(void);
	bool meteorCountFire(void);
	bool turnCountFire(void);
	void gemFire(void);
	bool gemCountFire(void);
	bool turnCountFire2(void);
	bool afterDeathTime(void);

	void setPlayerMemoryAddress(Player* player) { _player = player; }

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

	void collision(void);
	void pixelCollision(void);

	RECT getRcDizzy(void) { return _rcDizzy; }
	RECT getRcSpinAttack(void) { return _rcSpinAtk; }

	Dizzy() {}
	~Dizzy() {}
};

