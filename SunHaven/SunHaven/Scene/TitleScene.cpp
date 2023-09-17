#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
    _bgAlpha = 0.0f;
    _menuAlpha = 150.0f;

    _yOffset = 0.0f;

    for (int i = 0; i < 3; i++)
    {
        _rc[i] = RectMake(0, 400 + i * 59, 290, 59);
    }

    _isDone.reset();
    _isDone.set(0, true);

    SOUNDMANAGER->play("Main_Menu_Final", 0.5f);
    //_sound = 0;
    _exPtMouse = _ptMouse;
    return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{
    _bgAlpha += 5.0f;
    if (_bgAlpha >= 255) _bgAlpha = 255;

    static float yOffsetDirection = 1.0f;
    _yOffset += 0.2f * yOffsetDirection;

    if (_yOffset >= 5.0f || _yOffset <= -5.0f)
    {
        yOffsetDirection *= -1.0f;
    }

    for (int i = 0; i < 3; i++)
    {
        if (PtInRect(&_rc[i], _ptMouse))
        {
            if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
               
                SOUNDMANAGER->play("E_titleButtonClick", 1.0f);

                if (_isDone.test(0))
                {

                    switch (i)
                    {
                    case 0:
                        _isDone = _isDone << 1;

                        break;

                    case 1:
						SOUNDMANAGER->stop("Main_Menu_Final");
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
                        SOUNDMANAGER->stop("Main_Menu_Final");
                        SCENEMANAGER->changeScene("Intro");

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

   
    buttonSound();
    

    SOUNDMANAGER->update();
}

void TitleScene::render(void)
{
    IMAGEMANAGER->render("TitleBG", getMemDC(), 0, 0, 225, 0, WINSIZE_X, WINSIZE_Y);   // 클리핑
    IMAGEMANAGER->GPFrameRender("TitleLogo", getMemDC(),
        265, 70 + _yOffset, 0.28, 0.28,
        IMAGEMANAGER->findGPImage("TitleLogo")->getFrameX(), IMAGEMANAGER->findGPImage("TitleLogo")->getFrameY(),
        InterpolationModeNearestNeighbor, 0);

    /*for (int i = 0; i < 3; i++)
    {
       DrawRectMake(getMemDC(), _rc[i]);
    }*/
    //IMAGEMANAGER->alphaRender("TITLE_MENU", getMemDC(), 0, 400, 0, 0, IMAGEMANAGER->findImage("TITLE_MENU")->getWidth(), 40, 150);

    // 메뉴 바탕 알파 클리핑
    IMAGEMANAGER->alphaRender("TitleMenu", getMemDC(), 0, 400, 0, 0, IMAGEMANAGER->findImage("TitleMenu")->getWidth(), 16, 150);

    for (int i = 0; i < 18; i++)
    {
        IMAGEMANAGER->alphaRender("TitleMenu", getMemDC(), 0, 416 + i * 8, 0, 16, IMAGEMANAGER->findImage("TitleMenu")->getWidth(), 8, 150);
    }

    IMAGEMANAGER->alphaRender("TitleMenu", getMemDC(), 0, 560, 0, 24, IMAGEMANAGER->findImage("TitleMenu")->getWidth(), 16, 150);


    for (int i = 0; i < 3; i++)
    {
        if (PtInRect(&_rc[i], _ptMouse))
        {
            
            IMAGEMANAGER->GPFrameRender("TitleButton", getMemDC(),
                50, 408 + i * 59, 2.2, 2,
                IMAGEMANAGER->findGPImage("TitleButton")->getFrameX(), IMAGEMANAGER->findGPImage("TitleButton")->getFrameY(),
                InterpolationModeNearestNeighbor, 0);
            if (!PtInRect(&_rc[i], _exPtMouse))
            {
               
            }
        }
    }
    _exPtMouse = _ptMouse;

    if (_isDone.test(0))
    {
        FONTMANAGER->textOut(getMemDC(), 60, 411, "배달의민족 을지로체", 35, 500, "플레이", strlen("플레이"), RGB(255, 255, 255));
        FONTMANAGER->textOut(getMemDC(), 60, 471, "배달의민족 을지로체", 35, 500, "맵 툴", strlen("맵 툴"), RGB(255, 255, 255));
        FONTMANAGER->textOut(getMemDC(), 60, 531, "배달의민족 을지로체", 35, 500, "나가기", strlen("나가기"), RGB(255, 255, 255));
    }

    else if (_isDone.test(1))
    {
        FONTMANAGER->textOut(getMemDC(), 60, 411, "배달의민족 을지로체", 35, 500, "새로운 캐릭터", strlen("새로운 캐릭터"), RGB(255, 255, 255));
        FONTMANAGER->textOut(getMemDC(), 60, 471, "배달의민족 을지로체", 35, 500, "캐릭터 불러오기", strlen("캐릭터 불러오기"), RGB(255, 255, 255));
        FONTMANAGER->textOut(getMemDC(), 60, 531, "배달의민족 을지로체", 35, 500, "뒤로", strlen("뒤로"), RGB(255, 255, 255));
    }

    IMAGEMANAGER->render("Cursor", getMemDC(), _ptMouse.x, _ptMouse.y);

  
}

void TitleScene::buttonSound()
{
    if (PtInRect(&_rc[0], _ptMouse) || PtInRect(&_rc[1], _ptMouse) || PtInRect(&_rc[2], _ptMouse))
    {
       
       
        _sound++;
        if (_sound == 1)
        {
            SOUNDMANAGER->play("E_titleButton", 1.0f);
        }

        if (_sound > 2)
        {
            _sound = 2;
        }

        if (_rc[0].bottom == _ptMouse.y || _rc[1].bottom == _ptMouse.y || _rc[2].bottom == _ptMouse.y)
        {
            _sound = 0;
        }

    }
    else
    {
        _sound = 0;
    }

   
  
}
