// Á¤¼ºÁø
#pragma once
#include "../GameNode/GameNode.h"
#include "../Class/Boss/Dynus.h"
#include "../Class/Enemy/EnemyManager.h"

class DynusScene : public GameNode
{
private:
	Dynus* _dynus;
	EnemyManager* _em;
	float _x, _y;
	char _text[64];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	DynusScene() {}
	~DynusScene() {}
};

