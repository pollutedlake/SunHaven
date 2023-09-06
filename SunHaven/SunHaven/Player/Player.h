#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../FrameWork/Animation/Animation.h"
#include "../Class/Inventory.h"

struct tagPlayerState
{
	float playerSpeed;
	int HP;
	int MP;

	int mineEXP;
	int combatEXP;
	int farmingEXP;
};


class Player : public GameNode
{
private:
	GImage* _playerImage;
	Animation* _playerMoveAnim;
	RECT _playerRC;

	RECT _miniRC[4];

	GImage* _fireball;
	Animation* _fireballAnim;
	RECT _fireballRC;


	GImage* _swordSlash;
	Animation* _swordSlashAnim;
	RECT _swordSlashRC;



	Inventory* _inven;


	float _x, _y;
	float _moveSpeed;

	bool _isCollisionLeft;
	bool _isCollisionRight;
	bool _isCollisionTop;
	bool _isCollisionBottom;


	float _jump;
	bool _isJump;

public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);

	void UseTool();
	void UseFishingLod();
	void UseSword();
	void UseCrossBow();

	POINT getPlayerPosition() { return PointMake((int)_x, (int)_y); }

	void setPlayerPosition(POINT position)
	{
		_x = position.x;
		_y = position.y;
	}

	void worldToCamera(POINT position)
	{
		_playerRC = RectMakeCenter(position.x, position.y,
			_playerMoveAnim->getFrameWidth(),
			_playerMoveAnim->getFrameHeight());


		
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_swordSlashRC = RectMakeCenter(position.x - 28, position.y,
				_swordSlashAnim->getFrameWidth(),
				_swordSlashAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_swordSlashRC = RectMakeCenter(position.x + 28, position.y,
				_swordSlashAnim->getFrameWidth(),
				_swordSlashAnim->getFrameHeight());
		}
	}

	RECT getPlayerRC() {return _playerRC;}

	Player() {}
	~Player() {}
};