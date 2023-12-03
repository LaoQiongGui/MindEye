#pragma once
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <set>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <opengl/glew.h>

// 通过进程名查找进程ID

DWORD FindPIDByName(LPWSTR wName);

// 获取进程已加载的模块信息

BOOL GetModuleInfoByName(DWORD dwPID, const WCHAR *wModuleName, MODULEENTRY32 *pMe32);

struct WindowMatchStruct
{
    const WCHAR* wWindowName = NULL;
    HWND hWnd = NULL;
    BOOL successFlg = FALSE;
};

// 全局变量
extern std::shared_ptr<spdlog::logger> logger;
extern DWORD g_dwRenderThreadId; // 渲染线程id
extern HANDLE g_hRenderThread; // 渲染线程句柄
