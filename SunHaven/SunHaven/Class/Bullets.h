#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "Enemy.h"

// 각도 표기 -> 라디안 표기 변환
#define DEGREE_RADIAN(_deg)		(PI * (_deg) / 180.f)

// 기능 -> 묶었다
struct tagBullet
{
	GImage* img;
	GImage* effectImg;
	//bitset<32> isEffect;
	bool isEffect;
	RECT rc;
	int radius;
	int count;
	int effectCount;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
};

// 공용 총알 (쏠 때마다 만들고 삭제)
class Bullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _bulletMax;
	float _range;
	float _missileTick;


public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);		// 갱신
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	Bullet(void) {}	//차후 캐스팅 대비
	virtual ~Bullet() {}	// 언제 지워질지 알 수 없어서 가상 소멸자
};

// 산탄
class CaseShot : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _bulletMax;
	float _missileTick;


public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);		// 갱신
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);

	CaseShot() {}
	~CaseShot() {}
};

// 유도 미사일
//class GuidedMissile : public GameNode
//{
//private:
//
//
//
//public:
//	HRESULT init(int bulletMax, float range);
//	void release(void);
//	void update(void);		// 갱신
//	void render(void);
//
//	void fire(float x, float y);
//	void draw(void);
//	void move(void);
//
//	GuidedMissile() {}
//	~GuidedMissile() {}
//};

// 빔
class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;	// 협업 시 재 정의
	tagBullet bullet;
	float _range;
	float _bulletMax;
	float _missileTick;


public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);		// 갱신
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Beam() {}
	~Beam() {}
};



