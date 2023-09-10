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

	GImage* _lynnMomHouse;
	GImage* _train1;

	Lynn* _lynn;

	GImage* _cursorImg;

	float _time;
	float _lynnMomTime;
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

	int _cutIdx;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderDialog();
	void dialog(string charName, string printString, int length, int expression);
	void updateDialog();

	bool unName();

	IntroScene() {}
	~IntroScene() {}
};
