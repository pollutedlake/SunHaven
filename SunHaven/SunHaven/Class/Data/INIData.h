#pragma once
#include "../../FrameWork/SingletonBase/SingletonBase.h"


struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class INIData : public SingletonBase<INIData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);
	void release(void);

	// INI
	// 데이터 추가 ->
	void addData(char* section, char* key, char* value);	// 2D 기준 소수점 무시

	// 세이브
	void iniSave(char* fileName);

	// 문자 값
	char* loadDataString(char* fileName, char* section, char* key);

	// 정수
	int loadDataInteger(char* fileName, char* section, char* key);

public:
	INIData() {}
	~INIData() {}
};

