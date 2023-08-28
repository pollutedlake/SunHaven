#pragma once
#include "GameNode.h"

#define DEGREE_RADIAN(_deg)		(PI * (_deg) / 180.f)

class TitleScene : public GameNode
{
private:
	float _bgAlpha;		// ��� ����
	float _menuAlpha;	// ��� �޴� ����

	float _yOffset;

	bitset<10> _isDone;

	RECT _rc[3];		// �÷��� ������ �ʾ��� ��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TitleScene() {}
	~TitleScene() {}
};

