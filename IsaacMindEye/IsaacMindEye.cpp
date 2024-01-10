#include "pch.h"
#include "IsaacMindEye.h"

// 日志初始化
extern std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt("basic_logger", "logs/isaac_mindeye_log.txt");

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // 创建定时刷新线程
        ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainTimer, NULL, 0, NULL);
        // 创建主线程
        ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MindEyeMain, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

VOID MindEyeMain()
{
    BOOL bRet = TRUE;
    HMODULE hModSelf = NULL;
    ::GetModuleHandleEx(NULL, L"IsaacMindEye.dll", &hModSelf);

    // 日志初始化
    spdlog::set_level(spdlog::level::info);
    spdlog::flush_on(spdlog::level::err);
    spdlog::flush_every(std::chrono::seconds(5));

    // 创建控制台
    FILE *stream = NULL;
    ::AllocConsole();
    ::SetConsoleTitle(L"IssacDebugConsole");
    ::freopen_s(&stream, "CON", "r", stdin);
    ::freopen_s(&stream, "CON", "w", stdout);
    ::Sleep(40);

    // 查找游戏窗口
    WindowMatchStruct windowMatchStruct = {};
    windowMatchStruct.wWindowName = L"Binding of Isaac";
    windowMatchStruct.hWnd = NULL;
    ::EnumWindows(FindWindowByNameProc, (LPARAM)&windowMatchStruct);

    // 设置游戏窗口回调函数
    HANDLE hEventConsolePause = ::CreateEvent(NULL, TRUE, TRUE, L"IsaacConsolePause");
    oldConsoleProc = (WNDPROC)::GetWindowLongPtr(windowMatchStruct.hWnd, GWLP_WNDPROC);
    if (::SetWindowLongPtr(windowMatchStruct.hWnd, GWLP_WNDPROC, (LONG)ChangeShowModeProc) == NULL)
    {
        DWORD error = ::GetLastError();
        CHAR buffer[MAX_PATH] = "";
        sprintf_s(buffer, MAX_PATH, "%8X", error);
        ::MessageBoxA(0, buffer, 0, 0);
    }

    // HOOK
    if (!Hook())
    {
        // 卸载DLL
        ::MessageBox(0, L"HOOK失败", L"ERROR", 0);
        ::FreeLibraryAndExitThread(hModSelf, 0);
        return;
    }

    IsaacGame *pIsaacGame = IsaacGame::begin();

    HANDLE hEventMainTimer = ::OpenEvent(EVENT_ALL_ACCESS, TRUE, L"IsaacMainTimer");
    while (TRUE)
    {
        ::WaitForSingleObject(hEventMainTimer, INFINITE);
        ::WaitForSingleObject(hEventConsolePause, INFINITE);
        ClearConsole();
        pIsaacGame->refresh();
    }
    pIsaacGame->end();

    return;
}

/**
 * 获取NvOgl对象.
 *
 * \return NvOgl对象
 */
DWORD GetNvOglObj()
{
    // 获取nvoglv32.dll基址
    MODULEENTRY32 me32 = {};
    me32.dwSize = sizeof(MODULEENTRY32);
    DWORD dwPID = ::GetCurrentProcessId();
    GetModuleInfoByName(dwPID, L"nvoglv32.dll", &me32);
    dwNvoglvBaseAdd = (DWORD)me32.modBaseAddr;
    logger->info("nvoglvBaseAdd: {:#8X}", dwNvoglvBaseAdd);

    HANDLE hEvent = ::CreateEvent(NULL, TRUE, FALSE, L"GetNvOglObj");

    // 添加断点
    MindEyeExceptionHandler::AddBreakPoint(dwNvoglvBaseAdd + 0x0019C000, EHGetNvOglObj, MindEyeExceptionHandler::SOFTBREAK, TRUE);

    // 等待获取NvOgl对象
    ::WaitForSingleObject(hEvent, INFINITE);
    ::CloseHandle(hEvent);

    return dwNvOglObj;
}

/**
 * 获取NvOgl对象的异常回调.
 *
 * \param ExceptionInfo：异常
 * \return 固定EXCEPTION_CONTINUE_EXECUTION
 */
LONG NTAPI EHGetNvOglObj(_EXCEPTION_POINTERS *ExceptionInfo)
{
    __asm
    {
        PUSH ESI;
        MOV ESI, FS: [0x00000BF0];
        MOV dwNvOglObj, ESI;
        POP ESI;
    }
    logger->info("nvglObj: {:#8X}", dwNvOglObj);

    DWORD dwRenderFuncAdd = *(DWORD *)(dwNvOglObj + 0x000328BC);
    logger->info("dwRenderFuncAdd: {:#8X}", dwRenderFuncAdd);
    // 获取NvOgl对象事件同步
    HANDLE hEvent = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, L"GetNvOglObj");
    ::SetEvent(hEvent);
    ::CloseHandle(hEvent);

    return EXCEPTION_CONTINUE_EXECUTION;
}

LRESULT ChangeShowModeProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HANDLE hEventConsolePause;
    switch (Msg)
    {
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_F1:
            hEventConsolePause = ::OpenEvent(EVENT_ALL_ACCESS, TRUE, L"IsaacConsolePause");
            if (::WaitForSingleObject(hEventConsolePause, 0) == WAIT_OBJECT_0)
            {
                ::ResetEvent(hEventConsolePause);
            }
            else
            {
                ::SetEvent(hEventConsolePause);
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return oldConsoleProc(hWnd, Msg, wParam, lParam);
}
