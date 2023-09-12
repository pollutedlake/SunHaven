#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../FrameWork/Animation/Animation.h"
#include "../Class/Inventory.h"
#include "../Class/Skill/SkillManager.h"

#define OBJECT_RANGE 50.0f

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
	RECT _playertoCameraRC;

	RECT _miniRC[4];

	GImage* _fireball;
	Animation* _fireballAnim;
	RECT _fireballRC;

	GImage* _MouseOver;
	RECT _selectRC;

	GImage* _swordSlash;
	Animation* _swordAnim;
	Animation* _swordSlashAnim;
	Animation* _swordSlashUpDownAnim;
	RECT _swordSlashRC;

	GImage* _axeSwing;
	Animation* _axeSwingAnim;
	RECT _axeSwingRC;

	GImage* _pickaxeSwing;
	Animation* _pickaxeSwingAnim;
	RECT _pickaxeSwingRC;

	GImage* _hoeSwing;
	Animation* _hoeSwingAnim;
	RECT _hoeSwingRC;

	GImage* _scytheSwing;
	Animation* _scytheSwingAnim;
	RECT _scytheSwingRC;

	GImage* _toolImage;
	Animation* _toolAnim;
	RECT _toolAnimRC;
	

	GImage* _fireBeam;
	RECT _firebeamRC;
	int offsetX = 0;


	Inventory* _inven;


	GImage* _collisionMap;

	float _x, _y;
	float _cx, _cy;
	float _moveSpeed;

	bool _isCollisionLeft;
	bool _isCollisionRight;
	bool _isCollisionTop;
	bool _isCollisionBottom;


	int axeSwingAnimArr[4] = { 15,16,17,18 };
	int pickaxeSwingAnimArr[4] = { 12,13,14,15 };
	int hoeSwingAnimArr[4] = { 12,13,14,15 };
	int scytheSwingAnimArr[4] = { 12,13,14,15 };

	bool _isLoop;


	float _jump;
	bool _isJump;

public:
	HRESULT init(float x, float y, string collisionMapkey);
	void release(void);
	void update(void);
	void render(void);

	void MouseOver(ObjectManager* object, POINT point);

	void UseTool(ObjectManager* object, POINT point);

	inline void UseToolAnim(bool stayKeydown)
	{
		_isLoop = stayKeydown ? true : false;
	}

	void UseFishingLod(POINT point);
	void UseSword();
	void UseCrossBow();

	void ObjectCollision(ObjectManager* object);

	POINT getPlayerPosition() { return PointMake((int)_x, (int)_y); }

	void setPlayerPosition(POINT position)
	{
		_x = position.x;
		_y = position.y;
	}

	void worldToCamera(POINT position)
	{
		_cx = position.x;
		_cy = position.y;


		_playertoCameraRC = RectMakeCenter(_cx, _cy,
			_playerMoveAnim->getFrameWidth(),
			_playerMoveAnim->getFrameHeight());


		
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_swordSlashRC = RectMakeCenter(_cx - 28, _cy,
				_swordSlashAnim->getFrameWidth(),
				_swordSlashAnim->getFrameHeight());

			_firebeamRC = RectMake(_cx, _cy - 24,
				_cx - (_firebeamRC.right - _firebeamRC.left), 50);

			_axeSwingRC = RectMakeCenter(_cx, _cy,
				_axeSwingAnim->getFrameWidth(),
				_axeSwingAnim->getFrameHeight());

			_pickaxeSwingRC = RectMakeCenter(_cx-12, _cy,
				_pickaxeSwingAnim->getFrameWidth(),
				_pickaxeSwingAnim->getFrameHeight());

			_hoeSwingRC = RectMakeCenter(_cx-8, _cy+6,
				_hoeSwingAnim->getFrameWidth(),
				_hoeSwingAnim->getFrameHeight());

			_scytheSwingRC = RectMakeCenter(_cx-12, _cy,
				_scytheSwingAnim->getFrameWidth(),
				_scytheSwingAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_swordSlashRC = RectMakeCenter(_cx + 28, _cy,
				_swordAnim->getFrameWidth(),
				_swordAnim->getFrameHeight());


			_axeSwingRC = RectMakeCenter(_cx, _cy,
				_axeSwingAnim->getFrameWidth(),
				_axeSwingAnim->getFrameHeight());

			_pickaxeSwingRC = RectMakeCenter(_cx+12, _cy,
				_pickaxeSwingAnim->getFrameWidth(),
				_pickaxeSwingAnim->getFrameHeight());

			_hoeSwingRC = RectMakeCenter(_cx+8, _cy + 6,
				_hoeSwingAnim->getFrameWidth(),
				_hoeSwingAnim->getFrameHeight());

			_scytheSwingRC = RectMakeCenter(_cx + 12, _cy,
				_scytheSwingAnim->getFrameWidth(),
				_scytheSwingAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			_swordSlashRC = RectMakeCenter(_cx, _cy-28,
				_swordAnim->getFrameWidth(),
				_swordAnim->getFrameHeight());


			_axeSwingRC = RectMakeCenter(_cx, _cy,
				_axeSwingAnim->getFrameWidth(),
				_axeSwingAnim->getFrameHeight());

			_pickaxeSwingRC = RectMakeCenter(_cx, _cy,
				_pickaxeSwingAnim->getFrameWidth(),
				_pickaxeSwingAnim->getFrameHeight());

			_hoeSwingRC = RectMakeCenter(_cx, _cy,
				_hoeSwingAnim->getFrameWidth(),
				_hoeSwingAnim->getFrameHeight());

			_scytheSwingRC = RectMakeCenter(_cx, _cy,
				_scytheSwingAnim->getFrameWidth(),
				_scytheSwingAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_swordSlashRC = RectMakeCenter(_cx, _cy+28,
				_swordAnim->getFrameWidth(),
				_swordAnim->getFrameHeight());


			_axeSwingRC = RectMakeCenter(_cx, _cy,
				_axeSwingAnim->getFrameWidth(),
				_axeSwingAnim->getFrameHeight());

			_pickaxeSwingRC = RectMakeCenter(_cx, _cy+12,
				_pickaxeSwingAnim->getFrameWidth(),
				_pickaxeSwingAnim->getFrameHeight());

			_hoeSwingRC = RectMakeCenter(_cx, _cy + 6,
				_hoeSwingAnim->getFrameWidth(),
				_hoeSwingAnim->getFrameHeight());

			_scytheSwingRC = RectMakeCenter(_cx, _cy+12,
				_scytheSwingAnim->getFrameWidth(),
				_scytheSwingAnim->getFrameHeight());
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

	RECT getPlayertoCameraRect(void) { return _playertoCameraRC; }

	Inventory* getInven() { return _inven; }

	Player() {}
	~Player() {}
};