#include "Scene.h"

CHAR buffer[MAX_PATH] = "C:\\Windows\\SysWOW64\\kernel32.dll";
WCHAR wBuffer[MAX_PATH] = L"";

VOID Scene::MainMenu()
{
    // 前处理

    // 页面布局

    BOOL bRouteIsaac = ImGui::Button("Isaac Console", {100, 40}); // 跳转至以撒辅助页面
    BOOL bRouteTest = ImGui::Button("Test", {100, 40});           // 跳转至测试页面

    // 页面响应

    if (bRouteIsaac)
    {
        Scene::EvtRoute(ISAACCONSOLE);
    }
    if (bRouteTest)
    {
        Scene::EvtRoute(TESTMENU);
    }

    // 后处理

    return;
}

VOID Scene::IsaacConsole()
{
    // 前处理

    DWORD dwPID = FindPIDByName((LPWSTR)L"isaac-ng.exe");

    // 页面布局

    BOOL bBack = ImGui::Button("Back", {100, 40}); // 返回主菜单
    BOOL bIsaacMindEyeStart = FALSE;
    BOOL bIsaacMindEyeEnd = FALSE;
    bIsaacMindEyeStart = ImGui::Button("Start Isaac MindEye.", { 200, 40 }); // 启动以撒的结合
    bIsaacMindEyeEnd = ImGui::Button("Terminate Isaac MindEye.", { 200, 40 }); // 关闭以撒的结合

    // 页面响应

    if (bBack)
    {
        Scene::EvtRoute(MAINMENU);
    }
    if (bIsaacMindEyeStart)
    {
        Scene::EvtIsaacMindEyeStart();
    }
    if (bIsaacMindEyeEnd)
    {
        Scene::EvtIsaacMindEyeEnd(dwPID);
    }

    // 后处理

    return;
}

VOID Scene::TestMenu()
{
    // 前处理

    // 页面布局

    BOOL bBack = ImGui::Button("Back", {100, 40}); // 返回主菜单
    ImGui::InputText("ModulePathInput", buffer, MAX_PATH, 0, NULL, NULL);
    BOOL bLoadPE = ImGui::Button("Load PE File", {200, 40});

    // 页面响应

    if (bBack)
    {
        Scene::EvtRoute(MAINMENU);
    }
    if (bLoadPE)
    {
        ::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), wBuffer, MAX_PATH);
        PortableExecutable PE = PortableExecutable(wBuffer);
        for (DWORD i = 0; i < PE.exportDirectory.NumberOfFunctions; i++)
        {
            printf_s("%08X %s\n", (DWORD)(PE.exportFunctionList[i].dwFunctionAddress), PE.exportFunctionList[i].functionName);
        }
    }

    // 后处理

    return;
}

/**
 * 场景跳转函数.
 *
 * \param DWORD：跳转目标画面ID的地址
 * \return 无返回值
 */
VOID Scene::EvtRoute(DWORD dwScene)
{
    g_dwScene = dwScene;
    return;
}

/**
 * 启动以撒的结合.
 *
 * \return 无返回值
 */
VOID Scene::EvtIsaacMindEyeStart()
{
    // 注入以撒辅助
    RemoteThreadInject32((LPWSTR)L"isaac-ng.exe", (LPWSTR)L"D:\\Workspace\\LaoQiongGui\\MindEye\\IsaacMindEye\\output\\x86\\Release\\IsaacMindEye.dll");
    // HijackProcessInject((LPWSTR)L"D:\\SteamLibrary\\steamapps\\common\\The Binding of Isaac Rebirth\\isaac-ng.exe", (LPWSTR)L"D:\\Workspace\\LaoQiongGui\\MindEye\\IsaacMindEye\\output\\x86\\Release\\IsaacMindEye.dll");
    return;
}

/**
 * 关闭以撒的结合.
 *
 * \param HANDLE：TerminateIsaacMindEye事件
 * \return 无返回值
 */
VOID Scene::EvtIsaacMindEyeEnd(DWORD dwProcessId)
{
    HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
    if (hProcess == NULL) {
        return;
    }
    ::TerminateProcess(hProcess, 0);
    ::CloseHandle(hProcess);
    return;
}
