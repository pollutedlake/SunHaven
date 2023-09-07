#pragma once
#include "Enemy.h"

class Player;

//enum class EShadeclawState
//{
//	IDLE,
//	MOVE,
//	ATTACK,
//	DIE
//};

class Shadeclaw : public Enemy
{
private:
	//EShadeclawState _state;

	float _speed;

	Player* _player;

public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move() override;
	void attack() override;
	void animation() override;
	void draw() override;

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	//EShadeclawState getEState(void) { return _state; }
	//void setEState(EShadeclawState state) { _state = state; }

	Shadeclaw() {}
	~Shadeclaw() {}
};

