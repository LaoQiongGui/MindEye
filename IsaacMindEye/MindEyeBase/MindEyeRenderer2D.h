#pragma once
#include "MindEyeCommon.h"
#include <ipp.h>

#include "MindEyeDto.h"
#include "MindEyeRendererBase.h"

struct MindEyeRenderer2DParams
{
	// 空间信息
	SpaceInfo spaceInfoEmitter;
	SpaceInfo spaceInfoListener;
};

class __declspec(uuid("{6F060410-E04A-CD59-2D00-F104E8CF13D3}"))
	MindEyeRenderer2D : public MindEyeRendererBase<MindEyeRenderer2D, MindEyeRenderer2DParams>
{
public:
	MindEyeRenderer2D();
	~MindEyeRenderer2D();

	void DoProcess(const MindEyeRenderer2DParams &params, FLOAT32 *pData, UINT32 cFrames, UINT32 cChannels) override;
};
