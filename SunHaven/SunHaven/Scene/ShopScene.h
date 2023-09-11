// ±è¼ºÀÇ
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Player/Player.h"



class ShopScene : public GameNode
{

private:
	Player* _player;
	
	RECT _bg;
	RECT bgtemp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShopScene(){}
	~ShopScene(){}
};

