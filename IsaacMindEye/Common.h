#pragma once
#define DEBUG_MODE
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <set>
#include <map>
#include <list>
#include <opengl/glew.h>

#ifdef DEBUG_MODE
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif // DEBUG_MODE

// 通过进程名查找进程ID

DWORD FindPIDByName(LPWSTR wName);

// 获取进程已加载的模块信息

BOOL GetModuleInfoByName(DWORD dwPID, const WCHAR *wModuleName, MODULEENTRY32 *pMe32);

// 控制台清屏

VOID ClearConsole();

// 查找窗口回调

BOOL CALLBACK FindWindowByNameProc(HWND hwnd, LPARAM lParam);

// 数字转为单字符显示

CHAR Num2SingleChar(DWORD dwNum);

struct WindowMatchStruct
{
    const WCHAR *wWindowName = NULL;
    HWND hWnd = NULL;
    BOOL successFlg = FALSE;
};

struct BreakPoint
{
    DWORD dwType;                                 // 断点类型
    DWORD dwAddress;                              // 断点地址
    PVECTORED_EXCEPTION_HANDLER ExceptionHandler; // 异常处理函数
    BOOL singleFlg;                               // 一次性标志
    BYTE bCode;                                   // 断点原代码

    BreakPoint();
    BreakPoint(DWORD dwBPType, DWORD dwAddress, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, BOOL singleFlg);
};

class MindEyeExceptionHandler
{
private:
    static HANDLE hExceptionHandler;
    static BreakPoint *pLastBreakPoint;
    static std::list<BreakPoint> breakPointList;

    static LONG NTAPI ExceptionHandler(_EXCEPTION_POINTERS *ExceptionInfo);

public:
    static const DWORD SOFTBREAK = 0x00000001;
    static const DWORD HARDBREAK = 0x00000002;
    static const DWORD PAGEGUARD = 0x00000003;

    static BOOL AddBreakPoint(DWORD dwBreakPointAdd, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, DWORD dwType, BOOL singleFlg);

private:
    MindEyeExceptionHandler();
    ~MindEyeExceptionHandler();
};
