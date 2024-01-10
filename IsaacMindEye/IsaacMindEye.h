#pragma once
#include "Common.h"
#include "NewFunctions.h"
#include "InlineHook.h"
#include "Hook.h"
#include "Timer.h"
#include "IsaacGame.h"

DWORD dwNvoglvBaseAdd = NULL;
DWORD dwNvOglObj = NULL;
WNDPROC oldConsoleProc = NULL;

VOID MindEyeMain();
BOOL Hook();
BOOL Unhook();
DWORD GetNvOglObj();
LONG NTAPI EHGetNvOglObj(_EXCEPTION_POINTERS *ExceptionInfo);
LRESULT ChangeShowModeProc(HWND, UINT, WPARAM, LPARAM);
