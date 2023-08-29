#include "stdafx.h"
#include "Dynus.h"

HRESULT Dynus::init(void)
{
	_x = CENTER_X - 317;
	_y = 0;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	//_dynusImg = IMAGEMANAGER->findImage("DynusBreathe");

	_dynusImg = IMAGEMANAGER->addImage("DynusBreathe", "Resources/Images/Boss/DynusBreathe.bmp",
		2536, 594, true, RGB(255, 0, 255));
	/*_dynusImg = IMAGEMANAGER->addImage("DynusSpell", "Resources/Images/Dynus/DynusSpell.bmp",
		3804, 3564, true, RGB(255, 0, 255));*/
	_breatheAni = new Animation;
	_breatheAni->init(_dynusImg->getWidth(), _dynusImg->getHeight(), 634, 297);
	_breatheAni->setDefPlayFrame(false, true);
	_breatheAni->setFPS(12);

	_bullet = new Bullet;
	_bullet->init("DynusOrb", 100, 1000.0f);

	_rcDynus = RectMakeCenter(_x, _y,
		_dynusImg->getFrameWidth(), _dynusImg->getFrameHeight());

	for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			_rcPa1Start[i][j] =
				RectMakeCenter(CENTER_X - 50 + 400 * cos(DEGREE_RADIAN(30 * i)) + 30 * j,
					CENTER_Y - 400 * sin(DEGREE_RADIAN(30 * i)), 50, 50);
		}
	}

	/*for (int i = 0; i < PA2_STARTPOS_NUM; i++)
	{

	}

	for (int i = 0; i < PA3_STARTPOS_NUM; i++)
	{

	}*/

	return S_OK;
}

HRESULT Dynus::init(const char* imageName, POINT position)
{
	//_x = position.x;
	//_y = position.y;

	//_worldTimeCount = GetTickCount();
	//_rndTimeCount = RND->getFromFloatTo(50, 150);

	//_dynusImg = IMAGEMANAGER->findImage(imageName);
	//_rcDynus = RectMakeCenter(_x, _y,
	//	_dynusImg->getFrameWidth(), _dynusImg->getFrameHeight());

	//_dynusImg = IMAGEMANAGER->addImage("DynusBreathe", "Resources/Images/Dynus/DynusBreathe.bmp",
	//	2536, 594, true, RGB(255, 0, 255));
	///*_dynusImg = IMAGEMANAGER->addImage("DynusSpell", "Resources/Images/Dynus/DynusSpell.bmp",
	//	3804, 3564, true, RGB(255, 0, 255));*/
	//_dynusAni = new Animation;
	//_dynusAni->init(_dynusImg->getWidth(), _dynusImg->getHeight(), 634, 297);
	//_dynusAni->setDefPlayFrame(false, true);
	//_dynusAni->setFPS(12);

	return S_OK;
}

void Dynus::release(void)
{
	_breatheAni->release();
	SAFE_DELETE(_breatheAni);

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void Dynus::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_breatheAni->AniStart();
	}

	_breatheAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	/*_bullet->fire(rc.left + (rc.right - rc.left) / 2,
		rc.bottom + (rc.top - rc.bottom) / 2 + 30,
		getAngle(rc.left + (rc.right - rc.left) / 2,
			rc.bottom + (rc.top - rc.bottom) / 2,
			_rocket->getPosition().x,
			_rocket->getPosition().y),
		RND->getFromFloatTo(2.0f, 4.0f));*/

	_bullet->update();
}

void Dynus::render(void)
{
	draw();

	_bullet->render();
}

void Dynus::move(void)
{

}

void Dynus::draw(void)
{
	IMAGEMANAGER->render("DynusWing", getMemDC(), _x + 210, _y + 10);
	_dynusImg->aniRender(getMemDC(), _x, _y, _breatheAni);

	for (int i = 0; i < PA1_STARTPOS_NUM_1; i++)
	{
		for (int j = 0; j < PA1_STARTPOS_NUM_2; j++)
		{
			DrawRectMake(getMemDC(), _rcPa1Start[i][j]);
		}
	}
}

void Dynus::bulletFire()
{
	
}

bool Dynus::bulletCountFire(void)
{
	if (_bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();

		return true;
	}

	return false;
}
