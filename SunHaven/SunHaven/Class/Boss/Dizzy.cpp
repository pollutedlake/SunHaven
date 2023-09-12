#include "Stdafx.h"
#include "Dizzy.h"

HRESULT Dizzy::init(void)
{
	_state = EDizzyState::WAKE;

	_img = IMAGEMANAGER->addFrameImage("DizzyWake", "Resources/Images/Boss/Dizzy/Dizzy_Wake.bmp",
		1218, 320, 7, 2, true, RGB(255, 0, 255));

	_x = CENTER_X;
	_y = CENTER_Y - 100;

	_rcDizzy = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_hp = 5000.0f;
	_maxHp = 5000.0f;

	_hpBar = new ProgressBar;

	_hpBar->init("", "ProgressBarBGW", "ProgressBarW", CENTER_X + 15, CENTER_Y + 257, 92 * 4 + 25, 14);

	_bullet = new Bullet;



	return S_OK;
}

void Dizzy::release(void)
{

}

void Dizzy::update(void)
{
}

void Dizzy::render(void)
{
	draw();

	_hpBar->render();

	char bossHpRate[128];

	sprintf_s(bossHpRate, "%d %s %d", static_cast<int>(_hp), "/", static_cast<int>(_maxHp));

	FONTMANAGER->textOut(getMemDC(), CENTER_X - 10, CENTER_Y + 230, "배달의민족 을지로체",
		20, 500, "디지", strlen("디지"), RGB(255, 255, 255));
	FONTMANAGER->textOut(getMemDC(), CENTER_X - 30, CENTER_Y + 250, "배달의민족 을지로체",
		15, 400, bossHpRate, strlen(bossHpRate), RGB(255, 255, 255));

	IMAGEMANAGER->render("DizzyHpBarBorder", getMemDC(), CENTER_X - 210, CENTER_Y + 220);
}

void Dizzy::draw(void)
{
	_img->frameRender(getMemDC(), _x, _y);
}
