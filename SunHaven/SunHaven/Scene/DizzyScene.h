#pragma once
#include "../GameNode/GameNode.h"
#include "../Class/Boss/Dizzy.h"
#include "../../Player/Player.h"


class DizzyScene : public GameNode
{
private:
	Dizzy* _dizzy;
	Player* _player;

	char _text[64];


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);

	DizzyScene() {}
	~DizzyScene() {}
};

