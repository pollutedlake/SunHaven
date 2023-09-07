#pragma once

class Skill
{
protected:
	string _index;
	string _name;
	string _type;
	int _tier;
	string _description;
	double _value1[3];
	double _value2[3];

public:
	virtual void init(string index, string name, string type, int tier, string description,
		double value1[], double value2[]);

	string getIndex(void) { return _index; }
	string getType(void) { return _type; }
	int getTier(void) { return _tier; }
	string getDescription(void) { return _description; }
	double getValue1(int index) { return _value1[index]; }
	double getValue2(int index) { return _value2[index]; }
};

