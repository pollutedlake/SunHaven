// ¹Î¿ë½Ä
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"
#include "../Class/Camera.h"
#include "../Class/Object/ObjectManager.h"

class UI;

class FarmScene : public GameNode
{
private:
	Player* _player;
	GImage* _bg;
	Camera* _camera;
	ObjectManager* _om;
	UI* _ui;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	FarmScene() {}
	~FarmScene() {}
};

