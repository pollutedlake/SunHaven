#include "Stdafx.h"
#include "UI.h"
#include "../../Player/Player.h"

HRESULT UI::init(void)
{
	return S_OK;
}

HRESULT UI::init(string sceneName)
{
	_sceneName = sceneName;
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
	_grayBar = IMAGEMANAGER->findImage("GrayBar");
	for (int i = 0; i < 10; i++)
	{
		_shortcutItemRC[i] = RectMake(WINSIZE_X / 2 - 176 + 36 * i, WINSIZE_Y - 80, 32, 32);
	}
	return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{

}

void UI::render(void)
{
	showBasicUI();
}

void UI::renderBar(int x, int y, float width, float height, int alpha, string color)
{
	char key[256];
	wsprintf(key, "%sBar", color.c_str());
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x, y + 2, width, height - 4, 0, 0, IMAGEMANAGER->findImage(key)->getWidth(), IMAGEMANAGER->findImage(key)->getHeight(), alpha);
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x + 2, y, width - 4, 2, 0, 0, IMAGEMANAGER->findImage(key)->getWidth(), IMAGEMANAGER->findImage(key)->getHeight(), alpha);
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x + 2, y + height - 2, width - 4, 2, 0, 0, IMAGEMANAGER->findImage(key)->getWidth(), IMAGEMANAGER->findImage(key)->getHeight(), alpha);
	wsprintf(key, "%sBarLT", color.c_str());
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x, y, alpha);
	wsprintf(key, "%sBarRT", color.c_str());
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x + width - 2, y, alpha);
	wsprintf(key, "%sBarLB", color.c_str());
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x, y + height - 2, alpha);
	wsprintf(key, "%sBarRB", color.c_str());
	IMAGEMANAGER->findImage(key)->alphaRender(getMemDC(), x + width - 2, y + height - 2, alpha);
}

void UI::showBasicUI()
{
	_clock->render(getMemDC(), 20, 20, _clock->getWidth() * 1.5f, _clock->getHeight() * 1.5f, 0, 0, _clock->getWidth(), _clock->getHeight());
	_cursor->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	_dateBar->GPFrameRender(getMemDC(), 130, 20, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
	_dateBar->GPFrameRender(getMemDC(), 130, 55, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
	_timeBar->GPFrameRender(getMemDC(), 130, 95, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
	_upperRightBar->GPFrameRender(getMemDC(), WINSIZE_X - 666, 0, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
	FONTMANAGER->textOut(getMemDC(), 135, 25, "배달의민족 을지로체", 20, 100, "봄 1년차", strlen("봄 1년차"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), 135, 60, "배달의민족 을지로체", 20, 100, "일요일 1일", strlen("일요일 1일"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), 135, 100, "배달의민족 을지로체", 20, 100, "06:00AM", strlen("06:00AM"), RGB(255, 255, 255));
	_goldIcon->render(getMemDC(), WINSIZE_X - 300, 8, _goldIcon->getWidth() * 1.5f, _goldIcon->getHeight() * 1.5f, 0, 0, _goldIcon->getWidth(), _goldIcon->getHeight());
	if (_player->getGold() / 1000 > 0)
	{
		wsprintf(_text, "%d,%d", _player->getGold() / 1000, _player->getGold() % 1000);
	}
	else
	{
		wsprintf(_text, "%d", _player->getGold());
	}
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 280, 8, "배달의민족 을지로체", 14, 100, _text, strlen(_text), RGB(255, 255, 255));
	_orbIcon->render(getMemDC(), WINSIZE_X - 200, 8, _orbIcon->getWidth() * 1.5f, _orbIcon->getHeight() * 1.5f, 0, 0, _orbIcon->getWidth(), _orbIcon->getHeight());
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 180, 8, "배달의민족 을지로체", 14, 100, "8", strlen("8"), RGB(255, 255, 255));
	_ticketIcon->render(getMemDC(), WINSIZE_X - 100, 4);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 75, 8, "배달의민족 을지로체", 14, 100, "13", strlen("13"), RGB(255, 255, 255));
	_fishingNetIcon->render(getMemDC(), WINSIZE_X - 400, 4);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 375, 8, "배달의민족 을지로체", 14, 100, "0/4", strlen("0/4"), RGB(255, 255, 255));
	_barnAnimalsIcon->render(getMemDC(), WINSIZE_X - 500, 4);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 470, 6, "배달의민족 을지로체", 14, 100, "0/6", strlen("0/6"), RGB(255, 255, 255));
	_skillTreeIcon->render(getMemDC(), WINSIZE_X - _skillTreeIcon->getWidth() * 1.5, 50, _skillTreeIcon->getWidth() * 1.5, _skillTreeIcon->getHeight() * 1.5,
		0, 0, _skillTreeIcon->getWidth(), _skillTreeIcon->getHeight());
	SetTextAlign(getMemDC(), TA_RIGHT);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 40, 65, "배달의민족 을지로체", 14, 100, "스킬 트리 [K]", strlen("스킬 트리 [K]"), RGB(255, 255, 255));
	_questBookIcon->render(getMemDC(), WINSIZE_X - _questBookIcon->getWidth() * 1.5 - 5, 95, _questBookIcon->getWidth() * 1.5, _questBookIcon->getHeight() * 1.5,
		0, 0, _questBookIcon->getWidth(), _questBookIcon->getHeight());
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 40, 100, "배달의민족 을지로체", 14, 100, "퀘스트 [L]", strlen("퀘스트 [L]"), RGB(255, 255, 255));
	SetTextAlign(getMemDC(), TA_LEFT);
	renderBar(WINSIZE_X / 2 - 300, WINSIZE_Y - 45, 560, 40, 100, "Gray");
	renderBar(WINSIZE_X / 2 - 290, WINSIZE_Y - 40, 100, 30, 255, "Gray");
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X / 2 - 240, WINSIZE_Y - 35, "배달의민족 을지로체", 20, 100, "레벨 160", strlen("레벨 160"), RGB(255, 255, 255));
	renderBar(WINSIZE_X / 2 - 170, WINSIZE_Y - 40, 200, 30, 255, "Gray");
	IMAGEMANAGER->render("HpIcon", getMemDC(), WINSIZE_X / 2 - 165, WINSIZE_Y - 35, 20, 20, 
		0, 0, IMAGEMANAGER->findImage("HpIcon")->getWidth(), IMAGEMANAGER->findImage("HpIcon")->getHeight());
	renderBar(WINSIZE_X / 2 + 50, WINSIZE_Y - 40, 200, 30, 255, "Gray");
	IMAGEMANAGER->render("ManaIcon", getMemDC(), WINSIZE_X / 2 + 50, WINSIZE_Y - 40, 30, 30,
		0, 0, IMAGEMANAGER->findImage("ManaIcon")->getWidth(), IMAGEMANAGER->findImage("ManaIcon")->getHeight());
	renderBar(WINSIZE_X / 2 + 80, WINSIZE_Y - 35, 165.f * (float)_player->getMP() / (float)_player->getMaxMP(), 20, 255, "Blue");
	renderBar(WINSIZE_X / 2 - 140, WINSIZE_Y - 35, 165.f * (float)_player->getHP() / (float)_player->getMaxHP(), 20, 255, "Red");
	wsprintf(_text, "%d/%d", _player->getMP(), _player->getMaxMP());
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X / 2 + 162, WINSIZE_Y - 35, "배달의민족 을지로체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));
	wsprintf(_text, "%d/%d", _player->getHP(), _player->getMaxHP());
	FONTMANAGER->textOut(getMemDC(), WINSIZE_X / 2 - 58, WINSIZE_Y - 35, "배달의민족 을지로체", 20, 100, _text, strlen(_text), RGB(255, 255, 255));

	SetTextAlign(getMemDC(), TA_LEFT);
}
