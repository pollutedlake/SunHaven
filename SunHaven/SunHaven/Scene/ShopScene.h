// ±è¼ºÀÇ
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/Inventory.h"


class ShopScene : public GameNode
{

private:
	Inventory* _temp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShopScene() {}
	~ShopScene(){}
};

