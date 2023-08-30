#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class Button : public GameNode
{
protected:
	function<void(int)> _onClick;

	RECT _rc;
	GImage* _image;
	float _x, _y;
	int _width, _height;
	int _frameX, _frameY;
	bool _click;
	bool _onCusor;

public:
	virtual HRESULT init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, char* str = "", COLORREF color = RGB(255, 255, 255), int fontSize = NULL, int offsetY = NULL);
	virtual HRESULT init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, bool toggle);

	virtual void buttonDown();
	virtual void buttonUp(int num);

	Button() : _x(0.0f), _y(0.0f), _width(0), _height(0), _click(false), _onCusor(false), _onClick(nullptr), _frameX(0), _frameY(0)
	{

	}
	~Button() {}
};

class NormalButton : public Button
{
private:
	char _str[64];
	COLORREF _color;
	int _fontSize;
	int _offsetY;

public:
	HRESULT init(void);
	HRESULT init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, char* str = "", COLORREF color = RGB(255, 255, 255), int fontSize = NULL, int offsetY = NULL);
	void release(void);
	void update(void);
	void render(void);

	void buttonDown();
	void buttonUp(int num);

	NormalButton();
	~NormalButton() {}
};

class ToggleButton : public Button
{
private:

public:
	HRESULT init(void);
	HRESULT init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, bool toggle);//char* str = "", COLORREF color = RGB(255, 255, 255), int fontSize = NULL, int offsetY = NULL);
	void release(void);
	void update(void);
	void render(void);

	void buttonDown();
	void buttonUp(int num);

	ToggleButton();
	~ToggleButton() {}
};