/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPV_Template_H
#define BLPV_Template_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
#include <BLP_ValidatorsUser.h>

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
bool_t BLPV_ValidatePacket(uint8_t *packetRaw,uint16_t totalLength, void *structuredData,uint16_t outputNb, uint16_t *packetId, uint16_t *failureId, uint8_t *failureInfo);
//packet function
BLPV_ValidatorFunction_t BLPVU_ValidateSetMode;
BLPV_ValidatorFunction_t BLPVU_ValidateAllTypes;
BLPV_ValidatorFunction_t BLPVU_ValidateAllRanges;
BLPV_ValidatorFunction_t BLPVU_ValidateImageSegment;
BLPV_ValidatorFunction_t BLPVU_ValidateFailureReport;
/* end */
#endif /* BLPV_Template_H */

