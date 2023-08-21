#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _logo;

	float _bgAlpha;		// ��� ����
	float _menuAlpha;	// ��� �޴� ����

	RECT _rc[3];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

