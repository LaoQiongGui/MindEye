#include "MindEyeWave.h"

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType = 0;
    DWORD dwChunkDataSize = 0;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType = 0;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
            {
                hr = HRESULT_FROM_WIN32(GetLastError());
            }
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize)
        {
            return S_FALSE;
        }
    }

    return S_OK;
}

HRESULT FindChunk(std::vector<BYTE> &bWaveData, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition)
{
    DWORD dwChunkType = 0;
    for (dwChunkDataPosition = 0; dwChunkDataPosition < bWaveData.size() - 2 * sizeof(DWORD);)
    {
        ::memcpy_s(&dwChunkType, sizeof(DWORD), &bWaveData[dwChunkDataPosition], sizeof(DWORD));
        dwChunkDataPosition += sizeof(DWORD);
        ::memcpy_s(&dwChunkSize, sizeof(DWORD), &bWaveData[dwChunkDataPosition], sizeof(DWORD));
        dwChunkDataPosition += sizeof(DWORD);
        if (fourcc == dwChunkType)
        {
            return S_OK;
        }
        if (dwChunkType == fourccRIFF)
        {
            dwChunkDataPosition += sizeof(DWORD);
        }
        else
        {
            dwChunkDataPosition += dwChunkSize;
        }
    }
    return S_FALSE;
}

HRESULT ReadChunkData(HANDLE hFile, void *buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }
    return hr;
}

HRESULT MindEyeWave::load(HANDLE hFile)
{
    HRESULT hr = S_OK;
    BOOL bRet = TRUE;
    // 加载音频至内存
    DWORD dwFileSize = ::GetFileSize(hFile, NULL);
    std::vector<BYTE> waveDataList;
    waveDataList.resize(dwFileSize, 0);

    DWORD dwReadedBytes = 0;
    bRet = ::ReadFile(hFile, waveDataList.data(), dwFileSize, &dwReadedBytes, NULL);
    if (!bRet)
    {
        hr = ::GetLastError();
        return hr;
    }

    DWORD dwChunkSize = 0;
    DWORD dwChunkDataPosition = 0;
    // 读取RIFF区块
    hr = FindChunk(waveDataList, fourccRIFF, dwChunkSize, dwChunkDataPosition);
    if (hr != S_OK)
    {
        return hr;
    }
    dwChunkID = fourccRIFF;
    dwChunkSize = dwChunkSize;
    ::memcpy_s(&dwFormat, sizeof(DWORD), &waveDataList[dwChunkDataPosition], sizeof(DWORD));

    // 读取fmt区块
    hr = FindChunk(waveDataList, fourccFMT, dwChunkSize, dwChunkDataPosition);
    if (hr != S_OK)
    {
        return hr;
    }
    dwFmtChunkID = fourccFMT;
    dwFmtChunkSize = dwChunkSize;
    ::memcpy_s(&wAudioFormat, 2 * sizeof(DWORD) + 4 * sizeof(WORD), &waveDataList[dwChunkDataPosition], 2 * sizeof(DWORD) + 4 * sizeof(WORD));

    // 读取data区块
    hr = FindChunk(waveDataList, fourccDATA, dwChunkSize, dwChunkDataPosition);
    if (hr != S_OK)
    {
        return hr;
    }
    dwDataChunkID = fourccDATA;
    dwDataChunkSize = dwChunkSize;
    bBufferData.resize(dwDataChunkSize, 0);
    ::memcpy_s(bBufferData.data(), dwDataChunkSize, &waveDataList[dwChunkDataPosition], dwDataChunkSize);
    return hr;
}

HRESULT MindEyeWave::save(HANDLE hFile)
{
    DWORD dwWrittenBytes = 0;
    if (!::WriteFile(hFile, this, (DWORD)&bBufferData - (DWORD)&dwChunkID, &dwWrittenBytes, NULL))
    {
        return ::GetLastError();
    }
    if (!::WriteFile(hFile, bBufferData.data(), dwDataChunkSize, &dwWrittenBytes, NULL))
    {
        return ::GetLastError();
    }
    return S_OK;
}

HRESULT MindEyeWave::load(const wchar_t *wFileName)
{
    HRESULT hr = S_OK;
    // 打开文件
    HANDLE hFile = ::CreateFileW(
        wFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        hr = ::GetLastError();
        return hr;
    }

    hr = load(hFile);
    ::CloseHandle(hFile);
    return hr;
}

HRESULT MindEyeWave::load(const char *fileName)
{
    HRESULT hr = S_OK;
    // 打开文件
    HANDLE hFile = ::CreateFileA(
        fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        hr = ::GetLastError();
        return hr;
    }

    hr = load(hFile);
    ::CloseHandle(hFile);
    return hr;
}

HRESULT MindEyeWave::save(const wchar_t *wFileName)
{
    HRESULT hr = S_OK;
    // 打开文件
    HANDLE hFile = ::CreateFileW(
        wFileName, GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        hr = ::GetLastError();
        return hr;
    }
    hr = save(hFile);
    ::CloseHandle(hFile);
    return hr;
}

HRESULT MindEyeWave::save(const char *fileName)
{
    HRESULT hr = S_OK;
    // 打开文件
    HANDLE hFile = ::CreateFileA(
        fileName, GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        hr = ::GetLastError();
        return hr;
    }
    hr = save(hFile);
    ::CloseHandle(hFile);
    return hr;
}

DWORD MindEyeWave::getEncodingFormat()
{
    switch (wAudioFormat)
    {
    case WAVE_FORMAT_PCM:
        switch (wBitsPerSample)
        {
        case 8:
            return ENCODING_FOEMAT_UINT8;
        case 16:
            return ENCODING_FOEMAT_UINT16;
        case 32:
            return ENCODING_FOEMAT_UINT32;
        default:
            break;
        }
        break;
    case WAVE_FORMAT_IEEE_FLOAT:
        switch (wBitsPerSample)
        {
        case 32:
            return ENCODING_FOEMAT_FLOAT;
        case 64:
            return ENCODING_FOEMAT_DOUBLE;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return ENCODING_FOEMAT_UNKNOWN;
}

HRESULT MindEyeWave::getWaveFormat(WAVEFORMATEX &WFX)
{
    // 未初始化
    if (dwChunkID != fourccRIFF)
    {
        return S_FALSE;
    }
    WFX.wFormatTag = wAudioFormat;
    WFX.nChannels = wNumChannels;
    WFX.nSamplesPerSec = dwSampleRate;
    WFX.nAvgBytesPerSec = dwByteRate;
    WFX.nBlockAlign = wBlockAlign;
    WFX.wBitsPerSample = wBitsPerSample;
    WFX.cbSize = sizeof(WAVEFORMATEX);
    return S_OK;
}
