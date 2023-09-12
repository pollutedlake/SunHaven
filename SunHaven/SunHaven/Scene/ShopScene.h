// ±è¼ºÀÇ
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"


//class Inventory;

struct shopList
{
	RECT _rc;
	int _buyGold;
	int _sellGold;
	string _name;
	RECT _buttonRc[3];

};

class ShopScene : public GameNode
{

private:
	Player* _player;
	//ItemData* _ID;
	
	RECT _solonRc;
	RECT _shopBg;
	RECT _shopItemBg;
	

	vector<shopList> _vShopList;
	vector<shopList>::iterator _viShopList;

	/*vector<tagWeapon*> _vWeapon;
	vector<tagWeapon*>::iterator _viWeapon;

	vector<tagAccessory*> _vAccessory;
	vector<tagAccessory*>::iterator _viAccessory;

	vector<tagConsumable*> _vConsumable;
	vector<tagConsumable*>::iterator _viConsumable;*/

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

