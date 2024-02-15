/*
// Copyright 2020 Intel Corporation All Rights Reserved.
//
//
// This software and the related documents are Intel copyrighted materials, and your use of them is governed by
// the express license under which they were provided to you ('License'). Unless the License provides otherwise,
// you may not use, modify, copy, publish, distribute, disclose or transmit this software or the related
// documents without Intel's prior written permission.
// This software and the related documents are provided as is, with no express or implied warranties, other than
// those that are expressly stated in the License.
//
*/

/*
//              Intel(R) Integrated Performance Primitives (Intel(R) IPP)
//              Computer Vision (ippCV_TL)
//
//
*/


#if !defined( IPPCV_TL_REDEFS_H__ )
#define IPPCV_TL_REDEFS_H__


#define ippiFilterSeparableGetBufferSize ippiFilterSeparableGetBufferSize_T
#define ippiFilterSeparableGetSpecSize ippiFilterSeparableGetSpecSize_T
#define ippiFilterSeparableGetBufferSize_L ippiFilterSeparableGetBufferSize_LT
#define ippiFilterSeparableGetSpecSize_L ippiFilterSeparableGetSpecSize_LT

#define ippiFilterSeparableInit_16s ippiFilterSeparableInit_16s_T_Proxy
#define ippiFilterSeparableInit_32f ippiFilterSeparableInit_32f_T_Proxy
#define ippiFilterSeparableInit_16s_L ippiFilterSeparableInit_16s_LT_Proxy
#define ippiFilterSeparableInit_32f_L ippiFilterSeparableInit_32f_LT_Proxy

#define ippiFilterSeparable_8u_C1R ippiFilterSeparable_8u_C1R_T_Proxy
#define ippiFilterSeparable_8u_C3R ippiFilterSeparable_8u_C3R_T_Proxy
#define ippiFilterSeparable_8u_C4R ippiFilterSeparable_8u_C4R_T_Proxy
#define ippiFilterSeparable_16s_C1R ippiFilterSeparable_16s_C1R_T_Proxy
#define ippiFilterSeparable_16s_C3R ippiFilterSeparable_16s_C3R_T_Proxy
#define ippiFilterSeparable_16s_C4R ippiFilterSeparable_16s_C4R_T_Proxy
#define ippiFilterSeparable_16u_C1R ippiFilterSeparable_16u_C1R_T_Proxy
#define ippiFilterSeparable_16u_C3R ippiFilterSeparable_16u_C3R_T_Proxy
#define ippiFilterSeparable_16u_C4R ippiFilterSeparable_16u_C4R_T_Proxy
#define ippiFilterSeparable_32f_C1R ippiFilterSeparable_32f_C1R_T_Proxy
#define ippiFilterSeparable_32f_C3R ippiFilterSeparable_32f_C3R_T_Proxy
#define ippiFilterSeparable_32f_C4R ippiFilterSeparable_32f_C4R_T_Proxy
#define ippiFilterSeparable_8u16s_C1R ippiFilterSeparable_8u16s_C1R_T_Proxy
#define ippiFilterSeparable_8u16s_C3R ippiFilterSeparable_8u16s_C3R_T_Proxy
#define ippiFilterSeparable_8u16s_C4R ippiFilterSeparable_8u16s_C4R_T_Proxy
#define ippiFilterSeparable_8u_C1R_L ippiFilterSeparable_8u_C1R_LT_Proxy
#define ippiFilterSeparable_8u_C3R_L ippiFilterSeparable_8u_C3R_LT_Proxy
#define ippiFilterSeparable_8u_C4R_L ippiFilterSeparable_8u_C4R_LT_Proxy
#define ippiFilterSeparable_16u_C1R_L ippiFilterSeparable_16u_C1R_LT_Proxy
#define ippiFilterSeparable_16u_C3R_L ippiFilterSeparable_16u_C3R_LT_Proxy
#define ippiFilterSeparable_16u_C4R_L ippiFilterSeparable_16u_C4R_LT_Proxy
#define ippiFilterSeparable_16s_C1R_L ippiFilterSeparable_16s_C1R_LT_Proxy
#define ippiFilterSeparable_16s_C3R_L ippiFilterSeparable_16s_C3R_LT_Proxy
#define ippiFilterSeparable_16s_C4R_L ippiFilterSeparable_16s_C4R_LT_Proxy
#define ippiFilterSeparable_32f_C1R_L ippiFilterSeparable_32f_C1R_LT_Proxy
#define ippiFilterSeparable_32f_C3R_L ippiFilterSeparable_32f_C3R_LT_Proxy
#define ippiFilterSeparable_32f_C4R_L ippiFilterSeparable_32f_C4R_LT_Proxy
#define ippiFilterSeparable_8u16s_C1R_L ippiFilterSeparable_8u16s_C1R_LT_Proxy
#define ippiFilterSeparable_8u16s_C3R_L ippiFilterSeparable_8u16s_C3R_LT_Proxy
#define ippiFilterSeparable_8u16s_C4R_L ippiFilterSeparable_8u16s_C4R_LT_Proxy


#ifdef __cplusplus
extern "C" {
#endif

IPPAPI(IppStatus, ippiFilterSeparableInit_16s_T_Proxy, (const Ipp16s* pRowKernel, const Ipp16s* pColumnKernel, IppiSize kernelSize, int divisor, int scaleFactor, IppDataType dataType, int numChannels, IppiFilterSeparableSpec* pSpec))
IPPAPI(IppStatus, ippiFilterSeparableInit_32f_T_Proxy, (const Ipp32f* pRowKernel, const Ipp32f* pColumnKernel, IppiSize kernelSize, IppDataType dataType, int numChannels, IppiFilterSeparableSpec* pSpec))
IPPAPI(IppStatus, ippiFilterSeparableInit_16s_LT_Proxy, (const Ipp16s* pRowKernel, const Ipp16s* pColumnKernel, IppiSize kernelSize, int divisor, int scaleFactor, IppDataType dataType, int numChannels, IppiFilterSeparableSpec* pSpec))
IPPAPI(IppStatus, ippiFilterSeparableInit_32f_LT_Proxy, (const Ipp32f* pRowKernel, const Ipp32f* pColumnKernel, IppiSize kernelSize, IppDataType dataType, int numChannels, IppiFilterSeparableSpec* pSpec))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C1R_T_Proxy, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C3R_T_Proxy, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C4R_T_Proxy, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C1R_T_Proxy, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C3R_T_Proxy, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C4R_T_Proxy, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C1R_T_Proxy, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C3R_T_Proxy, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C4R_T_Proxy, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C1R_T_Proxy, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C3R_T_Proxy, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C4R_T_Proxy, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C1R_T_Proxy, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C3R_T_Proxy, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C4R_T_Proxy, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C1R_LT_Proxy, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C3R_LT_Proxy, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C4R_LT_Proxy, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C1R_LT_Proxy, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C3R_LT_Proxy, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C4R_LT_Proxy, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C1R_LT_Proxy, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C3R_LT_Proxy, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C4R_LT_Proxy, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C1R_LT_Proxy, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C3R_LT_Proxy, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C4R_LT_Proxy, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C1R_LT_Proxy, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C3R_LT_Proxy, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C4R_LT_Proxy, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

#ifdef __cplusplus
}
#endif

#endif /* IPPCV_TL_REDEFS_H__ */
