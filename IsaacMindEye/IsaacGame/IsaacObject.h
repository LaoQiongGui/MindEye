#pragma once
#include <stdio.h>
#include <Windows.h>

class IIsaacObject
{
public:
	virtual ~IIsaacObject();
	virtual void show() = 0;
};

class IsaacObjectBase
{
protected:
	DWORD dwType;  // 对象分类
	FLOAT fXPos;   // 横坐标
	FLOAT fYPos;   // 纵坐标
	FLOAT fXSpeed; // 横坐标移动速度
	FLOAT fYSpeed; // 纵坐标移动速度
	IsaacObjectBase(DWORD gameObjectAdd);

	void show();

public:
	static DWORD getObjectType(DWORD gameObjectAdd);

	FLOAT getXPos();
	FLOAT getYPos();
	FLOAT getXSpeed();
	FLOAT getYSpeed();
};

class IsaacCharactor
	: public IIsaacObject,
	  public IsaacObjectBase
{
protected:
	DWORD dwHealthLimit; // 红心上限
	DWORD dwHealth;		 // 红心
	DWORD dwHealthEx;	 // 白心/金心/腐心等
	DWORD dwSheild;		 // 护盾
	DWORD dwKey;		 // 钥匙
	DWORD dwBomb;		 // 炸弹
	DWORD dwGold;		 // 金币
	DWORD dwCharId;		 // 角色id
	DWORD dwItemId;		 // 主动道具id
	DWORD dwCharge;		 // 主动道具充能
	DWORD dwTrinketId;	 // 饰品id
	DWORD dwPickupId;	 // 卡牌/药丸id
	DWORD dwPickupFlg;	 // 卡牌/药丸标志

public:
	IsaacCharactor(DWORD issacCharactorAdd);

	void show();

	DWORD getHealthLimit();
	DWORD getHealth();
	DWORD getHealthEx();
	DWORD getSheild();
	DWORD getKey();
	DWORD getBomb();
	DWORD getGold();
	DWORD getCharId();
	DWORD getItemId();
	DWORD getCharge();
	DWORD getTrinketId();
	DWORD getPickupId();
	DWORD getPickupFlg();
};

class IsaacTears
	: public IIsaacObject,
	  public IsaacObjectBase
{
protected:
	DWORD dwTearsType; // 弹幕类型

public:
	IsaacTears(DWORD isaacTearsAdd);

	void show();

	DWORD getTearsType();
};

class IsaacFamiliar
	: public IIsaacObject,
	  public IsaacObjectBase
{
protected:
public:
	IsaacFamiliar(DWORD isaacFamiliarAdd);

	void show();
};

class IsaacItem
	: public IIsaacObject,
	  public IsaacObjectBase
{
protected:
	DWORD dwItemType; // 道具分类
	DWORD dwItemId;	  // 道具id

public:
	IsaacItem(DWORD isaacItemAdd);

	void show();

	DWORD getItemType();
	DWORD getItemId();
};

class EnemyInfo
{
public:
	DWORD dwEnemyId;
	CHAR enemyName[32];
	CHAR moveMethod[32];
	CHAR attachMethod[32];

	EnemyInfo(DWORD enemyInfoAdd);
};

class IsaacEnemy
	: public IIsaacObject,
	  public IsaacObjectBase,
	  public EnemyInfo
{
protected:
	FLOAT fHealth; // 血量

public:
	IsaacEnemy(DWORD issacEnemyAdd);

	void show();

	FLOAT getHealth();
};