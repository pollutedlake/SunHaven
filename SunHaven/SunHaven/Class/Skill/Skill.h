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
	typedef tagSkillBorder skillBorderImg;

protected:
	string _index;
	string _name;
	string _type;
	int _tier;
	string _description;
	double _value1[3];
	double _value2[3];



protected:
	skillImg _image;
	skillBorderImg _img[40];


	RECT tmpRC[40];
	RECT borderRC[40];
	RECT _descriptionRC;

private:

public:
	virtual void init(string index, string name, string type, int tier, string description,
		double value1[], double value2[]);

	virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();



	string getIndex(void) { return _index; }
	string getType(void) { return _type; }
	int getTier(void) { return _tier; }
	string getDescription(void) { return _description; }
	double getValue1(int index) { return _value1[index]; }
	double getValue2(int index) { return _value2[index]; }

	Skill() {}
	~Skill() {}
};

