#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/Data/PlayerData.h"
#include "../Class/Data/EnemyData.h"

class TownScene : public GameNode
{
private:
	PlayerData* _playerData;
	EnemyData* _enemyData;

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

