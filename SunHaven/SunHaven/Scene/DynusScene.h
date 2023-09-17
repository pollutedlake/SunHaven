// Á¤¼ºÁø
#pragma once
#include "../GameNode/GameNode.h"
#include "../Class/Boss/Dynus.h"
#include "../Class/Enemy/Shadeclaw.h"
#include "../../Player/Player.h"
#include "../Class/Enemy/EnemyManager.h"

namespace DynusSceneDialog
{
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
		int _nextDialog;
		pair<string, int> _answer[4];
	};
};


class UI;
class DynusScene : public GameNode
{
private:
	GImage* _loopImg;
	GImage* _bg;
	GImage* _dialogWindow2;
	GImage* _dialogWindow1;
	GImage* _moveMapImg;
	RECT _rcStar[8];
	float _offsetX, _offsetY;

	Dynus* _dynus;
	Shadeclaw* _shadeclaw;
	Player* _player;
	EnemyManager* _em;

	DynusSceneDialog::Dialog _arrDialogs[67];
	int _dialogIdx;
	GImage* _speaker;
	float _typingTime;
	DynusSceneDialog::DialogState _dialogState;
	RECT _dialogRC;
	float _dialogSize;

	UI* _ui;

	char _text[64];

	RECT _portal;
	bool _moveMap;
	bool _enterScene;
	float _clippingRaius;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderDialog();
	void updateDialog();
	void dialog(DynusSceneDialog::Dialog dialog);
	void collision(void);

	DynusScene() {}
	~DynusScene() {}
};

