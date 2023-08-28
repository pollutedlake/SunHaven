#pragma once
#include "GameNode.h"

#define DEGREE_RADIAN(_deg)		(PI * (_deg) / 180.f)

class TitleScene : public GameNode
{
private:
	float _bgAlpha;		// 배경 알파
	float _menuAlpha;	// 배경 메뉴 알파

	float _yOffset;

	bitset<10> _isDone;

	RECT _rc[3];		// 플레이 누르지 않았을 때

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TitleScene() {}
	~TitleScene() {}
};

