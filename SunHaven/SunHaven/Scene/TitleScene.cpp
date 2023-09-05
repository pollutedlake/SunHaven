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

    cout << MYWINSIZE_X << "\t" << MYWINSIZE_Y << endl;

    SOUNDMANAGER->play("Main_Menu_Final", 1.0f);
    _sound = false;
    
    return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{
    _bgAlpha += 5.0f;
    if (_bgAlpha >= 255) _bgAlpha = 255;

    // _yOffset 값에 따라 이미지를 위아래로 움직이도록 설정
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
            _sound = true;
            //SOUNDMANAGER->play("E_titleButton", 1.0f);

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
                        //SCENEMANAGER->changeScene("DynusScene");

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
        else
        {
            _sound = false;
        }
       
    }

    if (_sound)
    {
        SOUNDMANAGER->play("E_titleButton", 1.0f);
    }

    SOUNDMANAGER->update();
}

void TitleScene::render(void)
{
    IMAGEMANAGER->render("TitleBG", getMemDC(), 0, 0, 225, 0, MYWINSIZE_X, MYWINSIZE_Y);   // 클리핑
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
        }
    }

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