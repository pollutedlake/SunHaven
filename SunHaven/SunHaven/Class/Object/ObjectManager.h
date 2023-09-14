#pragma once
#include "../../FrameWork/GameNode/GameNode.h"
#include "Tree.h"
#include "Rock.h"
#include "Grass.h"

class ObjectManager : public GameNode
{
private:
	typedef vector<Object*> vObject;
	typedef vector<Object*>::iterator viObject;

private:
	vObject _vObject;
	viObject _viObject;

public:
	HRESULT init(string sceneName);
	void release(void);
	queue<pair<string, POINT>> updateObjects(void);
	void render(void);

	vObject getObjectList() {return _vObject;}

	ObjectManager() {}
	~ObjectManager() {}
};

