#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

struct tagSkillImg
{
	GImage* skillIcon;
	GImage* skillFrame;
	RECT rc;
	RECT frameRC;
};

struct tagSkillBorder
{
	GImage* borderImg;
	int skillLV;
	int maxSkillLV;
	RECT iconRC;
	RECT borderRC;
};

class Skill : public GameNode
{
protected:
	typedef tagSkillImg skillImg;
	typedef tagSkillBorder skillImage;

protected:
	string _index;
	string _name;
	string _type;
	int _tier;
	string _description;
	float _value1[3];
	float _value2[3];
	const char* _filePath;



protected:
	skillImg _image;
	skillImage _img[40];


	RECT tmpRC[40];
	RECT borderRC[40];


private:
	char str[10];

public:
	virtual void init(string index, string name, string type, int tier, string description,
		float value1[], float value2[], const char* filePath, int width, int height);

	HRESULT init();
    void release();
    void update();
    void render();



	string getIndex(void) { return _index; }
	string getType(void) { return _type; }
	int getTier(void) { return _tier; }
	string getDescription(void) { return _description; }
	float getValue1(int index) { return _value1[index]; }
	float getValue2(int index) { return _value2[index]; }
	const char* getFilePath(void) { return _filePath; }
};

