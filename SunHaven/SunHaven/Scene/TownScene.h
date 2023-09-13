#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class TownScene : public GameNode
{
private:
	GPImage* _test;
	float _angle;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	void skillPopUp(void);
	void enemyPopUp(void);

	TownScene() {}
	~TownScene() {}
};

