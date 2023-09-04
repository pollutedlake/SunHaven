// ¹Î¿ë½Ä
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"


class FarmScene : public GameNode
{
private:
	Player* _player;
	GImage* _bg;

	Camera* _camera;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	FarmScene() {}
	~FarmScene() {}
};

