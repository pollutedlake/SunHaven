#pragma once
#include "../Enemy/Enemy.h"
#include "../Bullets/Bullets.h"

class Player;
class FlameImp : public Enemy
{
private:
	Player* _player;

	float _atkFromX, _atkFromY;
	float _atkToX, _atkToY;

	EnemyFireBall* _fireBall;

	float _fireBallSpeed;

public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void) override;
	void targetOn(void) override;
	void attack(void) override;
	void draw(void) override;

	bool attackCoolDown(void) override;

	//void collision(void);

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	FlameImp() {}
	~FlameImp() {}
};

