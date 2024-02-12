#pragma once
#include <Windows.h>
#include <mmreg.h>
#include <vector>

#ifdef _XBOX // Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX // Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

// 查找与读取文件区块
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition);
HRESULT FindChunk(std::vector<BYTE> &bWaveData, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *buffer, DWORD buffersize, DWORD bufferoffset);

class MindEyeWave
{
private:
    /**
     * 载入wav文件.
     *
     * \param hFile：载入文件句柄
     * \return S_OK：载入成功
     */
    HRESULT load(HANDLE hFile);

    /**
     * 保存wav文件.
     *
     * \param hFile：保存文件句柄
     * \return S_OK：保存成功
     */
    HRESULT save(HANDLE hFile);

public:
    static const DWORD UNKNOWN = 0x00000000;
    static const DWORD UINT8 = 0x00000001;
    static const DWORD UINT16 = 0x00000002;
    static const DWORD UINT32 = 0x00000003;
    static const DWORD FLOAT32 = 0x00000004;
    static const DWORD FLOAT64 = 0x00000005;

    // RIFF区块
    DWORD dwChunkID;
    DWORD dwChunkSize;
    DWORD dwFormat;

    // fmt区块
    DWORD dwFmtChunkID;
    DWORD dwFmtChunkSize;
    WORD wAudioFormat;
    WORD wNumChannels;
    DWORD dwSampleRate;
    DWORD dwByteRate;
    WORD wBlockAlign;
    WORD wBitsPerSample;

    // data区块
    DWORD dwDataChunkID;
    DWORD dwDataChunkSize;
    std::vector<BYTE> bBufferData;

    /**
     * 载入wav文件.
     *
     * \param wFileName：载入文件名
     * \return S_OK：载入成功
     */
    HRESULT load(const wchar_t *wFileName);

    /**
     * 载入wav文件.
     *
     * \param fileName：载入文件名
     * \return S_OK：载入成功
     */
    HRESULT load(const char *fileName);

    /**
     * 保存wav文件.
     *
     * \param wFileName：保存文件名
     * \return S_OK：保存成功
     */
    HRESULT save(const wchar_t *wFileName);

    /**
     * 保存wav文件.
     *
     * \param fileName：保存文件名
     * \return S_OK：保存成功
     */
    HRESULT save(const char *fileName);

    /**
     * 获取wav文件编码格式.
     *
     * \return 成功：UINT8 UINT16 UINT32 FLOAT32 FLOAT64 失败：UNKNOWN
     */
    DWORD getEncodingFormat();

    /**
     * 转换wav文件的格式.
     *
     * \param dwFormat：支持UINT8 UINT16 UINT32 FLOAT32 FLOAT64
     * \return TRUE：转换成功 FALSE：未加载文件
     */
    BOOL transform(DWORD dwTargetFormat);

    /**
     * 获取音频格式.
     *
     * \param WFX：音频格式的引用
     * \return S_OK：获取成功
     */
    HRESULT getWaveFormat(WAVEFORMATEX &WFX);
};