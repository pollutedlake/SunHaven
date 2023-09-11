#include "Stdafx.h"
#include "Lynn.h"

HRESULT Lynn::init(void)
{
	_lynnWalkImage = IMAGEMANAGER->findImage("LynnWalkSheet");
	_lynnIdleImage = IMAGEMANAGER->findImage("LynnBlinkSheet");

	_lynnWalkAnim = new Animation;
	_lynnWalkAnim->init(_lynnWalkImage->getWidth(),
		_lynnWalkImage->getHeight(),
		42, 52);
	_lynnWalkAnim->setFPS(4);

	_lynnIdleAnim = new Animation;
	_lynnIdleAnim->init(_lynnIdleImage->getWidth(),
		_lynnIdleImage->getHeight(),
		42, 52);
	_lynnIdleAnim->setFPS(3);

	_x = 300;
	_y = 50;
	_rc = RectMakeCenter(_x, _y, _lynnWalkImage->getFrameWidth(), _lynnWalkImage->getFrameHeight());
	_speed = 80.0f;
	return S_OK;
}

HRESULT Lynn::init(float x, float y)
{
	_lynnWalkImage = IMAGEMANAGER->findImage("LynnWalkSheet");
	_lynnBlinkImage = IMAGEMANAGER->findImage("LynnBlinkSheet");
	_lynnIdleImage = IMAGEMANAGER->findImage("LynnBreathingSheet");
	_lynnSadImage = IMAGEMANAGER->findImage("LynnSadSheet");
	_lynnTrainImage = IMAGEMANAGER->findImage("LynnTrainSheet");

	_lynnWalkAnim = new Animation;
	_lynnWalkAnim->init(_lynnWalkImage->getWidth(),
		_lynnWalkImage->getHeight(),
		42, 52);
	_lynnWalkAnim->setFPS(6);

	_lynnBlinkAnim = new Animation;
	_lynnBlinkAnim->init(_lynnBlinkImage->getWidth(),
		_lynnBlinkImage->getHeight(),
		42, 52);
	_lynnBlinkAnim->setFPS(6);

	_lynnIdleAnim = new Animation;
	_lynnIdleAnim->init(_lynnIdleImage->getWidth(),
		_lynnIdleImage->getHeight(),
		42, 52);
	_lynnIdleAnim->setFPS(6);

	_lynnSadAnim = new Animation;
	_lynnSadAnim->init(_lynnSadImage->getWidth(),
		_lynnSadImage->getHeight(),
		42, 52);
	_lynnSadAnim->setFPS(6);

	_lynnTrainAnim = new Animation;
	_lynnTrainAnim->init(_lynnTrainImage->getWidth(),
		_lynnTrainImage->getHeight(),
		50, 52);
	_lynnTrainAnim->setFPS(6);

	_actionStartTime = 0.0f;

	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _lynnWalkImage->getFrameWidth(), _lynnWalkImage->getFrameHeight());
	_speed = 80.0f;
	_actionIdx = 0;
	return S_OK;
}

void Lynn::release(void)
{
	_lynnWalkAnim->release();
	SAFE_DELETE(_lynnWalkAnim);
	_lynnBlinkAnim->release();
	SAFE_DELETE(_lynnBlinkAnim);
	_lynnIdleAnim->release();
	SAFE_DELETE(_lynnIdleAnim);
	_lynnSadAnim->release();
	SAFE_DELETE(_lynnSadAnim);
	_lynnTrainAnim->release();
	SAFE_DELETE(_lynnTrainAnim);
}

void Lynn::update(void)
{
	if(!_curAction->_loop)
	{
		if (_isActionFinished)
		{
			popAction();
		}
	}
	switch(_curAction->_state)
	{
		case WALK:
			move();
		break;
		case IDLE:
			idle();
		break;
		case SADIDLE:
			idle();
		break;
		case SADWALK:
			move();
		break;
	}
	_curAnim->frameUpdate(TIMEMANAGER->getElapsedTime());
	if (!_curAnim->isPlay())
	{
		_isActionFinished = true;
	}
	_rc = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
}

void Lynn::render(void)
{
	switch (_curAction->_state)
	{
	case WALK:
		_lynnWalkImage->aniRender(getMemDC(), _rc.left, _rc.top, _lynnWalkAnim);
		break;
	case IDLE:
		_lynnIdleImage->aniRender(getMemDC(), _rc.left, _rc.top, _lynnIdleAnim);
		break;
	}
}

void Lynn::render(HDC hdc)
{
	_curImg->aniRender(hdc, _rc.left, _rc.top, _curAnim);
}

void Lynn::move()
{
	_x = (_qMovePoints.front().first * (TIMEMANAGER->getWorldTime() - _actionStartTime) + _startX * (_moveTime - (TIMEMANAGER->getWorldTime() - _actionStartTime))) / _moveTime;
	_y = (_qMovePoints.front().second * (TIMEMANAGER->getWorldTime() - _actionStartTime) + _startY * (_moveTime - (TIMEMANAGER->getWorldTime() - _actionStartTime))) / _moveTime;
	if (TIMEMANAGER->getWorldTime() - _actionStartTime >= _moveTime)
	{
		_x = _qMovePoints.front().first;
		_y = _qMovePoints.front().second;
		_qMovePoints.pop();
		_isActionFinished = true;
	}
}

void Lynn::idle()
{
	if (_lynnIdleAnim->getNowPlayIdx() % 6 == 5 && !_lynnIdleAnim->isPlay())
	{
		if(_dir != UP)
		{
			_curAnim->AniStop();
			_curAnim = _lynnBlinkAnim;
			_curImg = _lynnBlinkImage;
			_curAnim->setPlayFrame(3 * _dir, 3 * (_dir + 1) - 1, false, false);
			_curAnim->AniStart();
		}
	}

	if (_lynnBlinkAnim->getNowPlayIdx() % 3 > 1 && !_lynnBlinkAnim->isPlay())
	{
		_curAnim->AniStop();
		_curAnim = _lynnIdleAnim;
		_curImg = _lynnIdleImage;
		_curAnim->setPlayFrame(6 * _dir, 6 * (_dir + 1) - 1, false, false);
		_curAnim->AniStart();
	}

	if (_actionStartTime + _curAction->_time < TIMEMANAGER->getWorldTime())
	{
		_isActionFinished = true;
	}
}

void Lynn::pushMovePoint(pair<float, float> movePoint)
{
	_qMovePoints.push(movePoint);
}

void Lynn::popAction()
{
	if (_qAction.empty())
	{
		return;
	}
	if(_curAction != nullptr)
	{
		_curAnim->AniStop();
		SAFE_DELETE(_curAction);
	}
	_curAction = _qAction.front();
	_actionIdx++;
	_qAction.pop();
	_actionStartTime = TIMEMANAGER->getWorldTime();
	switch (_curAction->_state)
	{
	case IDLE:
		_curImg = _lynnIdleImage;
		_curAnim = _lynnIdleAnim;
		setDir(_curAction->_dir);
		if (_dir == UP)
		{
			_curAnim->setPlayFrame(6 * _dir, 6 * (_dir + 1) - 1, false, true);
		}
		else
		{
			_curAnim->setPlayFrame(6 * _dir, 6 * (_dir + 1) - 1, false, false);
		}
	break;
	case WALK:
		_curImg = _lynnWalkImage;
		_curAnim = _lynnWalkAnim;
		_startX = _x;
		_startY = _y;
		_moveTime = getDistance(_startX, _startY, _qMovePoints.front().first, _qMovePoints.front().second) / _speed;
		setDir(_curAction->_dir);
		_curAnim->setPlayFrame(5 * _dir, 5 * (_dir + 1) - 1, false, true);
	break;
	case SADIDLE:
		_curImg = _lynnSadImage;
		_curAnim = _lynnSadAnim;
		setDir(_curAction->_dir);
		_curAnim->setPlayFrame(16 + 6 * _dir, 16 + 6 * (_dir + 1) - 1, false, true);
		break;
	case SADWALK:
		_curImg = _lynnSadImage;
		_curAnim = _lynnSadAnim;
		_startX = _x;
		_startY = _y;
		_moveTime = getDistance(_startX, _startY, _qMovePoints.front().first, _qMovePoints.front().second) / _speed;
		setDir(_curAction->_dir);
		_curAnim->setPlayFrame(4 * _dir, 4 * (_dir + 1) - 1, false, true);
		break;
	case TRAINSIT:
		_curImg = _lynnTrainImage;
		_curAnim = _lynnTrainAnim;
		_curAnim->setPlayFrame(0, 14, false, false);
		break;
	case TRAINSITIDLE:
		_curImg = _lynnTrainImage;
		_curAnim = _lynnTrainAnim;
		_curAnim->setPlayFrame(15, 20, false, true);
		break;
	}
	_isActionFinished = false;
	_curAnim->AniStart();
}

void Lynn::pushAction(Action* action)
{
	_qAction.push(action);
	if (_curAction == nullptr) 
	{ 
		popAction();
	}
}
