#include "Stdafx.h"
#include "IntroScene.h"

HRESULT IntroScene::init(void)
{
	_lynnMomHouse = IMAGEMANAGER->findImage("LynnMomHouse");
	_train1 = IMAGEMANAGER->findImage("Train1");
	_train2 = IMAGEMANAGER->findImage("Train2");
	_lynnMom = IMAGEMANAGER->findImage("LynnMom1");
	_catSleep = IMAGEMANAGER->findImage("CatSleep");
	for (int i = 0; i < 7; i++)
	{
		char text[64];
		wsprintf(text, "TrainPassenger0%d", i + 1);
		_trainPassengers[i] = IMAGEMANAGER->findImage(text);
	}
	_dialogWindow = IMAGEMANAGER->findImage("DialogWindow");
	_trainWindow = IMAGEMANAGER->findImage("TrainWindow1");
	_introCut[0] = IMAGEMANAGER->addImage("IntroCut1", WINSIZE_X, WINSIZE_Y);
	_introCut[1] = IMAGEMANAGER->addImage("IntroCut2", WINSIZE_X, WINSIZE_Y);
	_introCut[2] = IMAGEMANAGER->addImage("IntroCut3", WINSIZE_X, WINSIZE_Y);
	_cutIdx = 0;
	_changeCutImg = IMAGEMANAGER->addImage("TransformScene", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_cameraPos = { WINSIZE_X / 3, WINSIZE_Y / 3};
	
	_lynn = new Lynn;
	Action* action;
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
	action = new Action(SADIDLE, RIGHT, false, 0.5f);
	_lynn->pushAction(action);
	action = new Action(IDLE, UP, false, 0.5f);
	_lynn->pushAction(action);
	action = new Action(SADIDLE, DOWN, true);
	_lynn->pushAction(action);
	action = new Action(SADIDLE, DOWN, false, 2.0f);
	_lynn->pushAction(action);
	action = new Action(SADWALK, DOWN, false);
	_lynn->pushAction(action);
	action = new Action(SADWALK, RIGHT, false);
	_lynn->pushAction(action);
	action = new Action(SADIDLE, RIGHT, true);
	_lynn->pushAction(action);

	_lynn->pushMovePoint(make_pair(260, 290));
	_lynn->pushMovePoint(make_pair(260, 240));
	_lynn->pushMovePoint(make_pair(230, 240));
	_lynn->pushMovePoint(make_pair(230, 160));
	action = new Action(WALK, RIGHT, false);
	_lynn->pushAction(action);
	action = new Action(WALK, UP, false);
	_lynn->pushAction(action);
	action = new Action(IDLE, UP, true);
	_lynn->pushAction(action);
	action = new Action(WALK, LEFT, false);
	_lynn->pushAction(action);
	action = new Action(WALK, UP, false);
	_lynn->pushAction(action);
	action = new Action(TRAINSIT, RIGHT, false);
	_lynn->pushAction(action);
	action = new Action(TRAINSITIDLE, RIGHT, true);
	_lynn->pushAction(action);

	_nextActionTiming.push(2);
	_nextActionTiming.push(4);
	_nextActionTiming.push(16);
	_nextActionTiming.push(20);
	_nextActionTiming.push(21);
	_nextActionTiming.push(22);
	_nextActionTiming.push(23);
	_nextActionTiming.push(25);
	_nextActionTiming.push(28);
	_nextActionTiming.push(29);
	_nextActionTiming.push(32);
	_nextActionTiming.push(33);
	_nextActionTiming.push(37);
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
	_changeCutTime = 0.0f;
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y, 0, 0);
	_count = 0;
	_count2 = 0;

	_dialogIdx = 0;
	_typingTime = 0.0f;

	_cursorImg = IMAGEMANAGER->findImage("Cursor");
	_changeCut = false;
	_dark = false;
	_darkAlpha = 0;
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
		_time += TIMEMANAGER->getElapsedTime();
		_lynn->update();
		_cameraPos.x = _lynn->getX();
		_cameraPos.y = _lynn->getY();
		if (_time > 0.1f)
		{
			_time = 0.0f;
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
			_changeCutTime -= TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_changeCutTime < 0)
			{
				_changeCutTime = 0.0f;
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
		else if (_lynn->getActionIdx() == 8)
		{
			_dialogState = HIDE;
		}
		else if (_lynn->getActionIdx() == 9)
		{
			_dialogState = SHOW;
		}
		if (_dialogState == HIDE && _dialogIdx == 15)
		{
			_changeCutTime += TIMEMANAGER->getElapsedTime();
			if (_changeCutTime > 1.0f)
			{
				_dialogState = OPEN;
			}
		}
	}
	else if (_cutIdx == 1)
	{
		if(_changeCut)
		{
			if (_lynn->getActionIdx() == 27)
			{
				_changeCutTime -= TIMEMANAGER->getElapsedTime() * 1000.0f;
				if (_changeCutTime < 0)
				{
					_time = 0.0f;
					_changeCutTime = 0.0f;
					_lynn->setPos(100, 290);
					_lynn->popAction();
					_cutIdx++;
				}
			}
			else
			{
				_changeCutTime += TIMEMANAGER->getElapsedTime() * 1000.0f;
				if (_changeCutTime > WINSIZE_X)
				{
					_changeCut = false;
				}
				if (_dialogState == HIDE)
				{
					_dialogState = OPEN;
				}
			}
		}
		else
		{
			if (_lynn->getActionIdx() == 15)
			{
				_dialogState = HIDE;
			}
			else if (_lynn->getActionIdx() == 16)
			{
				_dialogState = SHOW;
			}
			else if (_lynn->getActionIdx() == 18)
			{
				if (_dialogState == HIDE)
				{
					_dialogState = OPEN;
				}
			}
			else if (_lynn->getActionIdx() == 19)
			{
				_dialogState = HIDE;
			}
			else if (_lynn->getActionIdx() == 20)
			{
				_dialogState = SHOW;
			}
			else if (_lynn->getActionIdx() == 23)
			{
				if (_dialogState == HIDE)
				{
					_dialogState = OPEN;
				}
			}
			else if (_lynn->getActionIdx() == 24)
			{
				if (_dialogState == SHOW)
				{
					_dialogState = HIDE;
				}
			}
			else if (_lynn->getActionIdx() == 27)
			{
				_changeCut = true;
				_changeCut = WINSIZE_X;
			}
		}
		if (_time + 0.1f < TIMEMANAGER->getWorldTime())
		{
			_count++;
			_time = TIMEMANAGER->getWorldTime();
		}
		cout << _lynn->getActionIdx() << endl;
		_lynn->update();
	}
	else if (_cutIdx == 2)
	{
		if(_changeCut)
		{
			_changeCutTime += TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_changeCutTime > WINSIZE_X)
			{
				_changeCut = false;
			}
		}
		else
		{
			if(_lynn->getActionIdx() == 28 || _lynn->getActionIdx() == 30 || _lynn->getActionIdx() == 34)
			{
				if (_dialogState == HIDE)
				{
					_dialogState = OPEN;
					if (_dialogIdx == 53)
					{
						_trainWindow = IMAGEMANAGER->findImage("TrainWindow2");
						_dark = true;
						_darkAlpha = 200;
					}
					if (_dialogIdx == 55)
					{
						_trainWindow = IMAGEMANAGER->findImage("TrainWindow1");
						_dark = false;
						_darkAlpha = 0;
					}
					if (_dialogIdx == 58)
					{
						_dark = true;
						_darkAlpha++;
						if (_darkAlpha > 255)
						{
							_darkAlpha = 255;
						}
						else
						{
							_dialogState = HIDE;
						}
					}
				}
			}
			else if (_lynn->getActionIdx() == 31)
			{
				if (_dialogState == SHOW)
				{
					_dialogState = CLOSE;
				}
			}
		}
		if (_time + 0.1f < TIMEMANAGER->getWorldTime())
		{
			_count++;
			_time = TIMEMANAGER->getWorldTime();
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
				cout << _dialogIdx << endl;
				if (_dialogIdx == 15 || _dialogIdx == 28 || _dialogIdx == 32 || _dialogIdx == 34 || _dialogIdx == 53 || _dialogIdx == 55 || _dialogIdx == 58)
				{
					if (_dialogState == SHOW)
					{
						_dialogState = CLOSE;
					}
				}
				if (checkNextActionTiming())
				{
					_lynn->popAction();
				}
				if (_dialogIdx > 23 && _cutIdx == 0)
				{
					_changeCut = true;
					_dialogState = CLOSE;
					_dialogIdx = 23;
					_changeCutTime = WINSIZE_X;
				}
				if (_dialogIdx == 59)
				{
					SCENEMANAGER->changeScene("Farm");
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
		for(int i = 0; i < 7; i++)
		{
			_trainWindow->frameRender(_introCut[1]->getMemDC(), 45 + 84 * i, 61, (_count % 51) % 10, (_count % 51) / 10);
		}
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
		if(_lynn->getActionIdx() >= 24)
		{
			IMAGEMANAGER->frameRender("RainCloud", _introCut[1]->getMemDC(), _lynn->getX() - 20, _lynn->getY() - 60, _count % (IMAGEMANAGER->findImage("RainCloud")->getMaxFrameX() + 1), 0);
		}
		_introCut[1]->render(getMemDC(), WINSIZE_X / 2 - _train1->getWidth() * 0.65f, 0, _train1->getWidth() * 1.3f, _train1->getHeight() * 1.3f, 0, 0, _train1->getWidth(), _train1->getHeight());
	}
	else if (_cutIdx == 2)
	{
		PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		for (int i = 0; i < 8; i++)
		{
			_trainWindow->frameRender(_introCut[2]->getMemDC(), 5 + 84 * i, 61, (_count % 51) % 10, (_count % 51) / 10);
		}
		_train2->render(_introCut[2]->getMemDC());
		_lynn->render(_introCut[2]->getMemDC());
		_introCut[2]->render(getMemDC(), WINSIZE_X / 2 - _train2->getWidth() * 0.65f, 0, _train2->getWidth() * 1.3f, _train2->getHeight() * 1.3f, 0, 0, _train2->getWidth(), _train2->getHeight());
		if(_dark)
		{
			IMAGEMANAGER->alphaRender("Black", getMemDC(), _darkAlpha);
		}
	}
	renderDialog();
	if (_changeCut)
	{
		PatBlt(_changeCutImg->getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		HBRUSH magenta = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_changeCutImg->getMemDC(), magenta);
		EllipseMakeCenter(_changeCutImg->getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _changeCutTime, _changeCutTime);
		SelectObject(_changeCutImg->getMemDC(), oldBrush);
		DeleteObject(magenta);
		_changeCutImg->render(getMemDC());
	}
	_cursorImg->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

void IntroScene::renderDialog()
{
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - _dialogWindow->getHeight() * _dialogSize / 2.0f, _dialogWindow->getWidth() * _dialogSize, _dialogWindow->getHeight() * _dialogSize);
	_dialogWindow->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow->getWidth() * _dialogSize, _dialogWindow->getHeight() * _dialogSize,
		0, 0, _dialogWindow->getWidth(), _dialogWindow->getHeight(), 240);
	if(_dialogState == SHOW)
	{
		dialog(_arrDialogs[_dialogIdx]);
	}

}

void IntroScene::dialog(Dialog dialog)
{
	char _text[256];
	wsprintf(_text, "Dialog%s", dialog._charName.c_str());
	RECT rc = RectMake(320, 480, _dialogRC.right - 350, 240);
	_speaker = IMAGEMANAGER->findImage(_text);
	if(_speaker != nullptr)
	{
		_speaker->frameRender(getMemDC(), _dialogRC.right - _speaker->getFrameWidth() * 0.2f, WINSIZE_Y - _speaker->getFrameHeight() * 2, 
			_speaker->getFrameWidth() * 2, _speaker->getFrameHeight() * 2, dialog._expression, 0);
	}
	_dialogWindow->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow->getWidth() * 2.2f, _dialogWindow->getHeight() * 2.2f,
		0, 0, _dialogWindow->getWidth(), _dialogWindow->getHeight(), 240);
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->textOut(getMemDC(), 514, 440, "배달의민족 을지로체", 15, 100, const_cast<char*>(dialog._charName.c_str()), dialog._charName.length(), RGB(0, 0, 0));
	SetTextAlign(getMemDC(), TA_LEFT);
	FONTMANAGER->drawText(getMemDC(), "배달의민족 을지로체", 20, 100, const_cast<char*>(dialog._dialog.c_str()), dialog._letterN, RGB(255, 255, 255), &rc);
	RECT answerRC[4];
	for(int i = 0; i < 4; i++)
	{
		answerRC[i] = RectMake(330, 570 + 30 * i, _dialogRC.right - 340, 30);
	}
	if(dialog._letterN == dialog._dialog.length())
	{
		for (int i = 0; i < dialog._answerN; i++)
		{
			if(PtInRect(&answerRC[i], _ptMouse))
			{
				IMAGEMANAGER->alphaRender("SelectAnswerBG", getMemDC(), rc.left - 6, answerRC[i].top, rc.right - rc.left + 6, answerRC[i].bottom - answerRC[i].top, 
					0, 0, IMAGEMANAGER->findImage("SelectAnswerBG")->getWidth(), IMAGEMANAGER->findImage("SelectAnswerBG")->getHeight(), 200);
				char str[256];
				wsprintf(str, "> %s", dialog._answer[i].c_str());
				FONTMANAGER->textOut(getMemDC(), answerRC[i].left, answerRC[i].top + 5, "배달의민족 을지로체", 20, 100, str, strlen(str), RGB(171, 174, 46));
			}
			else
			{
				FONTMANAGER->textOut(getMemDC(), answerRC[i].left, answerRC[i].top + 5, "배달의민족 을지로체", 20, 100, const_cast<char*>(dialog._answer[i].c_str()), dialog._answer[i].length(), RGB(123, 148, 162));
			}
		}
	}
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

bool IntroScene::checkNextActionTiming()
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
