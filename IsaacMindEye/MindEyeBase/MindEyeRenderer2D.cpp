#include "MindEyeRenderer2D.h"

MindEyeRenderer2D::MindEyeRenderer2D()
{
}

MindEyeRenderer2D::~MindEyeRenderer2D()
{
}

/**
 * 2D音效渲染函数.
 *
 * \param params：MindEyeRenderer2D参数
 * \param pData：音频数据
 * \param cFrames：声音帧数
 * \param cChannels：通道数
 */
void MindEyeRenderer2D::DoProcess(const MindEyeRenderer2DParams &params, FLOAT32 *pData, UINT32 cFrames, UINT32 cChannels)
{
    SpaceInfo spaceInfoEmitter = params.spaceInfoEmitter;
    SpaceInfo spaceInfoListener = params.spaceInfoListener;

    // 时域大小
    DWORD dwSize = cFrames;

    Ipp8u *pDFTInitBuf, *pDFTWorkBuf;
    int sizeDFTSpec, sizeDFTInitBuf, sizeDFTWorkBuf;

    // 计算缓冲区大小
    ippsDFTGetSize_C_32f(
        dwSize, IPP_FFT_NODIV_BY_ANY,
        ippAlgHintAccurate, &sizeDFTSpec, &sizeDFTInitBuf, &sizeDFTWorkBuf);
    IppsDFTSpec_C_32f *pDFTSpec = (IppsDFTSpec_C_32f *)ippsMalloc_8u(sizeDFTSpec);
    pDFTInitBuf = ippsMalloc_8u(sizeDFTInitBuf);
    pDFTWorkBuf = ippsMalloc_8u(sizeDFTWorkBuf);

    // FFT初始化
    ippsDFTInit_C_32f(
        cFrames, IPP_FFT_NODIV_BY_ANY,
        ippAlgHintAccurate, pDFTSpec, pDFTInitBuf);
    ippFree(pDFTInitBuf);

    // FFT缓冲区
    FLOAT *pTDRe = new FLOAT[dwSize]();
    FLOAT *pTDIm = new FLOAT[dwSize]();
    FLOAT *pFDRe = new FLOAT[dwSize]();
    FLOAT *pFDIm = new FLOAT[dwSize]();

    // 正向变换
    ippsDFTFwd_CToC_32f(pTDRe, pTDIm, pFDRe, pFDIm, pDFTSpec, pDFTWorkBuf);

    // TODO：音频处理

    // 逆向变换
    ippsDFTFwd_CToC_32f(pFDRe, pFDIm, pTDRe, pTDIm, pDFTSpec, pDFTWorkBuf);

    ippFree(pDFTSpec);
    ippFree(pDFTWorkBuf);
    ippFree(pTDRe);
    ippFree(pTDIm);
    ippFree(pFDRe);
    ippFree(pFDIm);
    return;
}
