#pragma once
#include <iostream>
#include <fstream>
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
	static HRESULT WINAPI Load(LoadParams *pLoadParams);

	CRITICAL_SECTION cs;
	std::map<DWORD, std::string> WaveMap;
	std::map<DWORD, HANDLE> LoadingMap;
	std::map<DWORD, MindEyeWave> LoadedMap;

public:
	HRESULT Init(WCHAR *wConfigPath);
	HRESULT Get(DWORD dwId, MindEyeWave **ppWaveFile);
	void Destroy();
};
