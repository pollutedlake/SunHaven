#pragma once
#include "../GameNode/GameNode.h"
#include "../Class/Boss/Dizzy.h"
#include "../../Player/Player.h"

class UI;
class DizzyScene : public GameNode
{
private:
	Dizzy* _dizzy;
	GImage* _moveMapImg;
	Player* _player;

	UI* _ui;

	char _text[64];
	RECT _portal;
	bool _moveMap;
	bool _enterScene;
	float _clippingRaius;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);

	DizzyScene() {}
	~DizzyScene() {}
};

