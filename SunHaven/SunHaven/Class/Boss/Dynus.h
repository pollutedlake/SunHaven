#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../Bullets/Bullets.h"

// 1페이즈 패턴 시작 위치 갯수
#define PA1_STARTPOS_NUM_1	7
#define PA1_STARTPOS_NUM_2	4
#define PA2_STARTPOS_NUM	4 
#define PA3_STARTPOS_NUM	3 

class Dynus : public GameNode
{
private:
	GImage* _dynusImg;
	Animation* _breatheAni;
	Bullet* _bullet;

	RECT _rcDynus;

	RECT _rcPa1Start[PA1_STARTPOS_NUM_1][PA1_STARTPOS_NUM_2];


	//RECT _rcPa2Start[PA2_STARTPOS_NUM];
	//RECT _rcPa3Start[PA3_STARTPOS_NUM];

	float _x, _y;
	float _bulletFireCount;
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

	void bulletFire(void);
	bool bulletCountFire(void);

	RECT getRcDynus(void) { return _rcDynus; }

	Dynus() {}
	~Dynus() {}
};

