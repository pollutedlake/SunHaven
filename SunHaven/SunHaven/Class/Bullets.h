#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "Enemy.h"

// ���� ǥ�� -> ���� ǥ�� ��ȯ
#define DEGREE_RADIAN(_deg)		(PI * (_deg) / 180.f)

// ��� -> ������
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

// ���� �Ѿ� (�� ������ ����� ����)
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
	void update(void);		// ����
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	Bullet(void) {}	//���� ĳ���� ���
	virtual ~Bullet() {}	// ���� �������� �� �� ��� ���� �Ҹ���
};

// ��ź
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
	void update(void);		// ����
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);

	CaseShot() {}
	~CaseShot() {}
};

// ���� �̻���
//class GuidedMissile : public GameNode
//{
//private:
//
//
//
//public:
//	HRESULT init(int bulletMax, float range);
//	void release(void);
//	void update(void);		// ����
//	void render(void);
//
//	void fire(float x, float y);
//	void draw(void);
//	void move(void);
//
//	GuidedMissile() {}
//	~GuidedMissile() {}
//};

// ��
class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;	// ���� �� �� ����
	tagBullet bullet;
	float _range;
	float _bulletMax;
	float _missileTick;


public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);		// ����
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Beam() {}
	~Beam() {}
};



