#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

namespace Type
{
	enum ObjectType
	{
		GRASS1,
		GRASS2,
		TREE1,
		TREE2,
		STONE1,
		STONE2
	};
}

class Object : public GameNode
{
private:
	//vector<Item> _dropItems;
	GImage* _image;
	POINT _tilePos;
	Type::ObjectType _type;
	RECT _rc;

public:
	HRESULT init(void);
	HRESULT init(Type::ObjectType type, POINT tilePos);
	void release(void);
	void update(void);
	void render(void);

	Object() {}
	~Object() {}
};

