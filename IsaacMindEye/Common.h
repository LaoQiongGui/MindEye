#pragma once
#define DEBUG_MODE
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>

#ifdef _WIN32
// windows x86 or x68
#ifdef _WIN64 // x64 windows
#define BreakPoint BreakPoint64
#else // x86 windows
#define BreakPoint BreakPoint32
#endif // end of _WIN64
#endif // end of _WIN32

#ifdef DEBUG_MODE
// DEBUG_MODE
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif // end of DEBUG_MODE

typedef unsigned __int64 QWORD;

/**
 * 通过进程名查找进程ID.
 *
 * \param wName：进程名（部分包含）
 * \return 非NULL：进程id NULL：匹配失败
 */
DWORD findPIDByName(LPWSTR wName);

/**
 * 获取进程已加载的模块信息.
 *
 * \param dwPID：进程ID，NULL代表自身进程
 * \param wModuleName：查找的模块名称（忽略大小写）
 * \param pMe32：查找到的模块信息
 * \return 找到模块返回TRUE 未找到返回FALSE
 */
BOOL GetModuleInfoByName(DWORD dwPID, const WCHAR *wModuleName, MODULEENTRY32 *pMe32);

/**
 * 控制台清屏.
 *
 * \return 无
 */
void ClearConsole();

/**
 * 查找窗口回调.
 *
 * \param hwnd：当前遍历的窗口句柄
 * \param lParam：使用WindowMatchStruct结构体
 * \return FALSE时停止
 */
BOOL CALLBACK FindWindowByNameProc(HWND hwnd, LPARAM lParam);

/**
 * 数字转为单字符显示.
 *
 * \param dwNum：数字
 * \return：单字符 数字0-9转为字符0-9 数字10-35转为字符A-Z
 */
CHAR Num2SingleChar(DWORD dwNum);

/**
 * 大小端转换.
 *
 * \param pT：待转换的数组
 * \param dwBufferSize：数组长度（字节单位）
 * \return TRUE：转换成功
 */
template <typename T>
void endianConvert(T *pT, DWORD dwLength)
{
    DWORD dwSize = sizeof(T);
    T *tmpList = new T[dwLength]();
    for (DWORD i = 0; i < dwLength; i++)
    {
        for (DWORD j = 0; j < dwSize; j++)
        {
            ((BYTE *)tmpList)[i * dwSize + j] = ((BYTE *)pT)[i * dwSize + dwSize - 1 - j];
        }
    }
    ::memcpy_s(pT, dwLength * sizeof(T), tmpList, dwLength * sizeof(T));
    delete[] tmpList;
}

/**
 * 字符串分割.
 *
 * \param strIn：待分割字符串
 * \param seprator：分隔符
 * \param strsOut：分割结果
 */
void splitStr(std::string &strIn, const char seprator, std::vector<std::string> &strsOut);

/**
 * 匹配特征码.
 *
 * \param featureCode：特征码
 * \param wModuleName：模块名（范围匹配） NULL（全内存匹配）
 * \return 非NULL：匹配到的地址 NULL：匹配失败
 */
UINT64 featureCodeMatch(const WCHAR *wModuleName, const BYTE *featureCode, UINT64 featureCodeLength);

struct WindowMatchStruct
{
    const WCHAR *wWindowName = NULL;
    HWND hWnd = NULL;
    BOOL successFlg = FALSE;
};

struct BreakPoint32
{
    DWORD dwType;                                 // 断点类型
    DWORD address;                                // 断点地址
    PVECTORED_EXCEPTION_HANDLER ExceptionHandler; // 异常处理函数
    BOOL singleFlg;                               // 一次性标志
    BYTE bCode;                                   // 断点原代码

    BreakPoint32();
    BreakPoint32(DWORD dwBPType, DWORD dwAddress, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, BOOL singleFlg);
};

struct BreakPoint64
{
    DWORD dwType;                                 // 断点类型
    QWORD address;                                // 断点地址
    PVECTORED_EXCEPTION_HANDLER ExceptionHandler; // 异常处理函数
    BOOL singleFlg;                               // 一次性标志
    BYTE bCode;                                   // 断点原代码

    BreakPoint64();
    BreakPoint64(DWORD dwBPType, QWORD qwAddress, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, BOOL singleFlg);
};

class MindEyeExceptionHandler
{
private:
    static HANDLE hExceptionHandler;
    static BreakPoint *pLastBreakPoint;
    static std::vector<BreakPoint> softBreakList;
    static std::vector<BreakPoint> hardBreakList;
    static std::vector<BreakPoint> pageGuardList;

    static LONG NTAPI ExceptionHandler(_EXCEPTION_POINTERS *ExceptionInfo);

    /**
     * 设置硬件断点.
     *
     * \param breakPoint：断点信息
     * \param dwSubscript：断点下标 0-3
     * \return TRUE：成功添加断点 FALSE：添加断点失败
     */
    static BOOL setHardBreakPoint(BreakPoint breakPoint, DWORD dwSubscript);

    /**
     * 删除硬件断点.
     *
     * \param dwSubscript：断点下标 0-3
     * \return TRUE：成功移除断点 FALSE：移除断点失败
     */
    static BOOL removeHardBreakPoint(DWORD dwSubscript);

public:
    /** 软件断点 */
    static const DWORD SOFTBREAK = 0x00000001;
    /** 硬件断点 */
    static const DWORD HARDBREAK = 0x00000002;
    /** 页面守护 */
    static const DWORD PAGEGUARD = 0x00000004;
    /** 硬件断点扩展：执行断点 */
    static const DWORD HARDEXEXEC = 0x00010000;
    /** 硬件断点扩展：访问断点 */
    static const DWORD HARDEXREAD = 0x00020000;
    /** 硬件断点扩展：写入断点 */
    static const DWORD HARDEXWRIT = 0x00040000;

    /**
     * 添加断点.
     *
     * \param qwBreakPointAddr：断点地址
     * \param ExceptionHandler：异常处理函数
     * \param dwType：断点类型 SOFTBREAK HARDBREAK PAGEGUARD 及各种扩展
     * \param singleFlg：是否是一次性断点
     * \return TRUE：断点添加成功 FALSE：断点添加失败
     */
    static BOOL AddBreakPoint(QWORD qwBreakPointAddr, PVECTORED_EXCEPTION_HANDLER ExceptionHandler, DWORD dwType, BOOL singleFlg);

private:
    MindEyeExceptionHandler();
    ~MindEyeExceptionHandler();
};
