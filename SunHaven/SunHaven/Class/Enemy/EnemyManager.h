#pragma once
#include "../GameNode/GameNode.h"
#include "../Enemy/Enemy.h"
#include "../Bullets/Bullets.h"

class Player;
class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vEnemy;
	viEnemy _viEnemy;

	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void spawnSteelSlug(void);
	void spawnFlameImp(void);
	void spawnShadeclaw(void);
	void spawnRootwalker(void);

	void removeEnemy(int arrNum);

	vector<Enemy*> getEnemys(void) { return _vEnemy; }
	void setPlayerMemoryAddress(Player* player) { _player = player; }

	EnemyManager() {}
	~EnemyManager() {}

};

