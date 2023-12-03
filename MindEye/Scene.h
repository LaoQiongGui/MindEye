#pragma once
#include "Common.h"
#include "PEAnalyze.h"

// 全局变量
// 当前场景
extern DWORD g_dwScene;

namespace Scene
{
	// 场景常量
	/** 主菜单 */
	static const DWORD MAINMENU = 0x00000000;
	/** 以撒的结合辅助 */
	static const DWORD ISAACCONSOLE = 0x01000000;
	/** 测试用 */
	static const DWORD TESTMENU = 0xFF000000;

	// 场景函数

	VOID MainMenu();
	VOID IsaacConsole();
	VOID TestMenu();

	// 事件函数

	VOID EvtRoute(DWORD dwScene);
	VOID EvtIsaacMindEyeStart();
	VOID EvtIsaacMindEyeEnd(DWORD dwProcessId);
}
