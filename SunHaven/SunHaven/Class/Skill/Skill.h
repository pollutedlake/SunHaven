#pragma once

class Skill
{
protected:
	string _index;
	string _name;
	string _type;
	int _tier;
	string _description;
	float _value1[3];
	float _value2[3];
	const char* _filePath;

public:
	virtual void init(string index, string name, string type, int tier, string description,
		float value1[], float value2[], const char* filePath, int width, int height);

	string getIndex(void) { return _index; }
	string getType(void) { return _type; }
	int getTier(void) { return _tier; }
	string getDescription(void) { return _description; }
	float getValue1(int index) { return _value1[index]; }
	float getValue2(int index) { return _value2[index]; }
	const char* getFilePath(void) { return _filePath; }
};

