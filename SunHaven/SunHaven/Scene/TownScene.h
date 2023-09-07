#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/Data/PlayerData.h"

class TownScene : public GameNode
{
private:

	PlayerData* _playerData;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	void skillPopUp(void);

	TownScene() {}
	~TownScene() {}
};

