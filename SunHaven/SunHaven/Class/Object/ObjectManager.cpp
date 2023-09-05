#include "Stdafx.h"
#include "ObjectManager.h"
#include "../Camera.h"

HRESULT ObjectManager::init(void)
{
	FILE* _fp;
	fopen_s(&_fp, "FarmMapObject.txt", "r");
	if (_fp != NULL)
	{
		int objectN;
		fscanf_s(_fp, "%d\n", &objectN);
		for (int i = 0; i < objectN; i++)
		{
			int type, tilePosX, tilePosY;
			fscanf_s(_fp, "%d %d %d\n", &type, &tilePosX, &tilePosY);
			Object* object = new Object;
			object->init((LivingObjectType)type, PointMake(tilePosX, tilePosY));
			_vObject.push_back(object);
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
		(*_viObject)->updateCameraPos(_camera->worldToCameraX((*_viObject)->getTilePos().x * 48 + 24), _camera->worldToCameraY((*_viObject)->getTilePos().y * 48 + 24));
	}
}

void ObjectManager::render(void)
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		(*_viObject)->render();
	}
}