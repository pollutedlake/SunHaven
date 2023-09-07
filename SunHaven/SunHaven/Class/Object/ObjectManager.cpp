#include "Stdafx.h"
#include "ObjectManager.h"
#include "../Camera.h"

HRESULT ObjectManager::init(void)
{
	FILE* _fp;
	fopen_s(&_fp, "FarmMapObject.txt", "r");
	if (_fp != NULL)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 100; k++)
			{
				int tile;
				fscanf_s(_fp, "%d ", &tile);
				if (tile == -1)
				{
					continue;
				}
				Object* object = nullptr;
				switch (tile / 2)
				{
					case 0:
						object = new Grass;
					break;
					case 1:
						object = new Tree;
					break;
					case 2:
						object = new Rock;
					break;
				}
				if(object != nullptr)
				{
					object->init((LivingObjectType)tile, PointMake(k, j));
					_vObject.push_back(object);
				}
			}
			fscanf_s(_fp, "\n");
		}
	}
	std::fclose(_fp);
    return S_OK;
}

void ObjectManager::release(void)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end();)
	{
		(*_viObject)->release();
		SAFE_DELETE((*_viObject));
		_viObject = _vObject.erase(_viObject);
	}
}

void ObjectManager::update(void)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		(*_viObject)->updateCameraPos(_camera->worldToCameraX((*_viObject)->getTilePos().x * 36 + 18), _camera->worldToCameraY((*_viObject)->getTilePos().y * 36 + 18));
		(*_viObject)->update();
	}
}

void ObjectManager::render(void)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		RECT rect;
		if(IntersectRect(&rect, &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), &(*_viObject)->getRC()))
		{
			(*_viObject)->renderHpBar();
		}
	}
}
