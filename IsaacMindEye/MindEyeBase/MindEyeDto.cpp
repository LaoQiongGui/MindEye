#include "MindEyeDto.h"

// MindEyeEmitter
MindEyeEmitter::~MindEyeEmitter()
{
    if (pAudio2SourceVoice != NULL)
    {
        pAudio2SourceVoice->Stop();
        pAudio2SourceVoice->DestroyVoice();
    }
}