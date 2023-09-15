#pragma once
#include "../Enemy/Enemy.h"

class Player;
class SteelSlug : public Enemy
{
private:
	Player* _player;

	float _atkFromX, _atkFromY;
	float _atkToX, _atkToY;

	float _atkSpeed;


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

	void pixelCollision(void) override;

	void setPlayerMemoryAddress(Player* player) { _player = player; }

	SteelSlug() {}
	~SteelSlug() {}
};

