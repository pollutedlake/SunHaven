#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"
#include "../UI/ProgressBar.h"

enum class EDizzyState
{
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

	GImage* _img;

	float _x, _y;

	RECT _rcDizzy;

	ProgressBar* _hpBar;
	float _hp;
	float _maxHp;

	Bullet* _bullet;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//void move(void);
	void draw(void);

	Dizzy() {}
	~Dizzy() {}
};

