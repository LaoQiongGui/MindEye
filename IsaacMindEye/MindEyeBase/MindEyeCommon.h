#pragma once
#define DEBUG_MODE
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT           // 开启spdlog的wchar支持

#include <Windows.h>
#include <xaudio2.h>
#include <xapobase.h>

#ifdef DEBUG_MODE
#define MYDEBUG(x) x
#else
#define MYDEBUG(x)
#endif

// 全局变量
extern CHAR *logStr;
