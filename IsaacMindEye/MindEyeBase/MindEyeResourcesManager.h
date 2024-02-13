#pragma once
#include "MindEyeCommon.h"
#include <map>
#include <string>
#include <json.h>

#include "MindEyeWave.h"

class MindEyeWaveManager
{
private:
	struct LoadParams
	{
		MindEyeWaveManager *pMindEyeWaveManager;
		DWORD dwId;
	};
	static HRESULT WINAPI load(LoadParams *pLoadParams);

	/** 关键段（用于线程同步） */
	CRITICAL_SECTION cs;

	/** 音频文件根目录 */
	char *rootDir;

	/** ID对应音频路径表 */
	std::map<DWORD, std::string> WaveMap;

	/** 加载中的音频列表 */
	std::map<DWORD, HANDLE> LoadingMap;

	/** 加载完的音频列表 */
	std::map<DWORD, MindEyeWave> LoadedMap;

public:
	/**
	 * 初始化资源管理器.
	 * 
	 * \param configPath：配置文件的路径
	 * \return S_OK：初始化成功
	 */
	HRESULT init(const char *configPath);

	/**
	 * 获取资源（异步）.
	 * 
	 * \param dwId：资源ID
	 * \param ppWaveFile：（输出）音频资源指针
	 * \return S_OK：获取资源成功 S_FALSE：资源不存在 ERROR_IO_PENDING：加载中
	 */
	HRESULT get(DWORD dwId, MindEyeWave **ppWaveFile);

	/**
	 * 销毁资源管理器.
	 * 
	 */
	void destroy();
};
