#pragma once
#include "../FrameWork/SingletonBase/SingletonBase.h"

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

	RECT worldToCameraRect(RECT rc);
	POINT worldToCamera(POINT point);
	POINT cameraToWorld(POINT point);
	float cameraToWorldX(float x);
	float cameraToWorldY(float y);
	float worldToCameraX(float x);
	float worldToCameraY(float y);

	Camera() {}
	~Camera() {}
};

