#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	GImage* _logo;

	float _bgAlpha;		// ��� ����
	float _menuAlpha;	// ��� �޴� ����

	bitset<10> _isDone;

	RECT _rc[3];		// �÷��� ������ �ʾ��� ��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

