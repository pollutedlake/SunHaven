#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

class UI : public GameNode
{
	string _sceneName;
	GImage* _clock;
	GImage* _cursor;
	GPImage* _dateBar;
	GPImage* _timeBar;
	GPImage* _upperRightBar;
	GImage* _goldIcon;
	GImage* _ticketIcon;
	GImage* _orbIcon;
	GImage* _fishingNetIcon;
	GImage* _barnAnimalsIcon;
	GImage* _skillTreeIcon;
	GImage* _questBookIcon;
	char* _text[256];

public:
	HRESULT init(void);
	HRESULT init(string sceneName);
	void release(void);
	void update(void);
	void render(void);

	UI() {}
	~UI() {}
};