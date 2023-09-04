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
	// ������ �߰� ->
	void addData(char* section, char* key, char* value);	// 2D ���� �Ҽ��� ����

	// ���̺�
	void iniSave(char* fileName);

	// ���� ��
	char* loadDataString(char* fileName, char* section, char* key);

	// ����
	int loadDataInteger(char* fileName, char* section, char* key);

public:
	INIData() {}
	~INIData() {}
};

