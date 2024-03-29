#include "IsaacObject.h"

IsaacObjectBase::IsaacObjectBase(DWORD gameObjectAdd)
{
	dwType = *(DWORD *)(gameObjectAdd + 0x0028);
	fXPos = *(FLOAT *)(gameObjectAdd + 0x0294);
	fYPos = *(FLOAT *)(gameObjectAdd + 0x0298);
	fXSpeed = *(FLOAT *)(gameObjectAdd + 0x02B8);
	fYSpeed = *(FLOAT *)(gameObjectAdd + 0x02BC);
}

DWORD IsaacObjectBase::getObjectType(DWORD gameObjectAdd)
{
	return *(DWORD *)(gameObjectAdd + 0x0028);
}

FLOAT IsaacObjectBase::getXPos()
{
	return fXPos;
}

FLOAT IsaacObjectBase::getYPos()
{
	return fYPos;
}

FLOAT IsaacObjectBase::getXSpeed()
{
	return fXSpeed;
}

FLOAT IsaacObjectBase::getYSpeed()
{
	return fYSpeed;
}

void IsaacObjectBase::show()
{
	printf_s("  横坐标：%4.1f  ", fXPos);
	printf_s("  纵坐标：%4.1f  ", fYPos);
	printf_s("横向速度：%4.1f  ", fXSpeed);
	printf_s("纵向速度：%4.1f\n", fYSpeed);
}

IsaacCharactor::IsaacCharactor(DWORD issacCharactorAdd)
	: IsaacObjectBase(issacCharactorAdd)
{
	dwHealthLimit = *(DWORD *)(issacCharactorAdd + 0x1290);
	dwHealth = *(DWORD *)(issacCharactorAdd + 0x1294);
	dwHealthEx = *(DWORD *)(issacCharactorAdd + 0x1298);
	dwSheild = *(DWORD *)(issacCharactorAdd + 0x129C);
	dwKey = *(DWORD *)(issacCharactorAdd + 0x12AC);
	dwBomb = *(DWORD *)(issacCharactorAdd + 0x12B4);
	dwGold = *(DWORD *)(issacCharactorAdd + 0x12B8);
	dwCharId = *(DWORD *)(issacCharactorAdd + 0x130C);
	dwItemId = *(DWORD *)(issacCharactorAdd + 0x14C4);
	dwCharge = *(DWORD *)(issacCharactorAdd + 0x14C8);
	dwTrinketId = *(DWORD *)(issacCharactorAdd + 0x15E8);
	dwPickupId = *(DWORD *)(issacCharactorAdd + 0x16C8);
	dwPickupFlg = *(DWORD *)(issacCharactorAdd + 0x16CC);
}

void IsaacCharactor::show()
{
	printf_s("人物\n");
	printf_s("红心上限：%2d  ", dwHealthLimit);
	printf_s("    红心：%2d  ", dwHealth);
	printf_s("    圣心：%2d  ", dwHealthEx);
	printf_s("    护盾：%2d\n", dwSheild);
	printf_s("    金币：%2d  ", dwGold);
	printf_s("    炸弹：%2d  ", dwBomb);
	printf_s("    钥匙：%2d\n", dwKey);
	IsaacObjectBase::show();
}

DWORD IsaacCharactor::getHealthLimit()
{
	return dwHealthLimit;
}

DWORD IsaacCharactor::getHealth()
{
	return dwHealth;
}

DWORD IsaacCharactor::getHealthEx()
{
	return dwHealthEx;
}

DWORD IsaacCharactor::getSheild()
{
	return dwSheild;
}

DWORD IsaacCharactor::getKey()
{
	return dwKey;
}

DWORD IsaacCharactor::getBomb()
{
	return dwBomb;
}

DWORD IsaacCharactor::getGold()
{
	return dwGold;
}

DWORD IsaacCharactor::getCharId()
{
	return dwCharId;
}

DWORD IsaacCharactor::getItemId()
{
	return dwItemId;
}

DWORD IsaacCharactor::getCharge()
{
	return dwCharge;
}

DWORD IsaacCharactor::getTrinketId()
{
	return dwTrinketId;
}

DWORD IsaacCharactor::getPickupId()
{
	return dwPickupId;
}

DWORD IsaacCharactor::getPickupFlg()
{
	return dwPickupFlg;
}
IsaacTears::IsaacTears(DWORD isaacTearsAdd)
	: IsaacObjectBase(isaacTearsAdd)
{
	dwTearsType = NULL;
}

void IsaacTears::show()
{
	printf_s("弹幕类型：%d\n", dwTearsType);
	IsaacObjectBase::show();
}

DWORD IsaacTears::getTearsType()
{
	return dwTearsType;
}

IsaacFamiliar::IsaacFamiliar(DWORD isaacFamiliarAdd)
	: IsaacObjectBase(isaacFamiliarAdd)
{
}

void IsaacFamiliar::show()
{
	printf_s("随从\n");
	IsaacObjectBase::show();
}

IsaacItem::IsaacItem(DWORD isaacItemAdd)
	: IsaacObjectBase(isaacItemAdd)
{
	dwItemType = *(DWORD *)(isaacItemAdd + 0x0028);
	dwItemId = *(DWORD *)(isaacItemAdd + 0x0030);
}

void IsaacItem::show()
{
	printf_s("道具id：%d\n", dwItemId);
	IsaacObjectBase::show();
}

DWORD IsaacItem::getItemType()
{
	return dwItemType;
}

DWORD IsaacItem::getItemId()
{
	return dwItemId;
}

IsaacEnemy::IsaacEnemy(DWORD issacEnemyAdd)
	: IsaacObjectBase(issacEnemyAdd),
	  EnemyInfo(*(DWORD *)(issacEnemyAdd + 0x0288))
{
	fHealth = *(FLOAT *)(issacEnemyAdd + 0x02D8);
}

void IsaacEnemy::show()
{
	printf_s("怪物名称：%s\n", enemyName);
	IsaacObjectBase::show();
}

FLOAT IsaacEnemy::getHealth()
{
	return fHealth;
}

EnemyInfo::EnemyInfo(DWORD enemyInfoAdd)
{
	dwEnemyId = *(DWORD *)(enemyInfoAdd + 0x0000);
	::memset(enemyName, 0, 32);
	::strcpy_s(enemyName, (CHAR *)(enemyInfoAdd + 0x000C));
	::memset(moveMethod, 0, 32);
	::strcpy_s(moveMethod, (CHAR *)(enemyInfoAdd + 0x0110));
	::memset(attachMethod, 0, 32);
	::strcpy_s(attachMethod, (CHAR *)(enemyInfoAdd + 0x0128));
}

IIsaacObject::~IIsaacObject()
{
}
