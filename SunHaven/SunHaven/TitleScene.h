#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _logo;

	float _bgAlpha;		// 배경 알파
	float _menuAlpha;	// 배경 메뉴 알파

	RECT _rc[3];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

