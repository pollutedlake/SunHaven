#include "Stdafx.h"
#include "IntroScene.h"

HRESULT IntroScene::init(void)
{
	_lynnMomHouse = IMAGEMANAGER->findImage("LynnMomHouse");
	_train1 = IMAGEMANAGER->findImage("Train1");
	_lynnMom = IMAGEMANAGER->findImage("LynnMom1");
	_catSleep = IMAGEMANAGER->findImage("CatSleep");
	for (int i = 0; i < 7; i++)
	{
		char text[64];
		wsprintf(text, "TrainPassenger0%d", i + 1);
		_trainPassengers[i] = IMAGEMANAGER->findImage(text);
	}
	_dialogWindow = IMAGEMANAGER->findImage("DialogWindow");
	_introCut[0] = IMAGEMANAGER->addImage("IntroCut1", WINSIZE_X, WINSIZE_Y);
	_introCut[1] = IMAGEMANAGER->addImage("IntroCut2", WINSIZE_X, WINSIZE_Y);
	_cutIdx = 0;
	_changeCutImg = IMAGEMANAGER->addImage("TransformScene", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_cameraPos = { WINSIZE_X / 3, WINSIZE_Y / 3};
	
	_lynn = new Lynn;
	Action* action;
	//if(_cutIdx == 0)
	//{
		_lynn->init(440, 90);
		_lynn->pushMovePoint(make_pair(440, 200));
		_lynn->pushMovePoint(make_pair(400, 200));
		_lynn->pushMovePoint(make_pair(400, 350));
		_lynn->pushMovePoint(make_pair(480, 350));
		action = new Action(IDLE, UP, false, 2.0f);
		_lynn->pushAction(action);
		action = new Action(WALK, DOWN, false);
		_lynn->pushAction(action);
		action = new Action(WALK, LEFT, false);
		_lynn->pushAction(action);
		action = new Action(WALK, DOWN, false);
		_lynn->pushAction(action);
		action = new Action(IDLE, RIGHT, true);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, DOWN, true);
		_lynn->pushAction(action);
		action = new Action(IDLE, RIGHT, true);
		_lynn->pushAction(action);
		action = new Action(WALK, RIGHT, false);
		_lynn->pushAction(action);
		action = new Action(IDLE, RIGHT, true);
		_lynn->pushAction(action);
		action = new Action(IDLE, DOWN, true);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, DOWN, true);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, RIGHT, true);
		_lynn->pushAction(action);
		action = new Action(IDLE, RIGHT, true);
		_lynn->pushAction(action);
	//}
	//else if (_cutIdx == 1)
	//{
	//	_lynn->init(220, 240);
		_lynn->pushMovePoint(make_pair(380, 240));
		_lynn->pushMovePoint(make_pair(530, 240));
		_lynn->pushMovePoint(make_pair(530, 290));
		_lynn->pushMovePoint(make_pair(660, 290));
		action = new Action(IDLE, RIGHT, true);
		_lynn->pushAction(action);
		action = new Action(WALK, RIGHT, false);
		_lynn->pushAction(action);
		action = new Action(IDLE, UP, true);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, RIGHT, false, 1.0f);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, DOWN, true);
		_lynn->pushAction(action);
		action = new Action(SADWALK, RIGHT, false);
		_lynn->pushAction(action);
		action = new Action(IDLE, UP, true);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, RIGHT, false, 1.0f);
		_lynn->pushAction(action);
		action = new Action(IDLE, UP, false, 1.0f);
		_lynn->pushAction(action);
		action = new Action(SADIDLE, DOWN, true);
		_lynn->pushAction(action);
		action = new Action(SADWALK, DOWN, false);
		_lynn->pushAction(action);
		action = new Action(SADWALK, RIGHT, false);
		_lynn->pushAction(action);
	//}
	_nextActionTiming.push(2);
	_nextActionTiming.push(4);
	_nextActionTiming.push(15);
	_nextActionTiming.push(20);
	_nextActionTiming.push(21);
	_nextActionTiming.push(22);
	_nextActionTiming.push(23);
	_nextActionTiming.push(25);
	_nextActionTiming.push(28);
	_nextActionTiming.push(29);
	_nextActionTiming.push(32);
	_nextActionTiming.push(33);
	FILE* fp;
	fopen_s(&fp, "IntroText.txt", "r");
	if (fp != nullptr)
	{
		for (int i = 0; i < 59; i++)
		{
			char name[256];
			fscanf_s(fp, "%[^\t]\t", name, _countof(name));
			name[strlen(name)] = '\0';
			_arrDialogs[i]._charName = name;
			fscanf_s(fp, "%d ", &_arrDialogs[i]._expression);
			fscanf_s(fp, "%d\n", &_arrDialogs[i]._answerN);
			char dialog[256];
			fscanf_s(fp, "%[^\n]\n", dialog, _countof(dialog));
			dialog[strlen(dialog)] = '\0';
			_arrDialogs[i]._dialog = dialog;
			for (int j = 0; j < _arrDialogs[i]._answerN; j++)
			{
				char answer[256];
				fscanf_s(fp, "%[^\n]\n", answer, _countof(answer));
				answer[strlen(answer)] = '\0';
				_arrDialogs[i]._answer[j] = answer;
			}
			_arrDialogs[i]._letterN = 0;
		}
		fclose(fp);
	}

	_time = 0.0f;
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y, 0, 0);
	_lynnMomTime = 0.0f;
	_count = 0;
	_count2 = 0;

	_dialogIdx = 0;
	_typingTime = 0.0f;

	_cursorImg = IMAGEMANAGER->findImage("Cursor");
	_changeCut = false;
	_dialogState = HIDE;
	return S_OK;
}

void IntroScene::release(void)
{
	_lynn->release();
	SAFE_DELETE(_lynn);
}

void IntroScene::update(void)
{
	if(_cutIdx == 0)
	{
		_lynnMomTime += TIMEMANAGER->getElapsedTime();
		_lynn->update();
		_cameraPos.x = _lynn->getX();
		_cameraPos.y = _lynn->getY();
		if (_lynnMomTime > 0.1f)
		{
			_lynnMomTime = 0.0f;
			_count++;
			if (_count2 < 3)
			{
				if(_count > 8)
				{
					_count = 0;
					_count2++;
				}
			}
			else
			{
				if (_count > _lynnMom->getMaxFrameX())
				{
					_count = 0;
					_count2 = 0;
				}
			}
		}
		if (_changeCut)
		{
			_time -= TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_time < 0)
			{
				_time = 0.0f;
				_lynn->setPos(220, 240);
				_lynn->popAction();
				_dialogIdx++;
				_cutIdx++;
			}
		}
		if (_lynn->getActionIdx() == 5)
		{
			if (_dialogState == HIDE)
			{
				_dialogState = OPEN;
			}
		}
	}
	else if (_cutIdx == 1)
	{
		if(_changeCut)
		{
			_time += TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_time > WINSIZE_X)
			{
				_changeCut = false;
				_time = 0;
			}
			if (_dialogState == HIDE)
			{
				_dialogState = OPEN;
			}
		}
		else
		{
			if (_time + 0.2f < TIMEMANAGER->getWorldTime())
			{
				_count++;
				_time = TIMEMANAGER->getWorldTime();
			}
		}
		_lynn->update();
	}
	updateDialog();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_dialogState == SHOW)
		{
			if (_arrDialogs[_dialogIdx]._letterN < strlen(_arrDialogs[_dialogIdx]._dialog.c_str()))
			{
				_arrDialogs[_dialogIdx]._letterN = strlen(_arrDialogs[_dialogIdx]._dialog.c_str());
			}
			else
			{
				_dialogIdx++;
				if (unName())
				{
					_lynn->popAction();
				}
				if (_dialogIdx > 23 && _cutIdx == 0)
				{
					_changeCut = true;
					_dialogState = CLOSE;
					_dialogIdx = 23;
					_time = WINSIZE_X;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Farm");
	}
}

void IntroScene::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	if(_cutIdx == 0)
	{
		_lynnMomHouse->render(_introCut[0]->getMemDC());
		_lynn->render(_introCut[0]->getMemDC());
		_lynnMom->frameRender(_introCut[0]->getMemDC(), 500, 320, _count, 0);
		_introCut[0]->render(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, _cameraPos.x - WINSIZE_X / 3, _cameraPos.y - WINSIZE_Y / 3,
			WINSIZE_X * 2 / 3, WINSIZE_Y * 2 / 3);
	}
	else if (_cutIdx == 1)
	{
		PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		_train1->render(_introCut[1]->getMemDC());
		_trainPassengers[0]->frameRender(_introCut[1]->getMemDC(), 190, 140, _count % 6, 0);
		_trainPassengers[1]->frameRender(_introCut[1]->getMemDC(), 323, 140, _count % (_trainPassengers[1]->getMaxFrameX() + 1), 0);
		_trainPassengers[2]->frameRender(_introCut[1]->getMemDC(), 475, 160, _count % (_trainPassengers[2]->getMaxFrameX() + 1), 0);
		_trainPassengers[3]->frameRender(_introCut[1]->getMemDC(), 323, 175, _count % (_trainPassengers[3]->getMaxFrameX() + 1), 0);
		_trainPassengers[4]->frameRender(_introCut[1]->getMemDC(), 138, 183, _count % (_trainPassengers[4]->getMaxFrameX() + 1), 0);
		_trainPassengers[5]->frameRender(_introCut[1]->getMemDC(), 405, 180, _count % (_trainPassengers[5]->getMaxFrameX() + 1), 0);
		_trainPassengers[6]->frameRender(_introCut[1]->getMemDC(), 215, 180, _count % (_trainPassengers[6]->getMaxFrameX() + 1), 0);
		_catSleep->frameRender(_introCut[1]->getMemDC(), 60, 195, _count % (_catSleep->getMaxFrameX() + 1), 0);
		_lynn->render(_introCut[1]->getMemDC());
		_introCut[1]->render(getMemDC(), WINSIZE_X / 2 - _train1->getWidth() * 0.65f, 0, _train1->getWidth() * 1.3f, _train1->getHeight() * 1.3f, 0, 0, _train1->getWidth(), _train1->getHeight());
	}
	if (_changeCut)
	{
		PatBlt(_changeCutImg->getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		HBRUSH magenta = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_changeCutImg->getMemDC(), magenta);
		EllipseMakeCenter(_changeCutImg->getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _time, _time);
		SelectObject(_changeCutImg->getMemDC(), oldBrush);
		DeleteObject(magenta);
		_changeCutImg->render(getMemDC());
	}
	renderDialog();
	_cursorImg->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

void IntroScene::renderDialog()
{
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - _dialogWindow->getHeight() * _dialogSize / 2.0f, _dialogWindow->getWidth() * _dialogSize, _dialogWindow->getHeight() * _dialogSize);
	_dialogWindow->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow->getWidth() * _dialogSize, _dialogWindow->getHeight() * _dialogSize,
		0, 0, _dialogWindow->getWidth(), _dialogWindow->getHeight(), 240);
	if(_dialogState == SHOW)
	{
		dialog(_arrDialogs[_dialogIdx]._charName, _arrDialogs[_dialogIdx]._dialog, _arrDialogs[_dialogIdx]._letterN, _arrDialogs[_dialogIdx]._expression);
	}

}

void IntroScene::dialog(string charName, string printString, int length, int expression)
{
	char _text[256];
	wsprintf(_text, "Dialog%s", charName.c_str());
	RECT rc = RectMake(320, 480, _dialogRC.right - 350, 480);
	_speaker = IMAGEMANAGER->findImage(_text);
	if(_speaker != nullptr)
	{
		_speaker->frameRender(getMemDC(), _dialogRC.right - _speaker->getFrameWidth() * 0.2f, WINSIZE_Y - _speaker->getFrameHeight() * 2, 
			_speaker->getFrameWidth() * 2, _speaker->getFrameHeight() * 2, expression, 0);
	}
	_dialogWindow->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow->getWidth() * 2.2f, _dialogWindow->getHeight() * 2.2f,
		0, 0, _dialogWindow->getWidth(), _dialogWindow->getHeight(), 240);
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->textOut(getMemDC(), 514, 440, "배달의민족 을지로체", 15, 100, const_cast<char*>(charName.c_str()), charName.length(), RGB(0, 0, 0));
	SetTextAlign(getMemDC(), TA_LEFT);
	FONTMANAGER->drawText(getMemDC(), "배달의민족 을지로체", 20, 100, const_cast<char*>(printString.c_str()), length, RGB(255, 255, 255), &rc);
}

void IntroScene::updateDialog()
{
	switch (_dialogState)
	{
	case OPEN:
		_dialogSize += TIMEMANAGER->getElapsedTime() * 5.0f;
		if (_dialogSize > 2.2f)
		{
			_dialogState = SHOW;
		}
	break;
	case SHOW:
		_dialogSize = 2.2f;
		if (_typingTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			_typingTime = TIMEMANAGER->getWorldTime();
			if (_arrDialogs[_dialogIdx]._letterN < strlen(_arrDialogs[_dialogIdx]._dialog.c_str()))
			{
				_arrDialogs[_dialogIdx]._letterN++;
			}
		}
	break;
	case HIDE:
		_dialogSize = 0.0f;
	break;
	case CLOSE:
		_dialogSize -= TIMEMANAGER->getElapsedTime() * 5.0f;
		if (_dialogSize < 0.0f)
		{
			_dialogState = HIDE;
		}
	break;
	}
}

bool IntroScene::unName()
{
	if (_dialogIdx == _nextActionTiming.front())
	{
		if(_nextActionTiming.size() != 1)
		{
			_nextActionTiming.pop();
		}
		return true;
	}
	return false;
}
