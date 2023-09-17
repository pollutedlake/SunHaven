// ±è¼ºÀÇ
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"
#include "../Class/Camera.h"
#include "../Class/Inventory.h"


struct shopList
{
	RECT _rc;
	int _buyGold;
	int _sellGold;
	string _name;
	RECT _buttonRc[3];
	string _grade;
	string _index;

};

class UI;

class ShopScene : public GameNode
{

private:
	Player* _player;
	Camera* _camera;

	RECT _solonRc;
	RECT _shopBg;
	RECT _shopItemBg;

	UI* _ui;
	vector<shopList> _vShopList;
	vector<shopList>::iterator _viShopList;

	Inventory* _inven;

	GImage* _moveMapImg;
	RECT _portal;
	bool _moveMap;
	bool _enterScene;
	float _clippingRaius;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void shopMold();
	void shopSlot();

	ShopScene(){}
	~ShopScene(){}
};

