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
	typedef list<pair<string, POINT>> lDropItem;
	typedef list<pair<string, POINT>>::iterator liDropItem;

private:
	Player* _player;
	GImage* _bg;
	Camera* _camera;
	ObjectManager* _om;
	UI* _ui;
	priority_queue<pair<GameNode*, int>, vector<pair<GameNode*, int>>, cmp> _vRenderList;
	
	lDropItem _lDropItem;
	liDropItem _liDropItem;
	GImage* _MouseOver;
	RECT _MouseRC;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void Collision(void);
	void renderDropItem();

	FarmScene() {}
	~FarmScene() {}
};

