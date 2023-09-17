#pragma once
#include "../Enemy/Enemy.h"

class Player;
class Shadeclaw : public Enemy
{
private:
	Player* _player;


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

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	Shadeclaw() {}
	~Shadeclaw() {}
};

