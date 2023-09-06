#pragma once
#include "../FrameWork/GameNode/GameNode.h"

struct Button
{
	function<void(int)> _onClick;

	RECT _rc;
	GImage* _image;
	float _x, _y;
	int _width, _height;
	int _frameX, _frameY;
	bool _click;
	bool _onCusor;
};

class NormalButton : public GameNode
{
private:
	char _str[64];
	COLORREF _color;
	int _fontSize;
	int _offsetY;
	Button _button;

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

class ToggleButton : public GameNode
{
private:
	Button _button;

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

class RadioButton : public GameNode
{
private:
	vector<Button*> _vButtons;
	vector<Button*>::iterator _viButtons;
	vector<char*> _str;
	COLORREF _color;
	int _fontSize;
	int _offsetY;

public:
	HRESULT init(void);
	HRESULT init(int buttonN, float x[], float y[], int width[], int height[], char* imageName, function<void(int)> onClick[], char* str[], COLORREF color = RGB(255, 255, 255), int fontSize = NULL, 
		int offsetY = NULL);
	void release(void);
	void update(void);
	void render(void);

	void buttonDown();
	void buttonUp(int num);

	RadioButton();
	~RadioButton() {}
};

class UI : public GameNode
{
	string _sceneName;
	GImage* _clock;
	GImage* _cursor;

public:
	HRESULT init(void);
	HRESULT init(string sceneName);
	void release(void);
	void update(void);
	void render(void);

	UI() {}
	~UI() {}
};