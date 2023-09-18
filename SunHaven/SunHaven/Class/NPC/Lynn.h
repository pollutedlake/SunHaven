#pragma once
#include "../../FrameWork/GameNode/GameNode.h"
#include "../../FrameWork/Animation/Animation.h"

enum State
{
	IDLE,
	WALK,
	SADIDLE,
	SADWALK,
	TRAINSITIDLE,
	TRAINSIT
};

enum Direction
{
	DOWN,
	RIGHT,
	UP,
	LEFT
};

struct Action
{
	State _state;
	Direction _dir;
	bool _loop;
	float _time;
	Action(State state, Direction dir, bool loop, float time = 0.0f) : _state(state), _dir(dir), _loop(loop), _time(time) {}
};

class Lynn : public GameNode
{
private:
	GImage* _lynnWalkImage;
	GImage* _lynnIdleImage;
	GImage* _lynnBlinkImage;
	GImage* _lynnSadImage;
	GImage* _lynnTrainImage;
	GImage* _curImg;

	Animation* _lynnWalkAnim;
	Animation* _lynnBlinkAnim;
	Animation* _lynnIdleAnim;
	Animation* _lynnSadAnim;
	Animation* _lynnTrainAnim;
	Animation* _curAnim;
	
	queue<Action*> _qAction;
	Action* _curAction;
	bool _isActionFinished;

	float _actionStartTime;

	State _state;
	Direction _dir;

	RECT _rc;
	queue<pair<float, float>> _qMovePoints;
	float _speed;
	
	float _moveTime;
	float _startX, _startY;
	float _x, _y;
	pair<float, float> _moveStartPoint;
	int _actionIdx;

public:
	HRESULT init(void);
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);

	void render(HDC hdc);
	void move();
	void idle();
	void pushMovePoint(pair<float, float> movePoint);

	void setState(State state) {_state = state;}
	void setDir(Direction dir) {_dir = dir;}
	void setPos(float x, float y) {_x = x; _y = y;}
	void popAction();
	void pushAction(Action* action);

	float getX() { return _x;}
	float getY() {return _y;}
	int getActionIdx() {return _actionIdx;}

	Lynn() {}
	~Lynn() {}
};

