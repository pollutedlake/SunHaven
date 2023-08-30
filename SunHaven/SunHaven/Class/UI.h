#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class Button : public GameNode
{
private:
	RECT _rc;
	GImage* _image;
	float _x, _y;
	int _width, _height;
	bool _click;
	bool _onCusor;

public:
	HRESULT init(void);
	HRESULT init(float x, float y, int width, int height, char* imageName, void(*onClick)());
	void release(void);
	void update(void);
	void render(void);

	Button();
	~Button() {}
};

