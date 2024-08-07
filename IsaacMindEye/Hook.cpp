#include "Hook.h"

LPVOID lpSwapBuffers = NULL;
LPVOID lpGlDrawElements = NULL;
LPVOID lpGlBindTexture = NULL;

BOOL Hook()
{
    // 加载DLL
    HMODULE hModGdi = ::LoadLibraryA("gdi32full.dll");
    HMODULE hModOpengl = ::LoadLibraryA("opengl32.dll");

    // HOOK SwapBuffers函数
    lpSwapBuffers = (LPVOID)::GetProcAddress(hModGdi, "SwapBuffers");
    if (lpSwapBuffers == NULL)
    {
        // 卸载DLL并删除opengl环境
        ::FreeLibrary(hModGdi);
        ::FreeLibrary(hModOpengl);
        return FALSE;
    }
    NewFunctions::fpSwapBuffers = (NewFunctions::SWAPBUFFERS)InlineHook::Hook(lpSwapBuffers, NewFunctions::SwapBuffers, 7);
    if (NewFunctions::fpSwapBuffers == NULL)
    {
        // 卸载DLL并删除opengl环境
        ::FreeLibrary(hModGdi);
        ::FreeLibrary(hModOpengl);
        return FALSE;
    }

    // HOOK glDrawElements函数
    lpGlDrawElements = (LPVOID)::GetProcAddress(hModOpengl, "glDrawElements");
    if (lpGlDrawElements == NULL)
    {
        // 卸载DLL并删除opengl环境
        ::FreeLibrary(hModGdi);
        ::FreeLibrary(hModOpengl);
        return FALSE;
    }
    NewFunctions::fpGlDrawElements = (NewFunctions::GLDRAWELEMENTS)InlineHook::Hook(lpGlDrawElements, NewFunctions::glDrawElements, 5);
    if (NewFunctions::fpGlDrawElements == NULL)
    {
        // 卸载DLL并删除opengl环境
        ::FreeLibrary(hModGdi);
        ::FreeLibrary(hModOpengl);
        return FALSE;
    }

    // HOOK glBindTexture函数
    lpGlBindTexture = (LPVOID)::GetProcAddress(hModOpengl, "glBindTexture");
    if (lpGlBindTexture == NULL)
    {
        // 卸载DLL并删除opengl环境
        ::FreeLibrary(hModGdi);
        ::FreeLibrary(hModOpengl);
        return FALSE;
    }
    NewFunctions::fpGlBindTexture = (NewFunctions::GLBINDTEXTURE)InlineHook::Hook(lpGlBindTexture, NewFunctions::glBindTexture, 5);
    if (NewFunctions::fpGlBindTexture == NULL)
    {
        // 卸载DLL并删除opengl环境
        ::FreeLibrary(hModGdi);
        ::FreeLibrary(hModOpengl);
        return FALSE;
    }

    // 卸载DLL并删除opengl环境
    ::FreeLibrary(hModGdi);
    ::FreeLibrary(hModOpengl);
    return TRUE;
}

BOOL Unhook()
{
    // 解除HOOK SwapBuffers函数
    if (!InlineHook::Unhook(lpSwapBuffers, NewFunctions::fpSwapBuffers, 7))
    {
        return FALSE;
    }
    NewFunctions::fpSwapBuffers = NULL;

    // 解除HOOK glDrawElements函数
    if (!InlineHook::Unhook(lpGlDrawElements, NewFunctions::fpGlDrawElements, 5))
    {
        return FALSE;
    }
    NewFunctions::fpGlDrawElements = NULL;

    // 解除HOOK glBindTexture函数
    if (!InlineHook::Unhook(lpGlBindTexture, NewFunctions::fpGlBindTexture, 5))
    {
        return FALSE;
    }
    NewFunctions::fpGlBindTexture = NULL;

    return TRUE;
}