#pragma once
#include "Enemy.h"

class Player_Temp;

enum class EShadeclawState
{
	IDLE,
	ATTACK,
	DIE
};

class Shadeclaw : public Enemy
{
private:
	EShadeclawState _state;

	float _speed;

	Player_Temp* _player;

public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move() override;
	void attack() override;
	void animation() override;
	void draw() override;

	void setPlayerMemoryAddress(Player_Temp* player) { _player = player; }

	Shadeclaw() {}
	~Shadeclaw() {}
};

