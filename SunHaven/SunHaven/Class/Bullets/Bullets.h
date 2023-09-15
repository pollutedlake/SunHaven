#pragma once
#include "../GameNode/GameNode.h"
#include "../Enemy/Enemy.h"

#define GEM_TYPE 5

struct tagBullet
{
	GImage* img;
	GPImage* pImg;
	RECT rc;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
	bool isUpDown;
	bool isLeft;
	bool isUp;
};

// 다이너스 탄알
class Bullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _bulletMax;
	float _range;

	float _spawnTime;
	float _spawnWorldTime;

	bool _isSpawn;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);
	bool spawningTime(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	Bullet(void) {}	
	virtual ~Bullet() {}
};

// 다이너스 빔
class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;

	float _range;
	float _bulletMax;

	bool _isLeft;

	int _currentFrameX;
	int _currentFrameY;

	float _worldTimeCount;

	int _index;

	float _sourX;
	float _sourX2;
	float _sourX3;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float speed);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Beam() {}
	~Beam() {}
};

// 디지 메테오
class Meteor : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	Meteor() {}
	virtual ~Meteor() {}
};

// 디지 잼
class Gems : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _bulletMax;
	float _range;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Gems() {}
	virtual ~Gems() {}
};


// 파이어볼
class Fireball : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;
	//tagBullet bullet;
	float _range;
	float _bulletMax;

	int _currentFrameX;
	int _currentFrameY;

	bool _isUpDown;

	float _worldTimeCount;

	int _index;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(float x, float y);
	void render(void);

	void fire(float x, float y, bool isLeft);
	void fireUpDown(float x, float y, bool isUp);
	void draw(void);
	void move(float x, float y);
	void RemoveBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Fireball() {}
	~Fireball() {}
};

class EnemyFireBall : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _bulletMax;
	float _range;

	int _currentFrameX;
	int _currentFrameY;

	float _worldTimeCount;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	EnemyFireBall(void) {}
	virtual ~EnemyFireBall() {}
};