#pragma once
#include "../SunHaven/FrameWork/GameNode/GameNode.h"

class DataScene : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	DataScene() {}
	~DataScene() {}
};

