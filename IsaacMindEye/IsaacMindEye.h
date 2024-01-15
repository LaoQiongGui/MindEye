#pragma once
#include "Common.h"
#include "NewFunctions.h"
#include "InlineHook.h"
#include "Hook.h"
#include "Timer.h"
#include "IsaacGame/IsaacGame.h"

WNDPROC oldConsoleProc = NULL;
std::set<WPARAM> pressedKeySet;

VOID MindEyeMain();
BOOL Hook();
BOOL Unhook();
LRESULT ChangeShowModeProc(HWND, UINT, WPARAM, LPARAM);
