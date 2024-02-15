/*
// Copyright 2016 Intel Corporation All Rights Reserved.
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
//              Color Conversion (ippCC_TL)
//
//
*/


#if !defined( IPPCC_TL_H__ )
#define IPPCC_TL_H__

#ifndef IPPDEFS_L_H__
  #include "ippdefs_l.h"
#endif

#include "ippcc_l.h"

#if defined( IPP_ENABLED_THREADING_LAYER_REDEFINITIONS )
    #include "ippcc_tl_redefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* /////////////////////////////////////////////////////////////////////////////
//  Name:   ippiRGBToLab_32f_P3R_LT
//          ippiRGBToLab_64f_P3R_LT
//          ippiLabToRGB_32f_P3R_LT
//          ippiLabToRGB_64f_P3R_LT
//          ippiRGBToLab_32f_P3R_T,
//          ippiRGBToLab_64f_P3R_T,
//          ippiLabToRGB_32f_P3R_T,
//          ippiLabToRGB_64f_P3R_T,
//  Purpose:    Converts an RGB image to CIE Lab color model and vice-versa
//  Parameters:
//    pSrc          Pointer to the source image ROI
//    srcStep       Step through the source  image (bytes)
//    pDst          Pointer to the destination image ROI
//    dstStep       Step through the destination image (bytes)
//    roiSize       Size of the ROI
//  Returns:
//     ippStsNullPtrErr  if src == NULL or dst == NULL or src[0,1,2] == NULL or dst[0,1,2] == NULL
//     ippStsSizeErr     if imgSize.width <= 0 || imgSize.height <= 0
//     ippStsNoErr       otherwise
*/
IPPAPI (IppStatus, ippiRGBToLab_32f_P3R_LT, (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiRGBToLab_64f_P3R_LT, (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiLabToRGB_32f_P3R_LT, (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiLabToRGB_64f_P3R_LT, (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiRGBToLab_32f_P3R_T,  (const Ipp32f* pSrc[3],      int srcStep[3], Ipp32f* pDst[3],      int dstStep[3], IppiSize  roiSize))
IPPAPI (IppStatus, ippiRGBToLab_64f_P3R_T,  (const Ipp64f* pSrc[3],      int srcStep[3], Ipp64f* pDst[3],      int dstStep[3], IppiSize  roiSize))
IPPAPI (IppStatus, ippiLabToRGB_32f_P3R_T,  (const Ipp32f* pSrc[3],      int srcStep[3], Ipp32f* pDst[3],      int dstStep[3], IppiSize  roiSize))
IPPAPI (IppStatus, ippiLabToRGB_64f_P3R_T,  (const Ipp64f* pSrc[3],      int srcStep[3], Ipp64f* pDst[3],      int dstStep[3], IppiSize  roiSize))

#ifdef __cplusplus
}
#endif

#endif /* IPPI_TL_H__ */
