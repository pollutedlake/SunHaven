#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../FrameWork/Animation/Animation.h"
//#include "../Class/Inventory.h"
#include "../Class/Skill/SkillManager.h"
#include "../Class/Bullets/Bullets.h"

#define OBJECT_RANGE 50.0f

class ObjectManager;
class Inventory;

enum class eTools
{
	SICKLE=0,
	HOE,
	AXE,
	PICKAXE,
	FISHINGLOD,
	SWORD
};

struct tagPlayerState
{
	char* playerName;
	float playerSpeed;
	int HP;
	int MP;
	int MaxHP;
	int MaxMP;
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
	Fireball* _fireBall;
	eTools _eTools;

	GPImage* _dashSlash;
	POINT _currentPoint = { (int)_cx,(int)_cy };
	RECT _dashSlashRC;
	RECT _dashSlashCollisionRC = {0,0,0,0};
	int _dashSlashCount = 0;
	bool _isDashAttack = false;

	float MPRecoverySec;

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
	Animation* _swordSwingAnim;
	Animation* _swordSlashAnim;
	Animation* _swordSlashUpDownAnim;
	RECT _swordSlashRC;
	RECT _swordSwingRC;

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


	GImage* _fishingLod;
	Animation* _fishingLodAnim;
	RECT _fishingLodRC;



	GImage* _toolImage;
	Animation* _toolAnim;
	RECT _toolAnimRC;
	

	GImage* _fireBeam;
	RECT _firebeamRC;
	int offsetX = 0;

	//Inventory* _inven;



	GImage* _fishingBorder;
	RECT _fishingBorderRC;

	GImage* _fishingCursor;
	RECT _fishingCursorRC;

	GImage* _fishingGreatZone;
	RECT _fishingGreatZoneRC;

	GImage* _fishingPerfectZone;
	RECT _fishingPerfectZoneRC;


	GImage* _collisionMap;

	float _x, _y;
	float _cx, _cy;
	float _moveSpeed;
	float _fishingRange = 0.0f;

	bool _isCollisionLeft;
	bool _isCollisionRight;
	bool _isCollisionTop;
	bool _isCollisionBottom;

	bool _isLeft;
	bool _isUpDown;
	bool _isUp;

	bool _isFishing;
	bool _isSuccessFishing;

	int axeSwingAnimArr[4] = { 15,16,17,18 };
	int pickaxeSwingAnimArr[4] = { 12,13,14,15 };
	int hoeSwingAnimArr[4] = { 12,13,14,15 };
	int scytheSwingAnimArr[4] = { 12,13,14,15 };

	bool _isLoop;

	int cursormovespeed = 2;

	float _jump;
	bool _isJump;
	float _invincibilityTime;
	bool _isDamaged;

public:
	HRESULT init(float x, float y, string collisionMapkey);
	void release(void);
	void update(void);
	void render(void);

	void MouseOver(ObjectManager* object, POINT point);

	//void UseTool(ObjectManager* object, POINT point);
	//bool UseTool(ObjectManager* object, POINT point);
	list<POINT> UseTool(ObjectManager* object, POINT point);


	inline void UseToolAnim(bool stayKeydown)
	{
		_isLoop = stayKeydown ? true : false;
	}

	void UseFishingLod(POINT point);
	void Fishing();
	void getFishItem(bool successFishing, Inventory* inven, string index);
	void UseSword();
	void UseCrossBow();

	void RecureHP();
	void RecureMP();

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
			/*_swordSlashRC = RectMakeCenter(_cx - 28, _cy,
				_swordSlashAnim->getFrameWidth(),
				_swordSlashAnim->getFrameHeight());*/

			_swordSwingRC = RectMakeCenter(_cx, _cy,
				_swordSwingAnim->getFrameWidth(),
				_swordSwingAnim->getFrameHeight());

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

			_fishingLodRC = RectMakeCenter(_cx, _cy,
				_fishingLodAnim->getFrameWidth(),
				_fishingLodAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			/*_swordSlashRC = RectMakeCenter(_cx + 28, _cy,
				_swordAnim->getFrameWidth(),
				_swordAnim->getFrameHeight());*/
			_swordSwingRC = RectMakeCenter(_cx, _cy,
				_swordSwingAnim->getFrameWidth(),
				_swordSwingAnim->getFrameHeight());


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

			_fishingLodRC = RectMakeCenter(_cx, _cy,
				_fishingLodAnim->getFrameWidth(),
				_fishingLodAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			/*_swordSlashRC = RectMakeCenter(_cx, _cy-28,
				_swordAnim->getFrameWidth(),
				_swordAnim->getFrameHeight());*/
			_swordSwingRC = RectMakeCenter(_cx, _cy,
				_swordSwingAnim->getFrameWidth(),
				_swordSwingAnim->getFrameHeight());


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

			_fishingLodRC = RectMakeCenter(_cx, _cy,
				_fishingLodAnim->getFrameWidth(),
				_fishingLodAnim->getFrameHeight());
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			/*_swordSlashRC = RectMakeCenter(_cx, _cy+28,
				_swordAnim->getFrameWidth(),
				_swordAnim->getFrameHeight());*/
			_swordSwingRC = RectMakeCenter(_cx, _cy,
				_swordSwingAnim->getFrameWidth(),
				_swordSwingAnim->getFrameHeight());


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

			_fishingLodRC = RectMakeCenter(_cx, _cy,
				_fishingLodAnim->getFrameWidth(),
				_fishingLodAnim->getFrameHeight());
		}

		for (int i = 0; i < _fireBall->getBullet().size(); i++)
		{
			_fireBall->getBullet()[i].rc= RectMakeCenter(_cx, _cy,
				_fireBall->getBullet()[i].img->getFrameWidth(),
				_fireBall->getBullet()[i].img->getFrameHeight());
		}

		_firebeamRC = RectMake(position.x, position.y - 24,
			position.x + (_firebeamRC.right - _firebeamRC.left), 50);
	}

	inline void hitDamage(float damage)
	{
		if (_invincibilityTime == 0.0f)
		{
			_isDamaged = true;
			_playerState.HP -= damage;
		}

		if (_playerState.HP <= 0)
		{
			_playerState.HP = 0;
		}
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

	}

	RECT getPlayerRC() { return _playerRC; }
	RECT getPlayertoCameraRect(void) { return _playertoCameraRC; }

	RECT getDashSlashCollisionRC() { return _dashSlashCollisionRC; }
	
	eTools getToolType() { return _eTools; }
	bool getIsSuccessFishing() { return _isSuccessFishing; }

	RECT getSwingRC() { return _swordSwingRC; }

	inline int getHP() { return _playerState.HP; }
	inline int getMaxHP() { return _playerState.MaxHP; }
	inline int getMP() { return _playerState.MP; }
	inline int getMaxMP() { return _playerState.MaxMP; }
	inline int getDefense() { return _playerState.defence; }
	inline int getAttackDamage() { return _playerState.attackDamage; }
	inline eTools getTools() { return _eTools; }
	inline int getGold() { return _playerState.gold; }
	

	void setHP(int itemStat)
	{
		_playerState.HP = getHP() + itemStat;
	}

	void setDefense(int itemStat)
	{
		_playerState.defence =  itemStat;
	}

	void setAttackDamage(int itemStat)
	{
		_playerState.attackDamage = getAttackDamage() + itemStat;

	}

	void setGold(int sellgold)
	{
		_playerState.gold = getGold() + sellgold;
	}

	Player() {}
	~Player() {}
};