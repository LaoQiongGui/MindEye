/* 
// Copyright 2001 Intel Corporation All Rights Reserved.
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
//              Core (ippCore)
// 
// 
*/


#if !defined( IPPCORE_H__ ) || defined( _OWN_BLDPCS )
#define IPPCORE_H__

#ifndef IPPDEFS_H__
  #include "ippdefs.h"
#endif

#include "ippcore_l.h"

#ifdef __cplusplus
extern "C" {
#endif


#if !defined( IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_SEQUENTIAL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../../lib" IPP_LIB_SUBDIR_ARCH_SUFFIX "/ippcore" )
  #elif defined( _IPP_SEQUENTIAL_STATIC )
    #pragma comment( lib, __FILE__ "/../../../lib" IPP_LIB_SUBDIR_ARCH_SUFFIX "/ippcoremt" )
  #elif defined( _IPP_PARALLEL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../../lib" IPP_LIB_SUBDIR_ARCH_SUFFIX "/threaded/ippcore" )
  #elif defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, __FILE__ "/../../../lib" IPP_LIB_SUBDIR_ARCH_SUFFIX "/threaded/ippcoremt" )
  #endif
#endif

/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetLibVersion
//  Purpose:    getting of the library version
//  Returns:    the structure of information about version
//              of ippcore library
//  Parameters:
//
//  Notes:      not necessary to release the returned structure
*/
IPPAPI( const IppLibraryVersion*, ippGetLibVersion, (void) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetStatusString
//  Purpose:    convert the library status code to a readable string
//  Parameters:
//    StsCode   Intel(R) IPP status code
//  Returns:    pointer to string describing the library status code
//
//  Notes:      don't free the pointer
*/
IPPAPI( const char*, ippGetStatusString, ( IppStatus StsCode ) )



/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetCpuClocks
//  Purpose:    reading of time stamp counter (TSC) register value
//  Returns:    TSC value
//
//  Note:      An hardware exception is possible if TSC reading is not supported by
/              the current chipset
*/

IPPAPI( Ipp64u, ippGetCpuClocks, (void) )


/* ///////////////////////////////////////////////////////////////////////////
//  Names:  ippSetFlushToZero,
//          ippSetDenormAreZero.
//
//  Purpose: ippSetFlushToZero enables or disables the flush-to-zero mode,
//           ippSetDenormAreZero enables or disables the denormals-are-zero
//           mode.
//
//  Arguments:
//     value       - !0 or 0 - set or clear the corresponding bit of MXCSR
//     pUMask      - pointer to user store current underflow exception mask
//                   ( may be NULL if don't want to store )
//
//  Return:
//   ippStsNoErr              - Ok
//   ippStsCpuNotSupportedErr - the mode is not supported
*/

IPPAPI( IppStatus, ippSetFlushToZero, ( int value, unsigned int* pUMask ))
IPPAPI( IppStatus, ippSetDenormAreZeros, ( int value ))



/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippAlignPtr
//  Purpose:    pointer aligning
//  Returns:    aligned pointer
//
//  Parameter:
//    ptr        - pointer
//    alignBytes - number of bytes to align
//
*/
IPPAPI( void*, ippAlignPtr, ( void * ptr, int alignBytes ) )

/* /////////////////////////////////////////////////////////////////////////////
//                   Functions to allocate and free memory
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippMalloc
//  Purpose:    64-byte aligned memory allocation
//  Parameter:
//    len       number of bytes
//  Returns:    pointer to allocated memory
//
//  Notes:      the memory allocated by ippMalloc has to be free by ippFree
//              function only.
*/

IPPAPI( void*, ippMalloc,  (int length) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippFree
//  Purpose:    free memory allocated by the ippMalloc function
//  Parameter:
//    ptr       pointer to the memory allocated by the ippMalloc function
//
//  Notes:      use the function to free memory allocated by ippMalloc
*/
IPPAPI( void, ippFree, (void* ptr) )



/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippInit
//  Purpose:    Automatic switching to best for current CPU library code using.
//  Returns:
//   ippStsNoErr
//
//  Parameter:  nothing
//
//  Notes:      At the moment of this function execution no any other Intel(R) IPP function
//              has to be working
*/
IPPAPI( IppStatus, ippInit, ( void ))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetCpuFreqMhz
//
//  Purpose:    the function estimates CPU frequency and returns
//              its value in MHz as a integer
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         null pointer to the freq value
//    ippStsSizeErr            wrong number of tries, internal var
//  Arguments:
//    pMhz                     pointer to the integer to write
//                             CPU freq value estimated
//
//  Notes:      no exact value is guaranteed, the value could
//              vary with CPU workloading
*/

IPPAPI(IppStatus, ippGetCpuFreqMhz, ( int* pMhz ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippSetNumThreads
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNoOperation        For static library internal threading is not supported
//    ippStsSizeErr            Desired number of threads less or equal zero
//
//  Arguments:
//    numThr                   Desired number of threads
*/
IPPAPI( IppStatus, ippSetNumThreads, ( int numThr ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetNumThreads
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//    ippStsNoOperation        For static library internal threading is not supported
//                             and return value is always == 1
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr
*/
IPPAPI( IppStatus, ippGetNumThreads, (int* pNumThr) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetMaxCacheSizeB
//
//  Purpose:  Detects maximal from the sizes of L2 or L3 in bytes
//
//  Return:
//    ippStsNullPtrErr         The result's pointer is NULL.
//    ippStsNotSupportedCpu    The CPU is not supported.
//    ippStsUnknownCacheSize   The CPU is supported, but the size of the cache is unknown.
//    ippStsNoErr              Ok
//
//  Arguments:
//    pSizeByte                Pointer to the result
//
//  Note:
//    1). Intel(R) processors are supported only.
//    2). Intel(R) Itanium(R) processors and platforms with Intel XScale(R) technology are unsupported
//    3). For unsupported processors the result is "0",
//        and the return status is "ippStsNotSupportedCpu".
//    4). For supported processors the result is "0",
//        and the return status is "ippStsUnknownCacheSize".
//        if sizes of the cache is unknown.
//
*/
IPPAPI( IppStatus, ippGetMaxCacheSizeB, ( int* pSizeByte ) )

/*
//  Name:       ippGetCpuFeatures
//  Purpose:    Detects CPU features.
//  Parameters:
//    pFeaturesMask   Pointer to the features mask.
//                    Nonzero value of bit means the corresponding feature is supported.
//                    Features mask values are defined in the ippdefs.h
//                      [ 0] - MMX        ( ippCPUID_MMX   )
//                      [ 1] - SSE        ( ippCPUID_SSE   )
//                      [ 2] - SSE2       ( ippCPUID_SSE2  )
//                      [ 3] - SSE3       ( ippCPUID_SSE3  )
//                      [ 4] - SSSE3      ( ippCPUID_SSSE3 )
//                      [ 5] - MOVBE      ( ippCPUID_MOVBE )
//                      [ 6] - SSE41      ( ippCPUID_SSE41 )
//                      [ 7] - SSE42      ( ippCPUID_SSE42 )
//                      [ 8] - AVX        ( ippCPUID_AVX   )
//                      [ 9] - ENABLEDBYOS( ippAVX_ENABLEDBYOS )
//                      [10] - AES        ( ippCPUID_AES   )
//                      [11] - PCLMULQDQ  ( ippCPUID_CLMUL )
//                      [12] - ABR        ( ippCPUID_ABR )
//                      [13] - RDRAND     ( ippCPUID_RDRAND )
//                      [14] - F16C       ( ippCPUID_F16C )
//                      [15] - AVX2       ( ippCPUID_AVX2 )
//                      [16] - ADOX/ADCX  ( ippCPUID_ADCOX )      ADCX and ADOX instructions
//                      [17] - RDSEED     ( ippCPUID_RDSEED )     The RDSEED instruction
//                      [18] - PREFETCHW  ( ippCPUID_PREFETCHW )  The PREFETCHW instruction
//                      [19] - SHA        ( ippCPUID_SHA )        Intel(R) Secure Hash Algorithm Extensions (Intel(R) SHA Extensions)
//                      [20:63] - Reserved
//
//    pCpuidInfoRegs  Pointer to the 4-element vector.
//                    Result of CPUID.1 are stored in this vector.
//                      [0] - register EAX
//                      [1] - register EBX
//                      [2] - register ECX
//                      [3] - register EDX
//                    If pointer pCpuidInfoRegs is set to NULL, registers are not stored.
//
//  Returns:
//    ippStsNullPtrErr         The pointer to the features mask (pFeaturesMask) is NULL.
//    ippStsNotSupportedCpu    CPU is not supported.
//    ippStsNoErr              Ok
//
//  Note: Only IA-32 and Intel(R) 64 are supported
*/
IPPAPI( IppStatus, ippGetCpuFeatures, ( Ipp64u* pFeaturesMask,
                                        Ipp32u  pCpuidInfoRegs[4] ) )

/*
//  Name:       ippGetEnabledCpuFeatures
//  Purpose:    Detects enabled features for loaded libraries
//  Returns:    Features mask
//                    Features mask values are defined in the ippdefs.h
//                      [ 0] - ippCPUID_MMX
//                      [ 1] - ippCPUID_SSE
//                      [ 2] - ippCPUID_SSE2
//                      [ 3] - ippCPUID_SSE3
//                      [ 4] - ippCPUID_SSSE3
//                      [ 5] - ippCPUID_MOVBE
//                      [ 6] - ippCPUID_SSE41
//                      [ 7] - ippCPUID_SSE42
//                      [ 8] - ippCPUID_AVX
//                      [ 9] - ippAVX_ENABLEDBYOS
//                      [10] - ippCPUID_AES
//                      [11] - ippCPUID_CLMUL
//                      [12] - ippCPUID_ABR
//                      [13] - ippCPUID_RDRAND
//                      [14] - ippCPUID_F16C
//                      [15] - ippCPUID_AVX2
//                      [16] - ippCPUID_ADCOX
//                      [17] - ippCPUID_RDSEED
//                      [18] - ippCPUID_PREFETCHW
//                      [19] - ippCPUID_SHA
//                      [20:63] - Reserved
//
*/
IPPAPI( Ipp64u, ippGetEnabledCpuFeatures, ( void ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippSetCpuFeatures
//
//  Purpose: Changes the set of enabled/disabled CPU features.
//           This function sets the processor-specific code of the Intel(R) IPP
//           library according to the processor features specified in cpuFeatures.
//
//  Return:
//        ippStsNoErr                 No errors.
//    Warnings:
//        ippStsFeatureNotSupported   Current CPU doesn't support at least 1 of the desired features;
//                                    For example you've ordered P8_FM feature combination (see below),
//                                    but you CPU doesn't support Intel(R) AES New Instructions. Non-supported features will be disabled -
//                                    ippCPUID_AES in our example.
//        ippStsUnknownFeature        At least one of the desired features is unknown;
//                                    All supported features are declared in the ipptypes.h header file
//        ippStsFeaturesCombination   Wrong or incomplete combination of features;
//                                    This warning indicates situation like if you've ordered (for example) ippCPUID_AVX
//                                    and haven't ordered ippCPUID_SSE42 or ippCPUID_SSE2 features - there are no Intel(R) CPUs
//                                    that support only some new feature (for example Intel(R) Advanced Vector Extensions instruction set) 
//                                    and don't support some previous feature generation like Intel(R) Streaming SIMD Extensions 2.
//                                    This means that all "old" features will be enabled automatically.
//        ippStsCpuMismatch           Indicates that the specified processor features are not valid. Previously set code is used.
//                                    This situation means that (for example) you can't set ippCPUID_AVX feature on CPU 
//                                    that doesn't support Intel(R) Advanced Vector Extensions instruction set, or operating system
//                                    doesn't support ippAVX_ENABLEDBYOS feature.
//
//  Arguments:
//    cpuFeatures                 Desired features to support by the library
//                                (see ippdefs.h for ippCPUID_XX definition)
//
//  NOTE:       this function can re-initializes dispatcher and after the
//              call another library (letter) may work
//  CAUTION:    At the moment of this function execution no any other Intel(R) IPP
//              function has to be working
//
//  The next pre-defined sets of features can be used:
//  32-bit code:
// #define PX_FM ( ippCPUID_MMX | ippCPUID_SSE )
// #define W7_FM ( PX_FM | ippCPUID_SSE2 )
// #define V8_FM ( W7_FM | ippCPUID_SSE3 | ippCPUID_SSSE3 )
// #define S8_FM ( V8_FM | ippCPUID_MOVBE )
// #define P8_FM ( V8_FM | ippCPUID_SSE41 | ippCPUID_SSE42 )
// #define G9_FM ( P8_FM | ippCPUID_AVX | ippAVX_ENABLEDBYOS | ippCPUID_F16C )
// #define H9_FM ( G9_FM | ippCPUID_AVX2 | ippCPUID_MOVBE | ippCPUID_PREFETCHW )
//
// 64-bit code:
// #define PX_FM ( ippCPUID_MMX | ippCPUID_SSE | ippCPUID_SSE2 )
// #define M7_FM ( PX_FM | ippCPUID_SSE3 )
// #define U8_FM ( M7_FM | ippCPUID_SSSE3 )
// #define N8_FM ( U8_FM | ippCPUID_MOVBE )
// #define Y8_FM ( U8_FM | ippCPUID_SSE41 | ippCPUID_SSE42 )
// #define E9_FM ( Y8_FM | ippCPUID_AVX | ippAVX_ENABLEDBYOS | ippCPUID_F16C )
// #define L9_FM ( E9_FM | ippCPUID_MOVBE | ippCPUID_AVX2 | ippCPUID_PREFETCHW )
// #define N0_FM ( L9_FM | ippCPUID_AVX512F | ippCPUID_AVX512CD | ippCPUID_AVX512PF | ippCPUID_AVX512ER | ippAVX512_ENABLEDBYOS )
// #define K0_FM ( L9_FM | ippCPUID_AVX512F | ippCPUID_AVX512CD | ippCPUID_AVX512VL | ippCPUID_AVX512BW | ippCPUID_AVX512DQ | ippAVX512_ENABLEDBYOS )
//
*/
IPPAPI( IppStatus, ippSetCpuFeatures,( Ipp64u cpuFeatures ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetCacheParams
//  Purpose:    Retrieves cache parameters: cache type, level and size
//  Parameter:  pointer to array of structures describing CPU cache:
//              typedef struct {
//                 int type;
//                 int level;
//                 int size
//              } IppCache;
//              where type can be: 0 = Null - No more caches, 
//                                 1 = Data Cache, 
//                                 2 = Instruction Cache, 
//                                 3 = Unified Cache.
//              level means cache level starting from 1
//              cache size field is in bytes
//  Returns:
//    ippStsNullPtrErr         Input pointer is NULL
//    ippStsCpuNotSupportedErr CPU arch is too old to be supported by this function
//    ippStsNoErr              No error
//
//  Notes:      don't free pointer!
*/
IPPAPI( IppStatus, ippGetCacheParams,( IppCache** ppCacheInfo ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetL2CacheSize
//  Purpose:    Retrieves L2 cache size in bytes
//  Parameter:  pointer to int where to store L2 cache size
//              if returned size is 0 - than CPU is not supported by this function
//  Returns:
//    ippStsNullPtrErr         Input pointer is NULL
//    ippStsCpuNotSupportedErr CPU arch is too old to be supported by this function
//    ippStsNoErr              No error
*/
IPPAPI( IppStatus, ippGetL2CacheSize,( int* pSize ))


#ifdef __cplusplus
}
#endif

#endif /* IPPCORE_H__ */
