#define DEBUG_MODE
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT           // 开启spdlog的wchar支持
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // 开启spdlog的文件名+行号打印

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <functional>
#include <set>
#include <map>
#include <algorithm>
#include <exception>
#include <Windows.h>
#include <WinUser.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <process.h>
#include <WinUser.h>
#include <d2d1.h>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xapobase.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <profileapi.h>
#include <fftw3.h>
#include <roapi.h>
#include <sapi.h>
#include <sphelper.h>

#ifdef DEBUG_MODE
#define MYDEBUG(x) x
#else
#define MYDEBUG(x)
#endif

// 全局变量
extern std::shared_ptr<spdlog::logger> logger;
extern CHAR *logStr;
