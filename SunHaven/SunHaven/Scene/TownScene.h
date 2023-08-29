#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class TownScene : public GameNode
{
private:
	float _frameTick;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	TownScene() {}
	~TownScene() {}
};

