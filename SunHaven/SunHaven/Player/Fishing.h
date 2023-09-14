#pragma once
#include "../FrameWork/GameNode/GameNode.h"


class Fishing : public GameNode
{
private:
	GImage* _fishingBorder;
	RECT _fishingBorderRC;

	GImage* _fishingCursor;
	RECT _fishingCursorRC;

	GImage* _fishingGreatZone;
	RECT _fishingGreatZoneRC;

	GImage* _fishingPerfectZone;
	RECT _fishingPerfectZoneRC;

	float _fishingRange = 0.0f;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Fishing() {}
	~Fishing() {}
};

