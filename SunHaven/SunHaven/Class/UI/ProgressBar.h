#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

class ProgressBar : public GameNode
{
private:
	GImage* _progressBarTop;
	GImage* _progressBarBottom;
	GImage* _progressBarFill;

	RECT _rc;
	int _x, _y;
	float _maxWidth;
	float _width;
	float _height;

public:
	HRESULT init(string barTop, string barBottom, string barFill, int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentX, float maxX);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	ProgressBar() {}
	virtual ~ProgressBar() {}
};