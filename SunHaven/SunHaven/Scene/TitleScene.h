// 정성진
#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class TitleScene : public GameNode
{
private:
	float _bgAlpha;		// 배경 알파
	float _menuAlpha;	// 배경 메뉴 알파
	float _yOffset;

	float _FrameTick;

	bitset<10> _isDone;

	RECT _rc[3];		// 플레이 누르지 않았을 때

	int _sound;

	POINT _exPtMouse;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void buttonSound();

	TitleScene() {}
	~TitleScene() {}
};

