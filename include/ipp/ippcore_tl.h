/*
// Copyright 2015 Intel Corporation All Rights Reserved.
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

#ifndef IPPCORE_TL_H__ 
#define IPPCORE_TL_H__ 

#ifndef IPPDEFS_L_H__
    #include "ippdefs_l.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OMP,
    TBB
} IppThreadingType;

typedef IppStatus(*functype_l)(IppSizeL i, void* arg);
typedef IppStatus(*functype)(int i, void* arg);

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetThreadingType (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to thrType is Null
//
//  Arguments:
//    thrType                  Pointer to memory location where to store current threading type 
*/

IPPAPI(IppStatus, ippGetThreadingType_LT, (IppThreadingType* thrType))
IPPAPI(IppStatus, ippGetThreadingType_T,  (IppThreadingType* thrType))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetNumThreads (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr 
*/

IPPAPI(IppStatus, ippGetNumThreads_LT, (int* pNumThr))
IPPAPI(IppStatus, ippGetNumThreads_T,  (int* pNumThr))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippSetNumThreads (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose: set the maximum number of threads that are used in OpenMP Threading Layer functions
//
//  Return:
//    ippStsNoErr                  Ok
//    ippStsSizeErr                The number is less than or equal to zero
//    ippStsOperationNotSupported  Indicates a warning that function not implemented for TBB Threading Layer*
//
//  Arguments:
//    numThr                   Variable where to store current numThr
*/

IPPAPI(IppStatus, ippSetNumThreads_LT, (int numThr))
IPPAPI(IppStatus, ippSetNumThreads_T, (int numThr))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetThreadIdx (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr 
*/

IPPAPI(IppStatus, ippGetThreadIdx_LT, (int* pThrIdx))
IPPAPI(IppStatus, ippGetThreadIdx_T,  (int* pThrIdx))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippParallelFor (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to arg or func is Null
//    any other output depending on func output
//
//  Arguments:
//    numTiles                  number of tiles
//    func                      pointer to function to use in cycle
//    arg                       pointer to the structure containing arguments for function above 
*/

IPPAPI(IppStatus, ippParallelFor_LT, (IppSizeL numTiles, void* arg, functype_l func))
IPPAPI(IppStatus, ippParallelFor_T,  (int numTiles, void* arg, functype func))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IPPCORE_TL_H__  */
