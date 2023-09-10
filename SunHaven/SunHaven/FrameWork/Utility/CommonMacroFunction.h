#pragma once

template <typename InterfaceType>
inline void SafeRelease(InterfaceType** currentScene)
{
	if (*currentScene != nullptr)
	{
		(*currentScene)->Release();
		*currentScene = nullptr;
	}
}

template <typename InterfaceType>
inline InterfaceType SafeAcquire(InterfaceType* newObject)
{
	if (newObject != nullptr)
	{
		newObject->AddRef();
	}

	return newObject;
}

inline HRESULT ExceptionToResult()
{
	try
	{
		throw;
	}

	catch (std::bad_alloc&)
	{
		return E_OUTOFMEMORY;
	}

	catch (...)
	{
		return E_FAIL;
	}
}

template <typename InterfaceType>
inline void SafeSet(InterfaceType** currentObject, InterfaceType* newObject)
{
	SafeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}


inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline bool SamePoint(POINT pt1, POINT pt2)
{
	if (pt1.x == pt2.x)
	{
		if (pt1.y == pt2.y)
		{
			return true;
		}
	}
	return false;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void MyTextOut(HDC hdc, int x, int y, LPCTSTR Text)
{
	TextOut(hdc, x, y, Text, lstrlen(Text));
}

inline RECT CollisionAreaResizing(RECT& rcDest, int width, int height)
{
	RECT rc =
	{
		rcDest.left + width / 2,
		rcDest.top + height / 2,
		rcDest.right - width / 2,
		rcDest.bottom - height / 2
	};

	return rc;
}