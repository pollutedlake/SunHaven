#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
	_limitRC.left = WINSIZE_X / 2;
	_limitRC.top = WINSIZE_Y / 2;
	_speed = 10;
	return S_OK;
}

void Camera::release(void)
{
	
}

void Camera::update(void)
{
	if (_position.x < _limitRC.left)
	{
		_position.x = _limitRC.left;
	}
	if (_position.x > _limitRC.right)
	{
		_position.x = _limitRC.right;
	}
	if (_position.y < _limitRC.top)
	{
		_position.y = _limitRC.top;
	}
	if (_position.y > _limitRC.bottom)
	{
		_position.y = _limitRC.bottom;
	}
}

void Camera::render(void)
{
}

void Camera::setPosition(POINT position)
{
	_position = position;
	if (_position.x < _limitRC.left)
	{
		_position.x = _limitRC.left;
	}
	if (_position.x > _limitRC.right)
	{
		_position.x = _limitRC.right;
	}
	if (_position.y < _limitRC.top)
	{
		_position.y = _limitRC.top;
	}
	if (_position.y > _limitRC.bottom)
	{
		_position.y = _limitRC.bottom;
	}
}

RECT Camera::worldToCameraRect(RECT rc)
{
	RECT cRC = RectMake(worldToCameraX(rc.left), worldToCameraY(rc.top), rc.right - rc.left, rc.bottom - rc.top);
	return cRC;
}

POINT Camera::worldToCamera(POINT point)
{
	return PointMake(WINSIZE_X / 2 - (_position.x - point.x), WINSIZE_Y / 2 - (_position.y - point.y));
}

POINT Camera::cameraToWorld(POINT point)
{
	return PointMake(point.x + (_position.x - WINSIZE_X / 2), point.y + (_position.y - WINSIZE_Y / 2));
}

float Camera::cameraToWorldX(float x)
{
	return x + (x - WINSIZE_X / 2);
}

float Camera::cameraToWorldY(float y)
{
	return y + (y - WINSIZE_Y / 2);
}

float Camera::worldToCameraX(float x)
{
	return WINSIZE_X / 2 - (_position.x - x);
}

float Camera::worldToCameraY(float y)
{
	return WINSIZE_Y / 2 - (_position.y - y);
}
