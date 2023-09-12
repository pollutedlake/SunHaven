#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"
#include "../UI/ProgressBar.h"

enum class EDizzyState
{
	SLEEP,
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
	GImage* _groggyImg;
	GImage* _rangeImg;

	float _x, _y;

	RECT _rcDizzy;

	ProgressBar* _hpBar;
	float _hp;
	float _maxHp;

	bool _isWake;

	bool _isLeft;

	float _worldTimeCount;

	int _currentFrameX;
	int _currentFrameY;

	Player* _player;

	Bullet* _bullet;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//void move(void);
	void draw(void);
	void animation(void);

	void spin(void);

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	Dizzy() {}
	~Dizzy() {}
};

