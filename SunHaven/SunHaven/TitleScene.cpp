#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_bgAlpha = 0.0f;
	_menuAlpha = 150.0f;

	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(0, 400 + i * 53, 290, 70);
	}
	cout << MYWINSIZE_X << "\t" << MYWINSIZE_Y << endl;
	return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{
	_bgAlpha += 5.0f;

	if (_bgAlpha >= 255) _bgAlpha = 255;
}

void TitleScene::render(void)
{
	IMAGEMANAGER->alphaRender("TITLE", getMemDC(), 0, 0, _bgAlpha);

	/*for (int i = 0; i < 3; i++)
	{
		DrawRectMake(getMemDC(), _rc[i]);
	}*/
	//IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 400, 0, 0, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 40, 150);

	IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 400, 0, 0, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 16, 150);

	for (int i = 0; i < 20; i++)
	{
		IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 416 + i * 8, 0, 16, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 8, 150);
	}

	IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 576, 0, 24, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 16, 150);

	FONTMANAGER->textOut(getMemDC(), 60, 410, "ÇÑÄÄ ¸»¶û¸»¶û Bold", 35, 500, "ÇÃ·¹ÀÌ", strlen("ÇÃ·¹ÀÌ"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), 60, 470, "ÇÑÄÄ ¸»¶û¸»¶û Bold", 35, 500, "¸Ê Åø", strlen("¸Ê Åø"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), 60, 530, "ÇÑÄÄ ¸»¶û¸»¶û Bold", 35, 500, "³ª°¡±â", strlen("³ª°¡±â"), RGB(255, 255, 255));

}
