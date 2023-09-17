// 정성진
#include "Stdafx.h"
#include "DynusScene.h"
#include "../Class/UI/UI.h"

HRESULT DynusScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("다이너스", "./Resources/Data/Map/DynusMap.bmp", 2400, 2400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("DynusMapCollision", "./Resources/Data/Map/DynusMapCollision.bmp", 2400, 2400);
	_player = new Player;
	_player->init(CENTER_X, CENTER_Y + 200, "DynusMapCollision");
	_player->setPlayerState(DATAMANAGER->getPlayereState());

	_dynus = new Dynus;

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(1320 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(816 - WINSIZE_Y / 2);

	for (int i = 0; i < 8; i++)
	{
		_rcStar[i] = RectMake(402 * (i % 4), 402 * (i / 4), 402, 402);
	}

	_loopImg = IMAGEMANAGER->addImage("BlueStarFill", "Resources/Images/Layer/StarShader.bmp",
		402, 402);
	_offsetX = _offsetY = 0.0f;
	_em = new EnemyManager;
	_dynus->setEnemyManagerMemoryAddress(_em);
	_em->setPlayerMemoryAddress(_player);
	_dynus->setPlayerMemoryAddress(_player);
	_dynus->init();

	_ui = new UI;
	_ui->init("Dynus");
	_ui->setAdressPlayer(_player);

	wsprintf(_text, "DynusScene");
	_moveMap = true;
	_portal = RectMake(530, 750, 280, 50);
	_moveMapImg = IMAGEMANAGER->addImage("MoveMap", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_clippingRaius = 0.0f;
	_enterScene = true;
	_dialogWindow2 = IMAGEMANAGER->findImage("DialogWindow2");
	_dialogWindow1 = IMAGEMANAGER->findImage("DialogWindow1");
	FILE* fp;
	fopen_s(&fp, "DynusText.txt", "r");
	if (fp != nullptr)
	{
		for (int i = 0; i < 67; i++)
		{
			char name[256];
			fscanf_s(fp, "%[^\t]\t", name, _countof(name));
			name[strlen(name)] = '\0';
			_arrDialogs[i]._charName = name;
			fscanf_s(fp, "%d ", &_arrDialogs[i]._expression);
			fscanf_s(fp, "%d ", &_arrDialogs[i]._answerN);
			if (_arrDialogs[i]._answerN == 0)
			{
				fscanf_s(fp, "%d\n", &_arrDialogs[i]._nextDialog);
			}
			char dialog[256];
			fscanf_s(fp, "%[^\n]\n", dialog, _countof(dialog));
			dialog[strlen(dialog)] = '\0';
			_arrDialogs[i]._dialog = dialog;
			for (int j = 0; j < _arrDialogs[i]._answerN; j++)
			{
				char answer[256];
				fscanf_s(fp, "%[^\t]\t", answer, _countof(answer));
				int nextDialog;
				fscanf_s(fp, "%d\n", &nextDialog);
				answer[strlen(answer)] = '\0';
				_arrDialogs[i]._answer[j] = make_pair(answer, nextDialog);
			}
			_arrDialogs[i]._letterN = 0;
		}
		fclose(fp);
	}
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y, 0, 0);
	_dialogIdx = 0;
	_typingTime = 0.0f;
	_dialogState = DynusSceneDialog::HIDE;
	return S_OK;
}

void DynusScene::release(void)
{
	_dynus->release();
	_em->release();
	_player->release();
	SAFE_DELETE(_player);
	SAFE_DELETE(_dynus);
	SAFE_DELETE(_em);
}

void DynusScene::update(void)
{
	SOUNDMANAGER->update();
	_player->update();
	CAMERA->setPosition(_player->getPlayerPosition());
	//CAMERA->update();
	_player->worldToCamera(CAMERA->worldToCamera
	(_player->getPlayerPosition()));
	if(!_moveMap)
	{
		_dynus->update();
		if (!_dynus->getIsDie())
		{
			_em->update();
		}
		else
		{
			if(_dialogIdx == 0 && _dialogState == DynusSceneDialog::HIDE)
			{
				_dialogState = DynusSceneDialog::OPEN;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_dialogState == DynusSceneDialog::SHOW && PtInRect(&_dialogRC, _ptMouse))
				{
					bool next = false;
					if (_arrDialogs[_dialogIdx]._letterN < strlen(_arrDialogs[_dialogIdx]._dialog.c_str()))
					{
						_arrDialogs[_dialogIdx]._letterN = strlen(_arrDialogs[_dialogIdx]._dialog.c_str());
					}
					else
					{
						_dialogIdx++;
						if (_dialogIdx > 21)
						{
							_dialogState = DynusSceneDialog::CLOSE;
						}
					}
				}
			}
		}
		_player->UseToolAnim(KEYMANAGER->isStayKeyDown(VK_LBUTTON));
		collision();

		static float offsetXDirection = 1.0f;
		_offsetX += 0.5f * offsetXDirection;

		if (_offsetX >= 100.0f || _offsetX <= -100.0f)
		{
			offsetXDirection *= -1.0f;
		}
		if (PtInRect(&_portal, _player->getPlayerPosition()))
		{
			_moveMap = true;
		}
	}
	else
	{
		if (_enterScene)
		{
			_clippingRaius += TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_clippingRaius > WINSIZE_X)
			{
				_clippingRaius = WINSIZE_X;
				_enterScene = false;
				_moveMap = false;
			}
		}
		else
		{
			_clippingRaius -= TIMEMANAGER->getElapsedTime() * 1000.0f;
			if (_clippingRaius < 0)
			{
				_clippingRaius = 0.0f;
				PostQuitMessage(0);
			}
		}
	}
	updateDialog();
}

void DynusScene::render(void)
{
	for (int i = 0; i < 8; i++)
	{
		_loopImg->loopRender(getMemDC(), &_rcStar[i],
			_offsetX, _offsetY);
	}

	/*IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 0, 0, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 960, 0, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 960, 400, 250);
	IMAGEMANAGER->alphaRender("StarShader", getMemDC(), 0, 400, 250);*/
	/*IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(0), CAMERA->worldToCameraY(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(402), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(402), CAMERA->worldToCameraY(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(804), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(804), CAMERA->worldToCameraY(402), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(1206), CAMERA->worldToCameraY(0), 150);
	IMAGEMANAGER->alphaRender("BlueStarFill", getMemDC(), CAMERA->worldToCameraX(1206), CAMERA->worldToCameraY(402), 150);*/
	//IMAGEMANAGER->render("StarShader", getMemDC(), 0, 400);
	//IMAGEMANAGER->alphaRender("StarShaderTest", getMemDC(), 0, 0, 150);
	//IMAGEMANAGER->render("DynusLayer0", getMemDC(), 0, 0, 30, 95, WINSIZE_X, WINSIZE_Y);
	//IMAGEMANAGER->alphaRender("DynusLayer0", getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2, CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y, _dynus->getBgAlpha());
	_bg->alphaRender(getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2, CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y, _dynus->getBgAlpha());
	if (!_dynus->getIsDie())
	{
		_em->render();
	}
	if (_dynus->getIsPlatform())
	{
		IMAGEMANAGER->render("DynusGuardPlatformL", getMemDC(), CAMERA->worldToCameraX(65), CAMERA->worldToCameraY(CENTER_Y + 45));
		IMAGEMANAGER->render("DynusGuardPlatformR", getMemDC(), CAMERA->worldToCameraX(WINSIZE_X - 95), CAMERA->worldToCameraY(CENTER_Y + 45));
		_dynus->drawPlatform();
	}
	_player->render();
	_dynus->render();
	renderDialog();
	if(!_dynus->getIsDie())
	{
		_ui->render();
	}
	IMAGEMANAGER->findImage("Cursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	if (_moveMap)
	{
		PatBlt(_moveMapImg->getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		HBRUSH magenta = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_moveMapImg->getMemDC(), magenta);
		EllipseMakeCenter(_moveMapImg->getMemDC(), (CAMERA->worldToCameraRect(_player->getPlayerRC()).right + CAMERA->worldToCameraRect(_player->getPlayerRC()).left) / 2.0f,
			(CAMERA->worldToCameraRect(_player->getPlayerRC()).bottom + CAMERA->worldToCameraRect(_player->getPlayerRC()).top) / 2.0f, _clippingRaius, _clippingRaius);
		SelectObject(_moveMapImg->getMemDC(), oldBrush);
		DeleteObject(magenta);
		_moveMapImg->render(getMemDC());
	}
}

void DynusScene::renderDialog()
{
	_dialogRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - _dialogWindow2->getHeight() * _dialogSize / 2.0f, _dialogWindow2->getWidth() * _dialogSize, _dialogWindow2->getHeight() * _dialogSize);
	if(strcmp(_arrDialogs[_dialogIdx]._charName.c_str(), "None"))
	{
		_dialogWindow2->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow2->getWidth() * _dialogSize, _dialogWindow2->getHeight() * _dialogSize,
			0, 0, _dialogWindow2->getWidth(), _dialogWindow2->getHeight(), 240);
	}
	else
	{
		_dialogWindow1->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow1->getWidth() * _dialogSize, _dialogWindow1->getHeight() * _dialogSize,
			0, 0, _dialogWindow1->getWidth(), _dialogWindow1->getHeight(), 240);
	}
	if (_dialogState == DynusSceneDialog::SHOW)
	{
		dialog(_arrDialogs[_dialogIdx]);
	}

}

void DynusScene::dialog(DynusSceneDialog::Dialog dialog)
{
	char _text[256];
	wsprintf(_text, "Dialog%s", dialog._charName.c_str());
	RECT rc = RectMake(320, 480, _dialogRC.right - 350, 240);
	_speaker = IMAGEMANAGER->findImage(_text);
	if (_speaker != nullptr)
	{
		_speaker->frameRender(getMemDC(), _dialogRC.right - _speaker->getFrameWidth() * 0.2f, WINSIZE_Y - _speaker->getFrameHeight() * 2,
			_speaker->getFrameWidth() * 2, _speaker->getFrameHeight() * 2, dialog._expression, 0);
	}
	if (strcmp(_arrDialogs[_dialogIdx]._charName.c_str(), "None"))
	{
		_dialogWindow2->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow2->getWidth() * _dialogSize, _dialogWindow2->getHeight() * _dialogSize,
			0, 0, _dialogWindow2->getWidth(), _dialogWindow2->getHeight(), 240);
	}
	else
	{
		_dialogWindow1->alphaRender(getMemDC(), _dialogRC.left, _dialogRC.top, _dialogWindow1->getWidth() * _dialogSize, _dialogWindow1->getHeight() * _dialogSize,
			0, 0, _dialogWindow1->getWidth(), _dialogWindow1->getHeight(), 240);
	}
	if (strcmp(_arrDialogs[_dialogIdx]._charName.c_str(), "None"))
	{
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), 514, 440, "배달의민족 을지로체", 15, 100, const_cast<char*>(dialog._charName.c_str()), dialog._charName.length(), RGB(0, 0, 0));
	}
	SetTextAlign(getMemDC(), TA_LEFT);
	FONTMANAGER->drawText(getMemDC(), "배달의민족 을지로체", 20, 100, const_cast<char*>(dialog._dialog.c_str()), dialog._letterN, RGB(255, 255, 255), &rc);
	RECT answerRC[4];
	for (int i = 0; i < 4; i++)
	{
		answerRC[i] = RectMake(330, 570 + 30 * i, _dialogRC.right - 340, 30);
	}
	if (dialog._letterN == dialog._dialog.length())
	{
		if (SOUNDMANAGER->isPlaySound("E_TextScroll3"))
		{
			SOUNDMANAGER->stop("E_TextScroll3");
		}
	}
}

void DynusScene::updateDialog()
{
	switch (_dialogState)
	{
	case DynusSceneDialog::OPEN:
		_dialogSize += TIMEMANAGER->getElapsedTime() * 5.0f;
		if (_dialogSize > 2.2f)
		{
			_dialogState = DynusSceneDialog::SHOW;
		}
		break;
	case DynusSceneDialog::SHOW:
		_dialogSize = 2.2f;
		if (_arrDialogs[_dialogIdx]._letterN < strlen(_arrDialogs[_dialogIdx]._dialog.c_str()))
		{
			if (_typingTime + 0.05f < TIMEMANAGER->getWorldTime())
			{
				_typingTime = TIMEMANAGER->getWorldTime();
				_arrDialogs[_dialogIdx]._letterN++;
				if (!SOUNDMANAGER->isPlaySound("E_TextScroll3"))
				{
					SOUNDMANAGER->play("E_TextScroll3", 1.0f);
				}
			}
		}
		break;
	case DynusSceneDialog::HIDE:
		_dialogSize = 0.0f;
		break;
	case DynusSceneDialog::CLOSE:
		_dialogSize -= TIMEMANAGER->getElapsedTime() * 5.0f;
		if (_dialogSize < 0.0f)
		{
			_dialogState = DynusSceneDialog::HIDE;
		}
		break;
	}
}