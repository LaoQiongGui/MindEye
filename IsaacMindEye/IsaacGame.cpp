#include "pch.h"
#include "IsaacGame.h"

IsaacGame *IsaacGame::pIsaacGame = NULL;
DWORD IsaacGame::dwCount = 0;

IsaacGame::IsaacGame()
{
    // 获取isaac-ng.exe模块基址
    MODULEENTRY32 me32 = {0};
    me32.dwSize = sizeof(MODULEENTRY32);
    GetModuleInfoByName(NULL, L"isaac-ng.exe", &me32);
    dwModuleBaseAdd = (DWORD)me32.modBaseAddr;

    // 游戏实例：isaac-ng.exe + GAMEOFFSET(7FD65C)
    pGame = (DWORD *)(dwModuleBaseAdd + GAMEOFFSET);

    pLevel = NULL;
    dwStatus = 0;
}

IsaacGame::~IsaacGame()
{
}

/**
 * 加载游戏地图.
 *
 */
void IsaacGame::loadMap()
{
    // 地图对象：[isaac-ng.exe+7FD65C]+0001796C
    DWORD dwMapBaseAdd = NULL;
    dwMapBaseAdd = *pGame + 0x0001796C;
    ::memcpy_s(map, MAPWIDTH * MAPHEIGHT * sizeof(DWORD), (DWORD *)dwMapBaseAdd, MAPWIDTH * MAPHEIGHT * sizeof(DWORD));
    for (DWORD i = 0; i < MAPHEIGHT; i++)
    {
        for (DWORD j = 0; j < MAPWIDTH; j++)
        {
            if (map[i][j] != 0xFFFFFFFF)
            {
                // 房间对象：[dwMapBaseAdd([pGame(isaac-ng.exe+7FD65C)]+0001796C)+offset*4] * B8 + [pGame(isaac-ng.exe+7FD65C)] + 14
                pRooms[i][j] = (DWORD *)(*((DWORD *)dwMapBaseAdd + i * MAPWIDTH + j) * 0xB8 + *pGame + 0x14);
            }
        }
    }
    showMap();
    return;
}

/**
 * 开始访问游戏对象.
 *
 * \return 游戏对象指针
 */
IsaacGame *IsaacGame::begin()
{
    if (pIsaacGame == NULL)
    {
        pIsaacGame = new IsaacGame();
    }
    dwCount++;
    return pIsaacGame;
}

/**
 * 结束访问游戏对象.
 *
 */
void IsaacGame::end()
{
    dwCount--;
    if (dwCount == 0)
    {
        IsaacGame *pIsaacGameTmp = pIsaacGame;
        pIsaacGame = NULL;
        delete pIsaacGameTmp;
    }
    return;
}

/**
 * 获取最新的游戏状态.
 *
 */
void IsaacGame::refresh()
{
    if (pGame == NULL)
    {
        return;
    }

    // 关卡实例：[isaac-ng.exe+GAMEOFFSET(7FD65C)]+LEVELOFFSET(00018190)
    pLevel = (DWORD *)(*pGame + LEVELOFFSET);

    if (pLevel == NULL)
    {
        return;
    }

    // 获取地图数据
    loadMap();
}

void IsaacGame::showMap()
{
    printf_s("游戏地图\n");
    printf_s(" - - - - - - - - - - - - -\n");
    for (DWORD i = 0; i < MAPHEIGHT; i++)
    {
        CHAR buffer1[MAX_PATH] = {0};
        CHAR buffer2[MAX_PATH] = {0};
        memset(buffer1, ' ', MAX_PATH);
        memset(buffer2, ' ', MAX_PATH);
        DWORD dwBufOffset = 0;
        buffer1[dwBufOffset] = '|';
        dwBufOffset += 1;
        for (DWORD j = 0; j < MAPWIDTH; j++)
        {
            if (map[i][j] != 0xFFFFFFFF)
            {
                buffer1[dwBufOffset] = 'A';
            }
            if (j == MAPWIDTH - 1 || map[i][j] != map[i][j + 1])
            {
                buffer1[dwBufOffset + 1] = '|';
            }
            if (i == MAPHEIGHT - 1 || map[i][j] != map[i + 1][j])
            {
                buffer2[dwBufOffset] = '-';
            }
            dwBufOffset += 2;
        }
        buffer1[dwBufOffset] = '\n';
        buffer1[dwBufOffset + 1] = '\0';
        buffer2[dwBufOffset] = '\n';
        buffer2[dwBufOffset + 1] = '\0';
        printf_s(buffer1);
        printf_s(buffer2);
    }
}
