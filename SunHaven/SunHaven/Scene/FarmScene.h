// ¹Î¿ë½Ä
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"
#include "../Class/Object/ObjectManager.h"
#include "../Class/UI/ProgressBar.h"
#include "../Class/Inventory.h"

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
	GImage* _moveMapImg;
	ObjectManager* _om;
	UI* _ui;
	priority_queue<pair<GameNode*, int>, vector<pair<GameNode*, int>>, cmp> _vRenderList;
	list<pair<POINT, int>> _hitEffectList;
	list<pair<POINT, int>>::iterator _itHitEffectList;
	
	lDropItem _lDropItem;
	liDropItem _liDropItem;
	GImage* _MouseOver;
	RECT _MouseRC;

	Inventory* _inven;

	RECT _portal;
	bool _moveMap;
	bool _enterScene;
	float _clippingRaius;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void Collision(void);
	void renderDropItem();
	void renderHitEffect();
	void getDropItem();
	void moveMap();

	FarmScene() {}
	~FarmScene() {}
};

