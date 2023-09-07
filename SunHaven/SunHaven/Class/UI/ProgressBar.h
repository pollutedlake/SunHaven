#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

class ProgressBar : public GameNode
{
private:
	GPImage* _progressBarTop;
	GPImage* _progressBarBottom;
	GImage* _progressBarFill;

	RECT _rc;
	int _x, _y;
	float _width;

public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentX, float maxX);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	ProgressBar() {}
	virtual ~ProgressBar() {}
};