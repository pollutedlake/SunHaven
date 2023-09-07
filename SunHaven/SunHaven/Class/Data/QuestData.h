#pragma once
#include "../Quest/Quest.h"

class QuestData
{
private:
	queue<Quest*> _quest;

public:
	void init(void);
	void questSetUp(Quest* qQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }

	QuestData() {}
	~QuestData() {}
};