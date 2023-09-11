#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../FrameWork/Animation/Animation.h"
#include "../Class/Inventory.h"
#include "../Class/Skill/SkillManager.h"

class ObjectManager;

enum class eTools
{
	SICKLE=0,
	HOE,
	AXE,
	PICKAXE,
	FISHINGLOD
};

struct tagPlayerState
{
	char* playerName;
	float playerSpeed;
	int HP;
	int MP;
	float HPRecoveryPerSec;
	float MPRecoveryPerSec;
	int gold;

	int attackDamage;
	int spellDamage;
	int defence;
	float critical;

	int mineEXP;
	int combatEXP;
	int farmingEXP;
};


class Player : public GameNode
{
private:
	tagPlayerState _playerState;
	int a;

	SkillManager* _skill;
	eTools _eTools;

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

	
	GImage* _fireBeam;
	RECT _firebeamRC;
	int offsetX = 0;


	Inventory* _inven;


	GImage* _collisionMap;

	float _x, _y;
	float _moveSpeed;

	bool _isCollisionLeft;
	bool _isCollisionRight;
	bool _isCollisionTop;
	bool _isCollisionBottom;


	float _jump;
	bool _isJump;

public:
	HRESULT init(float x, float y, string collisionMapkey);
	void release(void);
	void update(void);
	void render(void);

	void UseTool(ObjectManager* object);

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

			_firebeamRC = RectMake(position.x, position.y - 24,
				position.x - (_firebeamRC.right - _firebeamRC.left), 50);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_swordSlashRC = RectMakeCenter(position.x + 28, position.y,
				_swordSlashAnim->getFrameWidth(),
				_swordSlashAnim->getFrameHeight());

		}



		_firebeamRC = RectMake(position.x, position.y - 24,
			position.x + (_firebeamRC.right - _firebeamRC.left), 50);
	}




	bool isCollision()
	{

	}

	void setCollision(bool left, bool right, bool top, bool bottom)
	{
		_isCollisionLeft = left;
		_isCollisionRight = right;
		_isCollisionTop = top;
		_isCollisionBottom = bottom;

		cout << _isCollisionLeft <<
			_isCollisionRight <<
			_isCollisionTop << _isCollisionBottom << endl;
	}

	RECT getPlayerRC() { return _playerRC; }

	RECT getRect(void) { return _playerRC; }

	Player() {}
	~Player() {}
};