#pragma once

enum class EEnemyType
{
	STEELSLUG,
	MAGMABUG,
	FLAMEIMP,
	TRAPWEED,
	SHADECLEW
};

struct tagEnemy
{
	string name;
	int level;
	int hp;
	int minDmg;
	int maxDmg;
	int def;
	int exp;
};

class EnemyData
{
private:
	queue<tagEnemy*> _enemy;

public:
	void init(void);
	void enemySetUp(tagEnemy* qEnemy = nullptr);

	queue<tagEnemy*>* getEnemy() { return &this->_enemy; }

	EnemyData() {}
	~EnemyData() {}
};

