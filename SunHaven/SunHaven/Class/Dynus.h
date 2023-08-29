#pragma once
//#include "Animation.h"

class Dynus
{
private:
	GImage* _dynusImg;
	//Animation* _dynusAni;

	RECT _rcDynus;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	void draw(void);

	RECT getRcDynus(void) { return _rcDynus; }

	Dynus() {}
	~Dynus() {}
};

