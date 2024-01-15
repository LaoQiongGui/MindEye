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

LRESULT ChangeShowModeProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HANDLE hEventConsolePause;
    switch (Msg)
    {
    case WM_KEYDOWN:
        // 记录已按下的按键，避免重复触发
        if (pressedKeySet.find(wParam) != pressedKeySet.end())
        {
            break;
        }
        else
        {
            pressedKeySet.insert(wParam);
        }
        switch (wParam)
        {
        case VK_UP:
            if (::GetKeyState(VK_CONTROL) & 0xF0000000)
            {
                IsaacGame::begin()->preShowMode();
                return 0;
            }
            break;
        case VK_DOWN:
            if (::GetKeyState(VK_CONTROL) & 0xF0000000)
            {
                IsaacGame::begin()->nextShowMode();
                return 0;
            }
            break;
        // F1暂停控制台刷新
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
            return 0;
            break;
        default:
            break;
        }
        break;
    case WM_KEYUP:
        // 按键松开则移除记录
        pressedKeySet.erase(wParam);
    default:
        break;
    }
    return oldConsoleProc(hWnd, Msg, wParam, lParam);
}
