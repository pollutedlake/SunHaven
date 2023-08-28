#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _logo;

	float _bgAlpha;		// 배경 알파
	float _menuAlpha;	// 배경 메뉴 알파

	bitset<10> _isDone;

	RECT _rc[3];		// 플레이 누르지 않았을 때

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

