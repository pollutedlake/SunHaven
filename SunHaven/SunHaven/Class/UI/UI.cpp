#include "Stdafx.h"
#include "UI.h"

HRESULT UI::init(void)
{
	return S_OK;
}

HRESULT UI::init(string sceneName)
{
	_sceneName = sceneName;
	if (sceneName == "Farm")
	{
		_clock = IMAGEMANAGER->findImage("ClockUI");
		_cursor = IMAGEMANAGER->findImage("Cursor");
		_dateBar = IMAGEMANAGER->findGPImage("DateBar");
		_timeBar = IMAGEMANAGER->findGPImage("TimeBar");
		_upperRightBar = IMAGEMANAGER->findGPImage("UpperRightBar");
		_goldIcon = IMAGEMANAGER->findImage("GoldIcon");
		_ticketIcon = IMAGEMANAGER->findImage("TicketIcon");
		_orbIcon = IMAGEMANAGER->findImage("OrbIcon");
		_fishingNetIcon = IMAGEMANAGER->findImage("FishingNetIcon");
		_barnAnimalsIcon = IMAGEMANAGER->findImage("BarnAnimalsIcon");
		_skillTreeIcon = IMAGEMANAGER->findImage("SkillTreeIcon");
		_questBookIcon = IMAGEMANAGER->findImage("QuestBookIcon");
		for (int i = 0; i < 10; i++)
		{
			_shortcutItemRC[i] = RectMake(WINSIZE_X / 2 - 176 + 36 * i, WINSIZE_Y - 80, 32, 32);
		}
	}
	return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{
	if (_sceneName == "Title")
	{
		
	}
	else if (_sceneName == "Farm")
	{
		updateUIWindow();
	}
}

void UI::render(void)
{
	if (_sceneName == "Farm")
	{
		_clock->render(getMemDC(), 20, 20, _clock->getWidth() * 1.5f, _clock->getHeight() * 1.5f, 0, 0, _clock->getWidth(), _clock->getHeight());
		_cursor->render(getMemDC(), _ptMouse.x, _ptMouse.y);
		_dateBar->GPFrameRender(getMemDC(), 130, 20, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		_dateBar->GPFrameRender(getMemDC(), 130, 55, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		_timeBar->GPFrameRender(getMemDC(), 130, 95, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		_upperRightBar->GPFrameRender(getMemDC(), WINSIZE_X - 666, 0, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		FONTMANAGER->textOut(getMemDC(), 135, 25,"����ǹ��� ������ü", 20, 100, "�� 1����", strlen("�� 1����"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 135, 60,"����ǹ��� ������ü", 20, 100, "�Ͽ��� 1��", strlen("�Ͽ��� 1��"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 135, 100,"����ǹ��� ������ü", 20, 100, "06:00AM", strlen("06:00AM"), RGB(255, 255, 255));
		_goldIcon->render(getMemDC(), WINSIZE_X - 300, 8, _goldIcon->getWidth() * 1.5f, _goldIcon->getHeight() * 1.5f, 0, 0, _goldIcon->getWidth(), _goldIcon->getHeight());
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 280, 8, "����ǹ��� ������ü", 14, 100, "1,669", strlen("1,669"), RGB(255, 255, 255));
		_orbIcon->render(getMemDC(), WINSIZE_X - 200, 8, _orbIcon->getWidth() * 1.5f, _orbIcon->getHeight() * 1.5f, 0, 0, _orbIcon->getWidth(), _orbIcon->getHeight());
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 180, 8, "����ǹ��� ������ü", 14, 100, "8", strlen("8"), RGB(255, 255, 255));
		_ticketIcon->render(getMemDC(), WINSIZE_X - 100, 4);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 75, 8, "����ǹ��� ������ü", 14, 100, "13", strlen("13"), RGB(255, 255, 255));
		_fishingNetIcon->render(getMemDC(), WINSIZE_X - 400, 4);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 375, 8, "����ǹ��� ������ü", 14, 100, "0/4", strlen("0/4"), RGB(255, 255, 255));
		_barnAnimalsIcon->render(getMemDC(), WINSIZE_X - 500, 4);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 470, 6, "����ǹ��� ������ü", 14, 100, "0/6", strlen("0/6"), RGB(255, 255, 255));
		_skillTreeIcon->render(getMemDC(), WINSIZE_X - _skillTreeIcon->getWidth() * 1.5, 50, _skillTreeIcon->getWidth() * 1.5, _skillTreeIcon->getHeight() * 1.5, 
			0, 0, _skillTreeIcon->getWidth(), _skillTreeIcon->getHeight());
		SetTextAlign(getMemDC(), TA_RIGHT);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 40, 65, "����ǹ��� ������ü", 14, 100, "��ų Ʈ�� [K]", strlen("��ų Ʈ�� [K]"), RGB(255, 255, 255));
		_questBookIcon->render(getMemDC(), WINSIZE_X - _questBookIcon->getWidth() * 1.5 - 5, 95, _questBookIcon->getWidth() * 1.5, _questBookIcon->getHeight() * 1.5,
			0, 0, _questBookIcon->getWidth(), _questBookIcon->getHeight());
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 40, 100, "����ǹ��� ������ü", 14, 100, "����Ʈ [L]", strlen("����Ʈ [L]"), RGB(255, 255, 255));
		SetTextAlign(getMemDC(), TA_LEFT);
		for (int i = 0; i < 10; i++)
		{
			//IMAGEMANAGER->findImage("")
		}
	}
	else if (_sceneName == "Farm")
	{
		showUIWindow();
	}
}

void UI::updateUIWindow()
{
}

void UI::showUIWindow()
{

}
