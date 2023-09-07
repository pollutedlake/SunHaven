// ±è¼ºÀÇ
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/Inventory.h"
#include "../Class/Data/ItemData.h"
#include "../Class/Data/QuestData.h"


class ShopScene : public GameNode
{

private:
	Inventory* _temp;

	ItemData* _itemData;
	QuestData* _questData;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void itemPopUp(void);
	void questPopUp();


	ShopScene() {}
	~ShopScene(){}
};

