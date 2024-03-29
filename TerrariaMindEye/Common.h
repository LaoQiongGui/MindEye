#pragma once
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <d3d9.h>

struct WindowMatchStruct
{
    const WCHAR* wWindowName;
    HWND hWnd;
};

// 全局变量
extern std::shared_ptr<spdlog::logger> logger;
