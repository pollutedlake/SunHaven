#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_bgAlpha = 0.0f;
	_menuAlpha = 150.0f;

	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(0, 400 + i * 59, 290, 59);
	}

	_isDone.reset();
	_isDone.set(0, true);

	cout << MYWINSIZE_X << "\t" << MYWINSIZE_Y << endl;

	return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{
	_bgAlpha += 5.0f;
	TIMEMANAGER->update();
	if (_bgAlpha >= 255) _bgAlpha = 255;

	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_isDone.test(0))
				{

					switch (i)
					{
					case 0:
						_isDone = _isDone << 1;

						break;

					case 1:
						SCENEMANAGER->changeScene("MapTool");

						break;

					case 2:
						PostQuitMessage(0);

						break;
					}

				}

				else if (_isDone.test(1))
				{
					switch (i)
					{
					case 0:

						break;

					case 1:

						break;

					case 2:
						_isDone = _isDone >> 1;

						break;
					}

				}
			}
		}
	}
}

void TitleScene::render(void)
{
	IMAGEMANAGER->render("TITLE", getMemDC(), 0, 0);
	
	/*for (int i = 0; i < 3; i++)
	{
		DrawRectMake(getMemDC(), _rc[i]);
	}*/
	//IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 400, 0, 0, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 40, 150);

	IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 400, 0, 0, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 16, 150);

	for (int i = 0; i < 18; i++)
	{
		IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 416 + i * 8, 0, 16, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 8, 150);
	}

	IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 560, 0, 24, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 16, 150);
	

	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			IMAGEMANAGER->GPFrameRender("TITLE_BUTTON", getMemDC(),
				50, 410 + i * 59, 2.2, 2,
				IMAGEMANAGER->findGPImage("TITLE_BUTTON")->getFrameX(), IMAGEMANAGER->findGPImage("TITLE_BUTTON")->getFrameY(),
				InterpolationModeNearestNeighbor, 0);
		}
	}

	if (_isDone.test(0))
	{
		FONTMANAGER->textOut(getMemDC(), 60, 410, "한컴 말랑말랑 Bold", 35, 600, "플레이", strlen("플레이"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 60, 470, "한컴 말랑말랑 Bold", 35, 600, "맵 툴", strlen("맵 툴"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 60, 530, "한컴 말랑말랑 Bold", 35, 600, "나가기", strlen("나가기"), RGB(255, 255, 255));
	}

	else if (_isDone.test(1))
	{
		FONTMANAGER->textOut(getMemDC(), 60, 410, "한컴 말랑말랑 Bold", 35, 600, "새로운 캐릭터", strlen("새로운 캐릭터"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 60, 470, "한컴 말랑말랑 Bold", 35, 600, "캐릭터 불러오기", strlen("캐릭터 불러오기"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 60, 530, "한컴 말랑말랑 Bold", 35, 600, "뒤로", strlen("뒤로"), RGB(255, 255, 255));
	}

	IMAGEMANAGER->render("CURSOR", getMemDC(), _ptMouse.x, _ptMouse.y);
}
