#pragma once
#include "../../FrameWork/GameNode/GameNode.h"
#include "Tree.h"
#include "Rock.h"
#include "Grass.h"

class Camera;

class ObjectManager : public GameNode
{
private:
	typedef vector<Object*> vObject;
	typedef vector<Object*>::iterator viObject;

private:
	vObject _vObject;
	viObject _viObject;
	Camera* _camera;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setCameraAddress(Camera* camera) {_camera = camera;}

	vObject getObjectList() {return _vObject;}

	ObjectManager() {}
	~ObjectManager() {}
};

