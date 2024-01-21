#pragma once
#include "../Common.h"
#include "IsaacRoom.h"
#include "IsaacObject.h"

class IsaacGame
{
private:
	static const DWORD GAMEOFFSET = 0x007FD65C;
	static const DWORD LEVELOFFSET = 0x00018190;
	static const DWORD MAPWIDTH = 13;
	static const DWORD MAPHEIGHT = 13;

	static IsaacGame *pIsaacGame;
	static DWORD dwCount;

	DWORD dwModuleBaseAdd;
	DWORD *pGame;
	DWORD *pLevel;
	DWORD dwStatus;
	DWORD map[MAPHEIGHT][MAPWIDTH] = {0};
	DWORD *pRoomEntries[MAPHEIGHT][MAPWIDTH] = {0};

	IsaacRoom *pIsaacRoom;

	IsaacGame();
	~IsaacGame();

	void loadMap();	 // 加载游戏地图
	void loadRoom(); // 加载当前房间

	/** 调试用变量·函数 */
	DWORD dwShowMode; // 显示模式

	void showInConsole(); // 在控制台中显示（调试）
	void showMap();		  // 显示地图（调试）

public:
	static IsaacGame *begin(); // 开始访问游戏对象
	void end();				   // 结束访问游戏对象
	void refresh();			   // 获取最新的游戏状态

	/** 调试用变量·函数 */
	static const DWORD SHOWNONE = 0x0000;	  // 不显示游戏信息
	static const DWORD SHOWMAP = 0x0001;	  // 显示地图
	static const DWORD SHOWROOM = 0x0002;	  // 显示当前房间
	static const DWORD SHOWOBJECTS = 0x0004;  // 显示当前房间
	static const DWORD SHOWDEFAULT = SHOWMAP; // 默认显示信息

	void preShowMode();
	void nextShowMode();
};
