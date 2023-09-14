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

	float _patrolX;
	float _patrolY;

public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void) override;
	void targetOn(void) override;
	void attack(void) override;
	void animation(void) override;
	void draw(void) override;

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	//EShadeclawState getEState(void) { return _state; }
	//void setEState(EShadeclawState state) { _state = state; }

	Shadeclaw() {}
	~Shadeclaw() {}
};

