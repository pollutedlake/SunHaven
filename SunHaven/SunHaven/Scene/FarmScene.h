// �ο��
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"
#include "../Class/Camera.h"
#include "../Class/Object/ObjectManager.h"
#include "../Class/UI/ProgressBar.h"

struct cmp {
	bool operator()(pair<GameNode*, int> a, pair<GameNode*, int> b)
	{
		if (a.second > b.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class UI;

class FarmScene : public GameNode
{
private:
	Player* _player;
	GImage* _bg;
	Camera* _camera;
	ObjectManager* _om;
	UI* _ui;
	priority_queue<pair<GameNode*, int>, vector<pair<GameNode*, int>>, cmp> _vRenderList;
	ProgressBar* _progressBar;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void Collision(void);

	FarmScene() {}
	~FarmScene() {}
};

