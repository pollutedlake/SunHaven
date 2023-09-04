#pragma once
#include "../GameNode/GameNode.h"
//#include "../Enemy/EnemyManager.h"

class Player_Temp : public GameNode
{
private:
	RECT _rcPlayer;
	float _x, _y;

	//EnemyManager* _em;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RECT getRect(void) { return _rcPlayer; }
	POINT getPosition(void) { return PointMake(_x, _y); }

	//void setEnemyMangerMemoryAddress(EnemyManager* em) { _em = em; }

	Player_Temp() {}
	~Player_Temp() {}
};

