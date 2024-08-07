#include "NewFunctions.h"

extern NewFunctions::CREATETHREAD NewFunctions::fpCreateThread = NULL;
extern NewFunctions::CREATEPROCESSA NewFunctions::fpCreateProcessA = NULL;
extern NewFunctions::SWAPBUFFERS NewFunctions::fpSwapBuffers = NULL;
extern NewFunctions::GLDRAWELEMENTS NewFunctions::fpGlDrawElements = NULL;
extern NewFunctions::GLBINDTEXTURE NewFunctions::fpGlBindTexture = NULL;

BOOL WINAPI NewFunctions::CreateProcessA(
    LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
    LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    return fpCreateProcessA(
        lpApplicationName, lpCommandLine, lpProcessAttributes,
        lpThreadAttributes, bInheritHandles, dwCreationFlags,
        lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

HANDLE NewFunctions::CreateThread(
    LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    HANDLE handle = NewFunctions::fpCreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
    return handle;
}
BOOL WINAPI NewFunctions::SwapBuffers(HDC unnamedParam1)
{
    // TODO：执行自己的代码

    // 执行原函数
    return NewFunctions::fpSwapBuffers(unnamedParam1);
}

void GLAPIENTRY NewFunctions::glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
{
    // TODO：执行自己的代码

    // 执行原函数
    return NewFunctions::fpGlDrawElements(mode, count, type, indices);
}

void GLAPIENTRY NewFunctions::glBindTexture(GLenum target, GLuint texture)
{
    // TODO：执行自己的代码

    // 执行原函数
    return NewFunctions::fpGlBindTexture(target, texture);
}
