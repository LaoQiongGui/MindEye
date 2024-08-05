#include "Common.h"

DWORD findPIDByName(LPWSTR wName)
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32 = {};
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // 创建进程快照
    hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }
    Process32First(hSnapshot, &pe32);
    do
    {
        // 进程名匹配成功返回进程id
        if (wcsstr(pe32.szExeFile, wName) != NULL)
        {
            ::CloseHandle(hSnapshot);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hSnapshot, &pe32));

    // 进程名匹配失败返回NULL
    ::CloseHandle(hSnapshot);
    return NULL;
}

BOOL GetModuleInfoByName(DWORD dwPID, const WCHAR *wModuleName, MODULEENTRY32 *pMe32)
{
    // 进程id为NULL代表自身进程
    if (dwPID == NULL)
    {
        dwPID = ::GetCurrentProcessId();
    }

    // 模块名小写缓冲区
    WCHAR wModulePathLower[MAX_PATH] = L"";
    WCHAR wModuleNameLookForLower[MAX_PATH] = L"";
    wcscpy_s(wModuleNameLookForLower, MAX_PATH, wModuleName);
    _wcslwr_s(wModuleNameLookForLower, MAX_PATH);

    // 获取进程快照
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwPID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    // 遍历句柄
    BOOL bRet = ::Module32First(hSnapshot, pMe32);
    if (bRet)
    {
        do
        {
            // 模块名转小写
            wcscpy_s(wModulePathLower, MAX_PATH, pMe32->szExePath);
            _wcslwr_s(wModulePathLower, MAX_PATH);
            if (wcsstr(wModulePathLower, wModuleNameLookForLower) != NULL)
            {
                // 查找到模块，成功返回
                ::CloseHandle(hSnapshot);
                return TRUE;
            }
        } while (::Module32Next(hSnapshot, pMe32));
    }

    // 未查到到模块，失败返回
    ::CloseHandle(hSnapshot);
    return FALSE;
}

VOID ClearConsole()
{
    HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwCharsWritten;
    DWORD dwConSize;

    ::GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    ::FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &dwCharsWritten);
    ::FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &dwCharsWritten);
    ::SetConsoleCursorPosition(hConsole, coordScreen);
    return;
}

BOOL CALLBACK FindWindowByNameProc(HWND hwnd, LPARAM lParam)
{
    WindowMatchStruct *windowMatchStruct = (WindowMatchStruct *)lParam;

    WCHAR wWindowName[MAX_PATH] = L"";
    ::GetWindowText(hwnd, wWindowName, MAX_PATH);
    if (wcsstr(wWindowName, windowMatchStruct->wWindowName))
    {
        windowMatchStruct->hWnd = hwnd;
        windowMatchStruct->successFlg = TRUE;
        return FALSE;
    }
    return TRUE;
}

CHAR Num2SingleChar(DWORD dwNum)
{
    if (dwNum < 10)
    {
        return (CHAR)(dwNum + '0');
    }
    else
    {
        return (CHAR)(dwNum + 'A' - 10);
    }
}

void splitStr(std::string &strIn, const char seprator, std::vector<std::string> &strsOut)
{
    strsOut.clear();
    DWORD dwPos = 0;
    for (DWORD i = 0; i < strIn.length(); i++)
    {
        if (strIn[i] == seprator)
        {
            std::string strTmp = strIn.substr(dwPos, i - dwPos);
            strsOut.push_back(strTmp);
            dwPos = i + 1;
        }
    }
    if (dwPos != strIn.length())
    {
        std::string strTmp = strIn.substr(dwPos, strIn.length() - dwPos);
        strsOut.push_back(strTmp);
    }
    return;
}

UINT64 featureCodeMatch(const WCHAR *wModuleName, const BYTE *featureCode, UINT64 featureCodeLength)
{
    UINT64 qwBaseAddr = NULL;
    UINT64 qwBaseSize = 0xFFFFFFFF;

    // 获取模块信息
    if (wModuleName != NULL)
    {
        MODULEENTRY32 me32 = {};
        me32.dwSize = sizeof(MODULEENTRY32);
        if (!GetModuleInfoByName(NULL, wModuleName, &me32))
        {
            return NULL;
        }
        qwBaseAddr = (UINT64)(me32.modBaseAddr);
        qwBaseSize = me32.modBaseSize;
        DEBUG(::wprintf_s(L"模块名称：%s\n", (const WCHAR *)me32.szExePath);)
    }
    DEBUG(::printf_s("模块基址：%I64X    模块大小：%I64X\n", qwBaseAddr, qwBaseSize);)

    for (UINT64 qwAddr = qwBaseAddr; qwAddr < qwBaseAddr + qwBaseSize - featureCodeLength; qwAddr++)
    {
        if (::memcmp(featureCode, (LPVOID)qwAddr, featureCodeLength) == 0)
        {
            return qwAddr;
        }
    }
    return NULL;
}

HANDLE MindEyeExceptionHandler::hExceptionHandler = NULL;
BreakPoint *MindEyeExceptionHandler::pLastBreakPoint = NULL;
std::vector<BreakPoint> MindEyeExceptionHandler::softBreakList;
std::vector<BreakPoint> MindEyeExceptionHandler::hardBreakList(4, BreakPoint());
std::vector<BreakPoint> MindEyeExceptionHandler::pageGuardList;

LONG NTAPI MindEyeExceptionHandler::ExceptionHandler(_EXCEPTION_POINTERS *ExceptionInfo)
{
    QWORD qwExceptionAddr = (QWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress;
    switch (ExceptionInfo->ExceptionRecord->ExceptionCode)
    {
    // 软件断点
    case EXCEPTION_BREAKPOINT:
    {
        for (const auto &breakPoint : softBreakList)
        {
            if (breakPoint.address == qwExceptionAddr)
            {
                // 改回原代码
                DWORD dwProtect;
                ::VirtualProtect((LPVOID)breakPoint.address, 1, PAGE_EXECUTE_READWRITE, &dwProtect);
                ::memcpy_s((LPVOID)breakPoint.address, 1, &breakPoint.bCode, 1);
                ::VirtualProtect((LPVOID)breakPoint.address, 1, dwProtect, &dwProtect);

                // 执行异常处理
                LONG lRet = breakPoint.ExceptionHandler(ExceptionInfo);

                // 一次性断点则移除断点
                if (breakPoint.singleFlg)
                {
                    softBreakList.erase(softBreakList.begin() + ((QWORD)&breakPoint - (QWORD)softBreakList.data()) / sizeof(BreakPoint));
                }
                // 非一次性断点设置单步执行并记录
                else
                {
                    ExceptionInfo->ContextRecord->EFlags |= 0x00000100;
                    pLastBreakPoint = new BreakPoint(breakPoint);
                }

                // 回到断点位置执行
                return lRet;
            }
        }
        return EXCEPTION_CONTINUE_SEARCH;
        break;
    }
    // 硬件断点
    case STATUS_SINGLE_STEP:
    {
        // 其他断点引发的单步执行
        if (pLastBreakPoint != NULL)
        {
            DWORD dwProtect;
            BYTE bSoftBreak = '\xCC';
            if (pLastBreakPoint->dwType & SOFTBREAK)
            {
                // 恢复软件断点
                ::VirtualProtect((LPVOID)pLastBreakPoint->address, 1, PAGE_EXECUTE_READWRITE, &dwProtect);
                ::memcpy_s((LPVOID)pLastBreakPoint->address, 1, &bSoftBreak, 1);
                ::VirtualProtect((LPVOID)pLastBreakPoint->address, 1, dwProtect, &dwProtect);
                delete pLastBreakPoint;
                pLastBreakPoint = NULL;
                return EXCEPTION_CONTINUE_EXECUTION;
            }
            else if (pLastBreakPoint->dwType & HARDBREAK)
            {
                // 恢复硬件断点
                for (DWORD i = 0; i < hardBreakList.size(); i++)
                {
                    if (hardBreakList.at(i).address == pLastBreakPoint->address)
                    {
                        ExceptionInfo->ContextRecord->Dr7 |= (0x00000001ULL << (i * 2));
                        delete pLastBreakPoint;
                        pLastBreakPoint = NULL;
                        return EXCEPTION_CONTINUE_EXECUTION;
                    }
                }
                return EXCEPTION_CONTINUE_SEARCH;
            }
            else if (pLastBreakPoint->dwType & PAGEGUARD)
            {
                // 恢复页守护
                delete pLastBreakPoint;
                pLastBreakPoint = NULL;
                return EXCEPTION_CONTINUE_EXECUTION;
            }
            else
            {
                return EXCEPTION_CONTINUE_SEARCH;
            }
        }

        // 硬件断点处理
        for (DWORD i = 0; i < hardBreakList.size(); i++)
        {
            auto &breakPoint = hardBreakList.at(i);
            if (breakPoint.address == qwExceptionAddr)
            {
                LONG lRet = breakPoint.ExceptionHandler(ExceptionInfo);
                // 一次性断点则移除断点
                if (breakPoint.singleFlg)
                {
                    breakPoint = BreakPoint();
                    removeHardBreakPoint(i);
                }
                // 非一次性断点设置单步执行并记录
                else
                {
                    ExceptionInfo->ContextRecord->EFlags |= 0x00000100;
                    pLastBreakPoint = new BreakPoint(breakPoint);
                }
                return lRet;
            }
        }
        return EXCEPTION_CONTINUE_SEARCH;
    }
    // PAGE GUARD
    case EXCEPTION_GUARD_PAGE:
    {
        // TODO：PAGE GUARD处理
        return EXCEPTION_CONTINUE_SEARCH;
    }
    default:
    {
        return EXCEPTION_CONTINUE_SEARCH;
        break;
    }
    }
}

BOOL MindEyeExceptionHandler::setHardBreakPoint(BreakPoint breakPoint, DWORD dwSubscript)
{
    // 获取线程快照
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
    THREADENTRY32 te = {};
    te.dwSize = sizeof(THREADENTRY32);

    if (!::Thread32First(hSnapshot, &te))
    {
        printf_s("Thread32First\n");
        return FALSE;
    }

    DWORD dwCurrentProcessId = ::GetCurrentProcessId();
    do
    {
        // 跳过其他进程的线程
        if (te.th32OwnerProcessID != dwCurrentProcessId)
        {
            continue;
        }

        // 获取线程句柄
        HANDLE hThread = ::OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT, FALSE, te.th32ThreadID);
        if (hThread == NULL)
        {
            ::printf_s("获取线程句柄失败，错误代码：%08X\n", ::GetLastError());
            continue;
        }
        CONTEXT context = {};
        if (!::GetThreadContext(hThread, &context))
        {
            ::printf_s("获取线程上下文失败，错误代码：%08X\n", ::GetLastError());
            ::CloseHandle(hThread);
            continue;
        }

        switch (dwSubscript)
        {
        case 0:
            context.Dr0 = breakPoint.address;
            context.Dr7 &= 0xFFF0FFFF;
            context.Dr7 |= 0x00000001;
            // 访问断点
            if (breakPoint.dwType & HARDEXREAD)
            {
                context.Dr7 |= 0x00030000;
            }
            // 写入断点
            else if (breakPoint.dwType & HARDEXWRIT)
            {
                context.Dr7 |= 0x00010000;
            }
            // 默认为执行断点（不需要处理）
            break;
        case 1:
            context.Dr1 = breakPoint.address;
            context.Dr7 &= 0xFF0FFFFF;
            context.Dr7 |= 0x00000004;
            // 访问断点
            if (breakPoint.dwType & HARDEXREAD)
            {
                context.Dr7 |= 0x00300000;
            }
            // 写入断点
            else if (breakPoint.dwType & HARDEXWRIT)
            {
                context.Dr7 |= 0x00100000;
            }
            // 默认为执行断点（不需要处理）
            break;
        case 2:
            context.Dr2 = breakPoint.address;
            context.Dr7 &= 0xF0FFFFFF;
            context.Dr7 |= 0x00000010;
            // 访问断点
            if (breakPoint.dwType & HARDEXREAD)
            {
                context.Dr7 |= 0x03000000;
            }
            // 写入断点
            else if (breakPoint.dwType & HARDEXWRIT)
            {
                context.Dr7 |= 0x01000000;
            }
            // 默认为执行断点（不需要处理）
            break;
        case 3:
            context.Dr3 = breakPoint.address;
            context.Dr7 &= 0x0FFFFFFF;
            context.Dr7 |= 0x00000040;
            // 访问断点
            if (breakPoint.dwType & HARDEXREAD)
            {
                context.Dr7 |= 0x30000000;
            }
            // 写入断点
            else if (breakPoint.dwType & HARDEXWRIT)
            {
                context.Dr7 |= 0x10000000;
            }
            // 默认为执行断点（不需要处理）
            break;
        default:
            return FALSE;
        }

        ::SetThreadContext(hThread, &context);
        ::CloseHandle(hThread);
        printf_s("设置线程上下文成功 Dr0：%I64X Dr7：%I64X。\n", context.Dr0, context.Dr7);
    } while (::Thread32Next(hSnapshot, &te));

    ::CloseHandle(hSnapshot);
    return TRUE;
}

BOOL MindEyeExceptionHandler::removeHardBreakPoint(DWORD dwSubscript)
{
    // 获取线程快照
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
    THREADENTRY32 te = {};
    te.dwSize = sizeof(THREADENTRY32);

    if (!::Thread32First(hSnapshot, &te))
    {
        return FALSE;
    }

    DWORD dwCurrentProcessId = ::GetCurrentProcessId();
    do
    {
        // 跳过其他进程的线程
        if (te.th32OwnerProcessID != dwCurrentProcessId)
        {
            continue;
        }
        // 获取线程句柄
        HANDLE hThread = ::OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT, FALSE, te.th32ThreadID);
        if (hThread == NULL)
        {
            continue;
        }
        CONTEXT context = {};
        if (!::GetThreadContext(hThread, &context))
        {
            ::CloseHandle(hThread);
            continue;
        }

        switch (dwSubscript)
        {
        case 0:
            context.Dr0 = NULL;
            context.Dr7 &= 0xFFFFFFFC;
            break;
        case 1:
            context.Dr1 = NULL;
            context.Dr7 &= 0xFFFFFFF3;
            break;
        case 2:
            context.Dr2 = NULL;
            context.Dr7 &= 0xFFFFFFCF;
            break;
        case 3:
            context.Dr3 = NULL;
            context.Dr7 &= 0xFFFFFF3F;
            break;
        default:
            return FALSE;
        }

        if (!::SetThreadContext(hThread, &context))
        {
            ::printf_s("添加硬件断点失败\n");
        }
        ::CloseHandle(hThread);
    } while (::Thread32Next(hSnapshot, &te));

    ::CloseHandle(hSnapshot);
    return TRUE;
}

BOOL MindEyeExceptionHandler::AddBreakPoint(QWORD qwBreakPointAddr, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, DWORD dwType, BOOL singleFlg)
{
    BreakPoint breakPoint = BreakPoint(dwType, qwBreakPointAddr, ExceptionHandler, singleFlg);

    // 首次调用注册异常处理函数
    if (hExceptionHandler == NULL)
    {
        hExceptionHandler = ::AddVectoredExceptionHandler(1, MindEyeExceptionHandler::ExceptionHandler);
    }

    // 判断中断类型
    // 软件断点
    if (dwType & SOFTBREAK)
    {
        // 判断断点是否已存在
        for (const auto &breakPointTmp : softBreakList)
        {
            if (breakPointTmp.address == qwBreakPointAddr)
            {
                DEBUG(printf_s("WARNING：断点已存在。\n");)
                return FALSE;
            }
        }

        // 插入断点
        DWORD dwProtect;
        if (!::VirtualProtect((LPVOID)qwBreakPointAddr, 1, PAGE_EXECUTE_READWRITE, &dwProtect))
        {
            DEBUG(printf_s("更改读写权限失败，位置：%I64X，错误代码：%X。\n", qwBreakPointAddr, ::GetLastError());)
            return FALSE;
        }
        breakPoint.bCode = *(BYTE *)qwBreakPointAddr;
        softBreakList.push_back(breakPoint);

        // 添加软件断点
        BYTE bSoftBreak = '\xCC';
        ::memcpy_s((LPVOID)qwBreakPointAddr, 1, &bSoftBreak, 1);
        ::VirtualProtect((LPVOID)qwBreakPointAddr, 1, dwProtect, &dwProtect);
        return TRUE;
    }
    // 硬件断点
    else if (dwType & HARDBREAK)
    {
        // 判断断点是否已存在
        for (const auto &breakPointTmp : softBreakList)
        {
            if (breakPointTmp.address == qwBreakPointAddr)
            {
                DEBUG(printf_s("WARNING：断点已存在。\n");)
                return FALSE;
            }
        }

        // 遍历硬件断点
        for (DWORD i = 0; i < hardBreakList.size(); i++)
        {
            if (hardBreakList.at(i).dwType == NULL)
            {
                // 设置空闲的硬件断点
                hardBreakList.at(i) = breakPoint;
                return setHardBreakPoint(breakPoint, i);
            }
        }

        // 硬件断点已满
        return FALSE;
    }
    // PAGE GUARD
    else if (dwType & PAGEGUARD)
    {
        // TODO：添加PAGE GUARD
        return FALSE;
    }
    else
    {
        return FALSE;
    }
}

MindEyeExceptionHandler::MindEyeExceptionHandler()
{
}

MindEyeExceptionHandler::~MindEyeExceptionHandler()
{
}

BreakPoint32::BreakPoint32()
{
    this->dwType = NULL;
    this->address = NULL;
    this->ExceptionHandler = NULL;
    this->singleFlg = NULL;
    this->bCode = NULL;
    return;
}

BreakPoint32::BreakPoint32(DWORD dwBPType, DWORD dwAddress, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, BOOL singleFlg)
{
    this->dwType = dwBPType;
    this->address = dwAddress;
    this->ExceptionHandler = ExceptionHandler;
    this->singleFlg = singleFlg;
    this->bCode = NULL;
    return;
}

BreakPoint64::BreakPoint64()
{
    this->dwType = NULL;
    this->address = NULL;
    this->ExceptionHandler = NULL;
    this->singleFlg = NULL;
    this->bCode = NULL;
    return;
}

BreakPoint64::BreakPoint64(DWORD dwBPType, QWORD qwAddress, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, BOOL singleFlg)
{
    this->dwType = dwBPType;
    this->address = qwAddress;
    this->ExceptionHandler = ExceptionHandler;
    this->singleFlg = singleFlg;
    this->bCode = NULL;
    return;
}
