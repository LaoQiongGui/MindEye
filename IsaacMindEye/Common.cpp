#include "pch.h"
#include "Common.h"

extern DWORD g_dwRenderThreadId = NULL;
extern HANDLE g_hRenderThread = NULL;

/**
 * 通过进程名查找进程ID.
 *
 * \param wName：进程名（部分包含）
 * \return 非NULL：进程id NULL：匹配失败
 */
DWORD FindPIDByName(LPWSTR wName)
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
        logger->debug(pe32.szExeFile);
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

/**
 * 获取进程已加载的模块信息.
 *
 * \param dwPID：进程ID
 * \param wModuleName：查找的模块名称（忽略大小写）
 * \param pMe32：查找到的模块信息
 * \return 找到模块返回TRUE 未找到返回FALSE
 */
BOOL GetModuleInfoByName(DWORD dwPID, const WCHAR *wModuleName, MODULEENTRY32 *pMe32)
{
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
