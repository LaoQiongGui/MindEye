#pragma once
#include "Common.h"

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
	DWORD *pRooms[MAPHEIGHT][MAPWIDTH] = {0};

	IsaacGame();
	~IsaacGame();

	void loadMap(); // 加载游戏地图

public:
	static IsaacGame *begin(); // 开始访问游戏对象
	void end();				   // 结束访问游戏对象
	void refresh();			   // 获取最新的游戏状态
	void showMap();
};
