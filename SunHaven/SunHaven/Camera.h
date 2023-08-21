#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
private:
	POINT _position;
	RECT _limitRC;
	int _speed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPosition() { return _position; }

	void setPosition(POINT position);
	void setLimitRight(int limitRight) { _limitRC.right = limitRight; }
	void setLimitBottom(int limitBottom) { _limitRC.bottom = limitBottom; }

	POINT worldToCamera(POINT point);
	float getXScreen(float x);
	float getYScreen(float y);

	Camera() {}
	~Camera() {}
};

