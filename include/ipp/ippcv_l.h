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

/*
//              Intel(R) Integrated Performance Primitives (Intel(R) IPP)
//              Computer Vision (ippCV_L)
//
//
*/


#if !defined( IppCV_L_H__ ) || defined( _OWN_BLDPCS )
#define IppCV_L_H__

#ifndef __IPPDEFS64X_H__
  #include "ippdefs_l.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussianGetBufferSize
//
//  Purpose:    Computes the size of the working buffer for the Gaussian filter
//
//  Return:
//     ippStsNoErr          Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr     One of the pointers is NULL.
//     ippStsSizeErr        maxRoiSize  has a field with zero or negative value.
//     ippStsDataTypeErr    Indicates an error when dataType has an illegal value.
//     ippStsBadArgErr      Indicates an error if kernelSize is even or is less than 3.
//     ippStsChannelErr     Indicates an error when numChannels has an illegal value.
//
//  Arguments:
//     maxRoiSize           Maximal size of the image ROI in pixels.
//     kernelSize           Size of the Gaussian kernel (odd, greater or equal to 3).
//     dataType             Data type of the source and destination images.
//     numChannels          Number of channels in the images. Possible values are 1 and 3.
//     pSpecSize            Pointer to the computed size (in bytes) of the Gaussian
//                            specification structure.
//     pBufferSize          Pointer to the computed size (in bytes) of the external buffer.
*/
IPPAPI(IppStatus, ippiFilterGaussianGetBufferSize_L,(IppiSizeL maxRoiSize, int kernelSize,
                  IppDataType dataType, IppiBorderType borderType, int numChannels, IppSizeL* pBufferSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussianGetSpecSize_L
//
//  Purpose:    Computes the size of the working buffer for the Gaussian filter GaussianSpec
//
//  Return:
//     ippStsNoErr          Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr     One of the pointers is NULL.
//     ippStsSizeErr        maxRoiSize  has a field with zero or negative value.
//     ippStsDataTypeErr    Indicates an error when dataType has an illegal value.
//     ippStsBadArgErr      Indicates an error if kernelSize is even or is less than 3.
//     ippStsChannelErr     Indicates an error when numChannels has an illegal value.
//
//  Arguments:
//     kernelSize           Size of the Gaussian kernel (odd, greater or equal to 3).
//     dataType             Data type of the source and destination images.
//     numChannels          Number of channels in the images. Possible values are 1 and 3.
//     pSpecSize            Pointer to the computed size (in bytes) of the Gaussian
//                            specification structure.
//     pInitBufferSize      Pointer to the computed size (in bytes) of the external buffer for the Gaussian filter GaussianSpec.
*/
IPPAPI(IppStatus, ippiFilterGaussianGetSpecSize_L,(int kernelSize, IppDataType dataType, int numChannels, IppSizeL *pSpecSize, IppSizeL* pInitBufferSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussianInit
//
//  Purpose:    initialization of Spec for Gaussian filter
//
//  Return:
//     ippStsNoErr          Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr     One of the pointers is NULL.
//     ippStsSizeErr        roiSize has a field with zero or negative value.
//     ippStsDataTypeErr    Indicates an error when borderType has an illegal value.
//     ippStsBadArgErr      kernelSize is even or is less than 3.
//     ippStsChannelErr     Indicates an error when numChannels has an illegal value.
//     ippStsBorderErr      Indicates an error condition if borderType has a illegal
//                           value.
//
//  Arguments:
//     roiSize              Size of the image ROI in pixels.
//     kernelSize           Size of the Gaussian kernel (odd, greater or equal to 3).
//     sigma                Standard deviation of the Gaussian kernel.
//     borderType           One of border supported types.
//     dataType             Data type of the source and destination images.
//     numChannels          Number of channels in the images. Possible values are 1 and 3.
//     pSpec                Pointer to the Spec.
//     pBuffer              Pointer to the buffer:
*/


IPPAPI(IppStatus, ippiFilterGaussianInit_L,(IppiSizeL roiSize, int kernelSize, Ipp32f sigma, IppiBorderType borderType, IppDataType dataType, int numChannels,
       IppFilterGaussianSpec* pSpec, Ipp8u* pInitBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussian
//
//  Purpose:    Applies Gaussian filter with borders
//
//  Return:
//     ippStsNoErr      Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr One of the specified pointers is NULL.
//     ippStsSizeErr    roiSize has a field with zero or negative value.
//     ippStsStepErr    Indicates an error condition if srcStep or dstStep is less
//                        than  roiSize.width * <pixelSize>.
//     ippStsNotEvenStepErr One of the step values is not divisible by 4 for floating-point images.
//     ippStsBadArgErr  kernelSize is less than 3 or sigma is less or equal than 0.
//
//  Arguments:
//     pSrc             Pointer to the source image ROI.
//     srcStep          Distance in bytes between starts of consecutive lines in the source image.
//     pDst             Pointer to the destination image ROI.
//     dstStep          Distance in bytes between starts of consecutive lines in the destination image.
//     roiSize          Size of the source and destination image ROI.
//     borderType       One of border supported types.
//     borderValue      Constant value to assign to pixels of the constant border. if border type equals ippBorderConstant
//     pSpec            Pointer to the Gaussian specification structure.
//     pBuffer          Pointer to the working buffer.
*/

IPPAPI(IppStatus, ippiFilterGaussian_32f_C1R_L,(const Ipp32f* pSrc, IppSizeL srcStep,
      Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16u_C1R_L,(const Ipp16u * pSrc, IppSizeL srcStep,
      Ipp16u * pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp16u borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16s_C1R_L,(const Ipp16s* pSrc, IppSizeL srcStep,
      Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp16s borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_8u_C1R_L,(const Ipp8u* pSrc, IppSizeL srcStep,
      Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp8u borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_32f_C3R_L,(const Ipp32f* pSrc, IppSizeL srcStep,
      Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp32f borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16u_C3R_L,(const Ipp16u * pSrc, IppSizeL srcStep,
      Ipp16u * pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp16u borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16s_C3R_L,(const Ipp16s* pSrc, IppSizeL srcStep,
      Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp16s borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_8u_C3R_L,(const Ipp8u* pSrc, IppSizeL srcStep,
      Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, IppiBorderType borderType,  const Ipp8u borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))


/****************************************************************************************\
*                                Morphological Operations                                *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiDilateGetBufferSize_L,   ippiErodeGetBufferSize_L
//
//
//  Purpose:  Gets the size of the internal state or specification structure for morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image, or width or height of the structuring
//                             element is less than,or equal to zero.
//
//  Parameters:
//    roiSize                  Size of the source and destination image ROI in pixels.
//    maskSize                 Size of the structuring element.
//    dataType                 The type of data
//    numChannels              The number of channels
//    pBufferSize              Pointer to the buffer size value for the morphological initialization function.
*/

IPPAPI(IppStatus, ippiDilateGetBufferSize_L, (IppiSizeL roiSize,  IppiSizeL maskSize, IppDataType datatype, int numChannels, IppSizeL* pBufferSize))

IPPAPI(IppStatus, ippiErodeGetBufferSize_L, (IppiSizeL roiSize,  IppiSizeL maskSize, IppDataType datatype, int numChannels, IppSizeL* pBufferSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiDilateGetSpecSize_L,     ippiErodeGetSpecSize_L
//
//
//  Purpose:  Gets the size of the internal state or specification structure for morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image, or width or height of the structuring
//                             element is less than,or equal to zero.
//
//  Parameters:
//    roiSize                  Size of the source and destination image ROI in pixels.
//    maskSize                 Size of the structuring element.
//    pSpecSize                Pointer to the specification structure size.
*/

IPPAPI(IppStatus, ippiDilateGetSpecSize_L,(IppiSizeL roiSize, IppiSizeL maskSize, IppSizeL* pSpecSize))
IPPAPI(IppStatus, ippiErodeGetSpecSize_L,(IppiSizeL roiSize, IppiSizeL maskSize, IppSizeL* pSpecSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiDilateInit_L,        ippiErodeInit_L
//
//  Purpose:  Initialize the internal state or specification structure for morphological operation.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image or width or height of the structuring
//                             element is less than, or equal to zero.
//    ippStsAnchorErr          Anchor point is outside the structuring element.
//
//  Parameters:
//    roiSize                  Size of the source and destination image ROI in pixels.
//    pMask                    Pointer to the structuring element (mask).
//    maskSize                 Size of the structuring element.
//    pMorphSpec               Pointer to the morphology specification structure.
*/


IPPAPI(IppStatus, ippiDilateInit_L,(IppiSizeL roiSize, const Ipp8u* pMask, IppiSizeL maskSize, IppiMorphStateL* pMorphSpec))
IPPAPI(IppStatus, ippiErodeInit_L,(IppiSizeL roiSize, const Ipp8u* pMask, IppiSizeL maskSize, IppiMorphStateL* pMorphSpec))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiDilate_8u_C1R,    ippiDilate_8u_C3R,
//          ippiDilate_8u_C4R,    ippiDilate_32f_C1R,
//          ippiDilate_32f_C3R,   ippiDilate_32f_C4R
//
//          ippiErode_8u_C1R,     ippiErode_8u_C3R,
//          ippiErode_8u_C4R,     ippiErode_32f_C1R,
//          ippiErode_32f_C3R,    ippiErode_32f_C4R,
//
//          ippiDilate_16u_C1R,            ippiDilate_16s_C1R,
//          ippiDilate_1u_C1R
//
//  Purpose:    Perform erosion/dilation of the image arbitrary shape structuring element.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            The ROI width or height is less than 1,
//                             or ROI width is bigger than ROI width in the state structure.
//    ippStsStepErr            Step is too small to fit the image.
//    ippStsNotEvenStepErr     Step is not multiple of the element.
//    ippStsBadArgErr          Incorrect border type.
//

//  Parameters:
//    pSrc                     Pointer to the source image.
//    srcStep                  Step in the source image.
//    pDst                     Pointer to the destination image.
//    dstStep                  Step in the destination image.
//    roiSize                  Size of the source and destination image ROI in pixels.
//    borderType               Type of border (ippBorderRepl now).
//    borderValue              Pointer to the vector of values for the constant border.
//    pMorphSpec               Pointer to the morphology specification structure.
//    pBuffer                  Pointer to the external work buffer.
*/

IPPAPI(IppStatus, ippiDilate_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep,
                                   Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep,
                                   Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep,
                                   Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep,
                                   Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep,
                                   Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep,
                                   Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_1u_C1R_L,( const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                                   IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer ))
IPPAPI(IppStatus, ippiDilate_16u_C1R_L,(const Ipp16u* pSrc, IppSizeL srcStep,
                                   Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilate_16s_C1R_L,(const Ipp16s* pSrc, IppSizeL srcStep,
                                   Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiErode_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep,
                                   Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType,const  Ipp8u borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep,
                                   Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep,
                                   Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep,
                                   Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep,
                                   Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep,
                                   Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_16u_C1R_L,(const Ipp16u* pSrc, IppSizeL srcStep,
                                   Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_16s_C1R_L,(const Ipp16s* pSrc, IppSizeL srcStep,
                                   Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
                                   IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErode_1u_C1R_L,( const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                                   IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphStateL* pMorphSpec, Ipp8u* pBuffer ))



/****************************************************************************************\
*                       Advanced Morphological Operations                                *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphGetSpecSize_L
//
//  Purpose:  Gets the size of the internal state or specification structure for advanced morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image, or width or height of the structuring.
//                             element is less than, or equal to zero.
//
//  Parameters:
//    roiSize                  Maximum size of the image ROI, in pixels.
//    maskSize                 Size of the structuring element.
//    dataType                 The type of data
//    numChannels              The number of channels
//    pSpecSize                Pointer to the specification structure size.
*/

IPPAPI(IppStatus, ippiMorphGetSpecSize_L,(IppiSizeL roiSize, IppiSizeL maskSize, IppDataType depth, int numChannels, IppSizeL* pSpecSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphGetBufferSize_L
//
//  Purpose:  Gets the size of the work buffer for the advanced morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image, or width or height of the structuring.
//                             element is less than, or equal to zero.
//
//  Parameters:
//    roiSize                  Maximum size of the image ROI, in pixels.
//    maskSize                 Size of the structuring element.
//    dataType                 The type of data
//    numChannels              The number of channels
//    pBufferSize              Pointer to the buffer size value for the morphology initialization function.
*/

IPPAPI(IppStatus, ippiMorphGetBufferSize_L,(IppiSizeL roiSize, IppiSizeL maskSize, IppDataType depth, int numChannels, IppSizeL* bufferSize))



/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphInit_L
//
//  Purpose:  Initialize the internal state or specification structure for advanced morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image or width or height of the structuring
//                             element is less than, or equal to zero.
//    ippStsAnchorErr          Anchor point is outside the structuring element.
//
//  Parameters:
//    roiSize                  Maximum size of the image ROI, in pixels.
//    pMask                    Pointer to the structuring element (mask).
//    maskSize                 Size of the structuring element.
//    dataType                 The type of data
//    numChannels              The number of channels
//    pMorphSpec               Pointer to the advanced morphology specification structure.
*/

IPPAPI( IppStatus, ippiMorphInit_L,( IppiSizeL roiSize, const Ipp8u* pMask, IppiSizeL maskSize, IppDataType depth, int numChannels,
                                              IppiMorphAdvStateL* pMorphSpec))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphClose_8u_C1R_L,             ippiMorphClose_8u_C3R_L,
//          ippiMorphClose_8u_C4R_L,             ippiMorphClose_32f_C1R_L,
//          ippiMorphClose_32f_C3R_L,            ippiMorphClose_32f_C4R_L
//
//          ippiMorphOpen_8u_C1R_L,              ippiMorphOpen_8u_C3R_L,
//          ippiMorphOpen_8u_C4R_L,              ippiMorphOpen_32f_C1R_L,
//          ippiMorphOpen_32f_C3R_L,             ippiMorphOpen_32f_C4R_L,
//
//          ippiMorphClose_16u_C1R_L,            ippiMorphOpen_16u_C1R_L,
//          ippiMorphClose_16s_C1R_L,            ippiMorphOpen_16s_C1R_L,
//          ippiMorphClose_1u_C1R_L,             ippiMorphOpen_1u_C1R_L,

//          ippiMorphTophat_8u_C1R_L,            ippiMorphTophat_8u_C3R_L,
//          ippiMorphTophat_8u_C4R_L,            ippiMorphTophat_32f_C1R_L,
//          ippiMorphTophat_32f_C3R_L,           ippiMorphTophat_32f_C4R_L,
//
//          ippiMorphBlackhat_8u_C1R_L,          ippiMorphBlackhat_8u_C3R_L,
//          ippiMorphBlackhat_8u_C4R_L,          ippiMorphBlackhat_32f_C1R_L,
//          ippiMorphBlackhat_32f_C3R_L,         ippiMorphBlackhat_32f_C4R_L,
//
//          ippiMorphGradient_8u_C1R_L,     ippiMorphGradient_8u_C3R_L,
//          ippiMorphGradient_8u_C4R_L,     ippiMorphGradient_32f_C1R_L,
//          ippiMorphGradient_32f_C3R_L,    ippiMorphGradient_32f_C4R_L,
//
//  Purpose:    Perform advanced morphological operations on the image arbitrary shape structuring element.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            The ROI width or height is less than 1,
//                             or ROI width is bigger than ROI width in the state structure.
//    ippStsStepErr            Step is too small to fit the image.
//    ippStsNotEvenStepErr     Step is not multiple of the element.
//    ippStsBadArgErr          Incorrect border type.
//
//  Parameters:
//    pSrc                     Pointer to the source image.
//    srcStep                  Step in the source image.
//    pDst                     Pointer to the destination image.
//    dstStep                  Step in the destination image.
//    roiSize                  ROI size.
//    borderType               Type of border (ippBorderRepl now).
//    borderValue              Value for the constant border.
//    pMorphSpec               Pointer to the morphology specification structure.
//    pBuffer                  Pointer to the external work buffer.
*/

IPPAPI( IppStatus, ippiMorphOpen_16u_C1R_L,(
                const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_16s_C1R_L,(
                const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_1u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_8u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_8u_C3R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_8u_C4R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiMorphClose_8u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_8u_C3R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_8u_C4R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiMorphClose_16u_C1R_L,(
                const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_16s_C1R_L,(
                const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_1u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_32f_C1R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer))
IPPAPI( IppStatus, ippiMorphOpen_32f_C3R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphOpen_32f_C4R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_32f_C1R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_32f_C3R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphClose_32f_C4R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiMorphTophat_16u_C1R_L,(
                const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_16s_C1R_L,(
                const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_1u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_8u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_8u_C3R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_8u_C4R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_32f_C1R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_32f_C3R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphTophat_32f_C4R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiMorphBlackhat_16u_C1R_L,(
                const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_16s_C1R_L,(
                const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_1u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_8u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_8u_C3R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_8u_C4R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_32f_C1R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_32f_C3R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphBlackhat_32f_C4R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiMorphGradient_16u_C1R_L,(
                const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_16s_C1R_L,(
                const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp16s borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_1u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, int srcBitOffset, Ipp8u* pDst, IppSizeL dstStep, int dstBitOffset,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_8u_C1R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_8u_C3R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_8u_C4R_L,(
                const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp8u borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_32f_C1R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[1], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_32f_C3R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiMorphGradient_32f_C4R_L,(
                const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                IppiSizeL roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvStateL* pMorthSpec, Ipp8u* pBuffer ))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphSetMode_L
//
//  Purpose:    Set mode for symmetrical operation in advanced morphology
//              IPP_MORPH_DEFAULT - default behavior
//              IPP_MORPH_MASK_NO_FLIP - don't flip mask(the same mask for (erode(dilate)->dilate(erode)) operations)
//
//
//  Return:
//    ippStsNoErr               Ok.
//    ippStsNullPtrErr          One of the pointers is NULL.
//    ippStsNotSupportedModeErr Incorrect mode
//
//  Parameters:
//    mode                     Mode. One of IPP_MORPH_DEFAULT(flip), IPP_MORPH_MASK_NO_FLIP(no flip)
//    pMorphSpec               Pointer to the morphology specification structure.
*/

IPPAPI(IppStatus, ippiMorphSetMode_L, (int mode, IppiMorphAdvStateL* pMorphSpec))

/*///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCannyGetSize_L
//
//  Purpose: Calculates size of temporary buffer, required to run Canny function.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer bufferSize is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//
//  Parameters:
//    roi                  Size of image ROI in pixel
//    bufferSize               Pointer to the variable that returns the size of the temporary buffer
//F*/

IPPAPI(IppStatus, ippiCannyGetSize_L, ( IppiSizeL roi, IppSizeL* bufferSize ))
/*///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCanny_16s8u_C1R_L
//
//  Purpose: Creates binary image of source's image edges,
//                using derivatives of the first order.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Bad thresholds
//
//  Parameters:
//    pDX                   Pointers to the source image ( first derivatives  with respect to X )
//    dxStep                Step in bytes through the source image pSrcDx
//    pDY                   Pointers to the source image ( first derivatives  with respect to Y )
//    dyStep                Step in bytes through the source image pSrcDy
//    pDst                  Pointers to the destination image
//    dstStep               Step in bytes through the destination image
//
//    roiL                  Size of the source images ROI in pixels
//    lowThreshold          Low threshold for edges detection
//    highThreshold         Upper threshold for edges detection
//    norm                  Norm type, {ippNormL1, ippNormL2}
//    pBuffer               Pointer to the pre-allocated temporary buffer, which size can be
//                          calculated using ippiCannyGetSize function
//F*/

IPPAPI(IppStatus, ippiCanny_16s8u_C1R_L, ( Ipp16s* pSrcDx, IppSizeL srcDxStep, Ipp16s* pSrcDy, IppSizeL srcDyStep, Ipp8u* pDstEdges, IppSizeL dstEdgeStep, IppiSizeL roiSize, Ipp32f lowThreshold, Ipp32f highThreshold, IppNormType norm, Ipp8u* pBuffer ))
IPPAPI(IppStatus, ippiCanny_32f8u_C1R_L, ( Ipp32f* pSrcDx, IppSizeL srcDxStep, Ipp32f* pSrcDy, IppSizeL srcDyStep, Ipp8u* pDstEdges, IppSizeL dstEdgeStep, IppiSizeL roiSize, Ipp32f lowThreshold, Ipp32f highThreshold, IppNormType norm, Ipp8u* pBuffer ))


/****************************************************************************************\
*                                   Separable Filters                                    *
\****************************************************************************************/


/*///////////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterSeparableGetBufferSize_L,
//             ippiFilterSeparableGetSpecSize_L
//             ippiFilterSeparable_8u_C1R_L,      ippiFilterSeparable_8u_C3R_L,      ippiFilterSeparable_8u_C4R_L
//             ippiFilterSeparable_8u16s_C1R_L,   ippiFilterSeparable_8u16s_C3R_L,   ippiFilterSeparable_8u16s_C4R_L
//             ippiFilterSeparable_16s_C1R_L,     ippiFilterSeparable_16s_C3R_L,     ippiFilterSeparable_16s_C4R_L
//             ippiFilterSeparable_16u_C1R_L,     ippiFilterSeparable_16u_C3R_L,     ippiFilterSeparable_16u_C4R_L
//             ippiFilterSeparable_32f_C1R_L,     ippiFilterSeparable_32f_C3R_L,     ippiFilterSeparable_32f_C4R_L
//  Purpose:   Convolves source image rows and columns with the row and column kernels
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Zero divisor
//
//  Parameters:
//    pSrc                     The pointer to the source image
//    pDst                     The pointer to the destination image
//    srcStep                  The step in the source image
//    dstStep                  The step in the destination image
//    roiSize                  The image ROI size
//    borderType               Type of the border
//    borderValue              Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec                    Pointer to the allocated and initialized context structure
//    pBuffer                  The pointer to the working buffer
//    kernelSize               Sizes of row and column kernels
//    dataType                 Data type of source image {ipp8u|ipp16s|ipp16u|ipp32f}
//    kernelType               Kernel type {ipp16s|ipp32f}
//    numChannels              Number of channels, possible values are 1, 3 or 4
//    pBufferSize              Pointer to the size (in bytes) of the external buffer
//    pSpecSize                Pointer to the size (in bytes) of the spec structure
//    pRowKernel               Pointer to row kernel
//    pColumnKernel            Pointer to column kernel
//    divisor                  The integer value by which the computed result is divided
//    scaleFactor              The integer value by which the computed result is scaled
*/

IPPAPI(IppStatus, ippiFilterSeparableGetBufferSize_L, (IppiSizeL roiSize, IppiSize kernelSize, IppDataType dataType, IppDataType kernelType, int numChannels, IppSizeL* pBufferSize))
IPPAPI(IppStatus, ippiFilterSeparableGetSpecSize_L, (IppiSize kernelSize, IppDataType dataType, int numChannels, int* pSpecSize))

IPPAPI(IppStatus, ippiFilterSeparableInit_16s_L, (const Ipp16s* pRowKernel, const Ipp16s* pColumnKernel, IppiSize kernelSize, int divisor, int scaleFactor, IppDataType dataType,
    int numChannels, IppiFilterSeparableSpec* pSpec))
IPPAPI(IppStatus, ippiFilterSeparableInit_32f_L, (const Ipp32f* pRowKernel, const Ipp32f* pColumnKernel, IppiSize kernelSize, IppDataType dataType,
    int numChannels, IppiFilterSeparableSpec* pSpec))

IPPAPI(IppStatus, ippiFilterSeparable_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp16s* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp16s* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp16u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp16u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp32f* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize,
    IppiBorderType borderType, Ipp32f* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

/****************************************************************************************\
*                                   Universal Pyramids                                   *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidGetSize_L
//
//  Purpose:    Computes the size of the structure for pyramids and the size
//              of the required work buffer (in bytes)
//
//  Arguments:
//    pPyrSize              Pointer to the size value of pyramid structure
//    pSizeBuf              Pointer to the size value of the pyramid external work buffer
//    level                 Maximal number pyramid level.
//    roiSize               Zero level image ROI size.
//    rate                  Neighbor levels ratio (1<rate<=10)
//
//  Return:
//    ippStsNoErr           Ok
//    ippStsNullPtrErr      One of pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value.
//    ippStsBadArgErr       level is equal to or less than 0 or if rate has wrong value.
*/

IPPAPI(IppStatus, ippiPyramidGetSize_L,(IppSizeL* pPyrSize, IppSizeL* pBufSize, int level, IppiSizeL roiSize, Ipp32f rate))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidInit_L
//
//  Purpose:    Initializes structure for pyramids, calculates ROI for layers.
//
//  Arguments:
//    pPyr                  Pointer to the pointer to the pyramid structure.
//    level                 Maximal number pyramid level.
//    roiSize               Zero level image ROI size.
//    rate                  Neighbor levels ratio (1<rate<=10).
//    pPyrBuffer            Pointer to the buffer to initialize structure for pyramids.
//    pBuffer               Pointer to the work buffer.
//
//  Return:
//    ippStsNoErr           Ok
//    ippStsNullPtrErr      One of pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value.
//    ippStsBadArgErr       level is equal to or less than 0 or if rate has wrong value.
*/

IPPAPI( IppStatus, ippiPyramidInit_L,( IppiPyramidL** pPyr, int level, IppiSizeL roiSize, Ipp32f rate, Ipp8u* pPyrBuffer, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidLayerDownGetSize_32f_C1R_L,
//              ippiPyramidLayerUpGetSize_32f_C1R_L
//
//  Purpose:    Calculates the size of structure for creating a lower(an upper) pyramid layer and the size
//              of the temporary  buffer (in bytes).
//
//  Arguments:
//    srcRoi                   Source image ROI size.
//    dstRoi                   Destination image ROI size.
//    rate                     Neighbor levels ratio (1<rate<=10)
//    kerSize                  Kernel size
//    pStateSize               Pointer to the size value of pyramid state structure.
//    pBufSize                 Pointer to the size value of the external work buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsBadArgErr          Bad rate or kernel size
//
*/

IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_32f_C1R_L,(IppiSizeL srcRoi, Ipp32f rate, int kerSize, IppSizeL* pStateSize, IppSizeL* pBufSize))
IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_32f_C1R_L,(IppiSizeL dstRoi, Ipp32f rate, int kerSize, IppSizeL* pStateSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidLayerDownInit_32f_C1R_L,
//              ippiPyramidLayerUpInit_32f_C1R_L
//
//  Purpose:    Initializes a structure for creating a lower(an upper) pyramid layer.
//
//  Arguments:
//    ppState                  Pointer to the pointer to initialized pyramid state structure
//    srcRoi                   Source image ROI size.
//    dstRoi                   Destination image ROI size.
//    rate                     Neighbor levels ratio (1<rate<=10)
//    pKernel                  Separable symmetric kernel of odd length
//    kerSize                  Kernel size
//    mode                     IPPI_INTER_LINEAR - bilinear interpolation
//    StateBuf                 Pointer to the buffer to initialize state structure for pyramids.
//    pBuffer                  Pointer to the work buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsBadArgErr          Bad mode, rate or kernel size
*/


IPPAPI(IppStatus, ippiPyramidLayerDownInit_32f_C1R_L,(IppiPyramidDownState_32f_C1R_L** pState, IppiSizeL srcRoi,
                         Ipp32f rate, const Ipp32f* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))
IPPAPI(IppStatus, ippiPyramidLayerUpInit_32f_C1R_L,(IppiPyramidUpState_32f_C1R_L** ppState, IppiSizeL dstRoi,
                         Ipp32f rate, const Ipp32f* pKernel, int kerSize, int mode, Ipp8u* StateBuf))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiGetPyramidDownROI_L, ippiGetPyramidUpROI_L
//
//  Purpose:    Calculate possible size of destination ROI.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            Wrong src roi
//    ippStsBadArgErr          Wrong rate
//
//  Arguments:
//    srcRoi                   Source image ROI size.
//    pDstRoi                  Pointer to destination image ROI size (down).
//    pDstRoiMin               Pointer to minimal destination image ROI size (up).
//    pDstRoiMax               Pointer to maximal destination image ROI size (up).
//    rate                     Neighbor levels ratio (1<rate<=10)
*/

IPPAPI(IppStatus, ippiGetPyramidDownROI_L,(IppiSizeL srcRoi, IppiSizeL *pDstRoi, Ipp32f rate))
IPPAPI(IppStatus, ippiGetPyramidUpROI_L,(IppiSizeL srcRoi, IppiSizeL *pDstRoiMin, IppiSizeL *pDstRoiMax, Ipp32f rate))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidLayerDown_32f_C1R_L
//              ippiPyramidLayerUp_32f_C1R_L
//
//  Purpose:    Perform downsampling/upsampling of the image with 5x5 Gaussian.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of the specified pointers is NULL
//    ippStsSizeErr            The srcRoiSize or dstRoiSize has a field with zero or negative value
//    ippStsStepErr            The steps in images are too small
//    ippStsBadArgErr          pState->rate has wrong value
//    ippStsNotEvenStepErr     One of the step values is not divisible by 4 for floating-point
//                             images, or by 2 for short-integer images.
//  Arguments:
//    pSrc                     Pointer to the source image
//    srcStep                  Step in byte through the source image
//    srcRoiSize               Size of the source image ROI in pixel.
//    dstRoiSize               Size of the destination image ROI in pixel.
//    pDst                     Pointer to destination image
//    dstStep                  Step in byte through the destination image
//    pState                   Pointer to the pyramid layer structure
*/

IPPAPI(IppStatus, ippiPyramidLayerDown_32f_C1R_L,(const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize,
                         Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiPyramidDownState_32f_C1R_L* pState))

IPPAPI(IppStatus, ippiPyramidLayerUp_32f_C1R_L,(const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize,
                         Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiPyramidUpState_32f_C1R_L* pState))


#ifdef __cplusplus
}
#endif

#endif /* IPPI_L_H__ */
