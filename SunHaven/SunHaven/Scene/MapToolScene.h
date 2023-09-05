// �ڻ���
#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/Object/Object.h"

#define MapToolWidth	800
#define MapToolHeight	600

enum TileType
{
	NORMAL,
	COLLIDER,
	OBJECT
};

struct Tile
{
	GImage* _image = nullptr;
	int _tile = 0;
	TileType _type;
	LivingObjectType _livObjectType;
};

class NormalButton;
class ToggleButton;
class RadioButton;

class MapToolScene : public GameNode
{
private:
	GImage* _tileMapBuffer;
	Tile _tileMap[7][100][100];
	vector<Object*> _objectList;
	vector<Object*>::iterator _itObjectList;
	
	int _tileMapSize;

	GImage* _tilesBuffer;
	Tile _tiles[5][20][20];

	GImage* _collisionBuffer;

	vector<NormalButton*> _vNormalButton;
	vector<NormalButton*>::iterator _viNormalButton;
	vector<ToggleButton*> _vToggleButton;
	vector<ToggleButton*>::iterator _viToggleButton;
	vector<RadioButton*> _vRadioButton;
	vector<RadioButton*>::iterator _viRadioButton;

	Tile _selectTiles[MapToolWidth / TILEWIDTH + 1][MapToolHeight / TILEHEIGHT + 1];
	Object* _selectObject;
	bool _isSelectObject;

	POINT _cameraPos;
	char _tileSizeChar[20];
	bool _input;
	int _layer;
	int _curTiles;

	RECT _cursorRC;
	RECT _selectRC;
	RECT _tilesRC;
	RECT _mapToolRC;
	RECT _exCursorRC;

	int _selectTilesRow;
	int _selectTilesCol;

	bool _showLayer[6];
	bool _copyMapTool;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void changeLayer(int layer);

	void prevTiles(void);
	void nextTiles(void);
	void erase(void);
	void toggleShowLayer(int layer);
	void selectObject(int objectType);

	void copyTiles(void);
	void sortObjects(int start, int end);

	void saveMaps();
	void loadLayers();

	MapToolScene() {}
	~MapToolScene() {}
};
