#pragma once
#include "../GameNode/GameNode.h"
//#include "../Boss/Dynus.h"
#include "../Enemy/Enemy.h"
#include "../Bullets/Bullets.h"

class Player_Temp;
class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vEnemy;
	viEnemy _viEnemy;

	Bullet* _bullet;
	Player_Temp* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setEnemy(void);
	void spawnShadeclaw(void);
	void removeEnemy(int arrNum);

	void EnemyBulletFire(void);
	void collision(void);

	vector<Enemy*> getEnemys(void) { return _vEnemy; }
	Bullet* getBullet(void) { return _bullet; }
	void setPlayerMemoryAddress(Player_Temp* player) { _player = player; }

	/*float getCenterX() { return _centerX; }
	void setCenterX(float centerX) { _centerX = centerX; }

	float getCenterY() { return _centerY; }
	void setCenterY(float centerY) { _centerY = centerY; }*/

	EnemyManager() {}
	~EnemyManager() {}

};

