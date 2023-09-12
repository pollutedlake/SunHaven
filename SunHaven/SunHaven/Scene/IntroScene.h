#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/NPC/Lynn.h"

enum DialogState
{
	OPEN,
	SHOW,
	HIDE,
	CLOSE
};

struct Dialog
{
	string _charName;
	int _expression;
	string _dialog;
	int _letterN;
	int _answerN;
	string _answer[4];
};

class IntroScene : public GameNode
{
private:
	POINT _cameraPos;
	GImage* _introCut[3];
	GImage* _lynnMom;
	GImage* _dialogWindow;
	GImage* _changeCutImg;
	GImage* _trainPassengers[7];
	GImage* _catSleep;
	GImage* _trainWindow;

	GImage* _lynnMomHouse;
	GImage* _train1;
	GImage* _train2;

	Lynn* _lynn;

	GImage* _cursorImg;

	float _time;
	float _changeCutTime;
	int _count;
	int _count2;
	float _curTime;

	queue<int> _nextActionTiming;

	RECT _dialogRC;
	Dialog _arrDialogs[59];
	int _dialogIdx;
	GImage* _speaker;
	float _typingTime;
	DialogState _dialogState;
	float _dialogSize;

	bool _changeCut;
	bool _dark;

	int _darkAlpha;

	int _cutIdx;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderDialog();
	void dialog(Dialog dialog);
	void updateDialog();

	bool checkNextActionTiming();

	IntroScene() {}
	~IntroScene() {}
};
