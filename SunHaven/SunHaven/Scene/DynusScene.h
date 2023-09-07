// ������
#pragma once
#include "../GameNode/GameNode.h"
#include "../Class/Boss/Dynus.h"
#include "../Class/Enemy/Shadeclaw.h"
#include "../../Player/Player.h"
#include "../Class/Enemy/EnemyManager.h"

class DynusScene : public GameNode
{
private:
	Dynus* _dynus;
	Shadeclaw* _shadeclaw;
	Player* _player;
	EnemyManager* _em;

	char _text[64];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);

	DynusScene() {}
	~DynusScene() {}
};

