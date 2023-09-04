#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../FrameWork/Animation/Animation.h"

class Player : public GameNode
{
private:
	GImage* _playerImage;
	Animation* _playerMoveAnim;
	RECT _playerRC;

	float _x, _y;

public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);

	void UseTool();
	void UseFishingLod();
	void UseSword();
	void UseCrossBow();

	POINT getPlayerPosition() { return PointMake((int)_x, (int)_y); }
	void setPlayerPosition(POINT position);

	Player() {}
	~Player() {}
};