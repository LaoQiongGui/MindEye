#include "MindEyeResourcesManager.h"

HRESULT MindEyeWaveManager::Load(LoadParams* pLoadParams)
{
    MindEyeWave mindEyeWave = { 0 };
    CHAR* fileName = (CHAR*)pLoadParams->pMindEyeWaveManager->WaveMap[pLoadParams->dwId].data();
    HANDLE hFile = ::CreateFileA(
        fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        //printf("绝对路径打不开\n");
        // 获取错误代码
        HRESULT hr = ::GetLastError();
        // 检测保留的jsonDir文件路径，分割出其路径，和fileName拼接在一起构造出绝对路径
        char* lastSlash = strrchr(pLoadParams->pMindEyeWaveManager->jsonDir, '/');
        if (lastSlash != nullptr) {
            *lastSlash = '\0';
            char* path = pLoadParams->pMindEyeWaveManager->jsonDir;
            char* name = strchr(fileName, '/');
            int length = strlen(name) + strlen(path);
            char* new_fileName = new char[length + 1];
            strcpy_s(new_fileName, length + 1, path);
            strcat_s(new_fileName, length + 1, name);
            fileName = new_fileName;
            //用CreateFile再次打开试试
            HANDLE hFile = ::CreateFileA(
                fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE) {
                fileName = fileName;
                //printf("相对路径打不开\n");
            }
            else {
                //printf("相对路径\n");
                ::CloseHandle(hFile);
            }
        }
        else {
            fileName = fileName;
            //printf("路径无/符号，无法生成相对路径\n");
        }
    }
    else
    {
        printf("绝对路径\n");
        ::CloseHandle(hFile);
    }
    //
    HRESULT hr = mindEyeWave.Load(fileName);
    ::EnterCriticalSection(&pLoadParams->pMindEyeWaveManager->cs);
    pLoadParams->pMindEyeWaveManager->LoadingMap.erase(pLoadParams->dwId);
    if (hr == S_OK)
    {
        pLoadParams->pMindEyeWaveManager->LoadedMap.emplace(pLoadParams->dwId, mindEyeWave);
    }
    ::LeaveCriticalSection(&pLoadParams->pMindEyeWaveManager->cs);
    delete pLoadParams;
    return hr;
}

HRESULT MindEyeWaveManager::Init(const char* configPath)
{
    ::InitializeCriticalSection(&cs);

    HANDLE hFile = ::CreateFileA(configPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return ::GetLastError();
    }
    std::vector<CHAR> jsonStr;
    DWORD dwFileSize = ::GetFileSize(hFile, NULL);
    jsonStr.resize(dwFileSize + 1, 0);
    DWORD dwReadedBytes = 0;
    BOOL bRet = ::ReadFile(hFile, jsonStr.data(), dwFileSize, &dwReadedBytes, NULL);
    ::CloseHandle(hFile);
    if (!bRet)
    {
        return ::GetLastError();
    }
    Json::Value jsonData;
    Json::Reader jsonReader;
    bRet = jsonReader.parse(jsonStr.data(), jsonData);
    if (!bRet)
    {
        return S_FALSE;
    }
    for (Json::String key : jsonData.getMemberNames())
    {
        DWORD dwResourceId = std::stoul(key.c_str());
        std::string resourcePath = jsonData[key].asString().c_str();
        WaveMap.emplace(dwResourceId, resourcePath);
    }
    int length = strlen(configPath);
    // 分配一个足够大的缓冲区来存储 constString 的内容
    char* buffer = new char[length + 1];
    // 将 constString 的内容复制到缓冲区中
    strcpy_s(buffer, length + 1, configPath);
    jsonDir = buffer;
    return S_OK;
}

HRESULT MindEyeWaveManager::Get(DWORD dwId, MindEyeWave** ppWaveFile)
{
    ::EnterCriticalSection(&cs);
    if (WaveMap.find(dwId) == WaveMap.end())
    {
        ::LeaveCriticalSection(&cs);
        return S_FALSE;
    }
    if (LoadedMap.find(dwId) != LoadedMap.end())
    {
        *ppWaveFile = &LoadedMap[dwId];
        ::LeaveCriticalSection(&cs);
        return S_OK;
    }
    if (LoadingMap.find(dwId) == LoadingMap.end())
    {
        LoadParams* pLoadParams = new LoadParams();
        pLoadParams->pMindEyeWaveManager = this;
        pLoadParams->dwId = dwId;
        HANDLE hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Load, (LPVOID)pLoadParams, NULL, NULL);
        if (hThread == NULL)
        {
            delete pLoadParams;
            ::LeaveCriticalSection(&cs);
            return ::GetLastError();
        }
        LoadingMap.emplace(dwId, hThread);
    }
    ::LeaveCriticalSection(&cs);
    return ERROR_IO_PENDING;
}

void MindEyeWaveManager::Destroy()
{
    WaveMap.clear();
    LoadingMap.clear();
    LoadedMap.clear();
    ::DeleteCriticalSection(&cs);
    return;
}
