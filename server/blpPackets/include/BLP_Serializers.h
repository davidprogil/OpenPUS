/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPS_Serializers_H
#define BLPS_Serializers_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
#include <BLP_Fillers.h>
#include <BLP_SerializersUser.h>

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
bool_t BLPS_SerializeSetMode(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_SetMode_t *structuredData);
bool_t BLPS_SerializeAllTypes(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_AllTypes_t *structuredData);
bool_t BLPS_SerializeAllRanges(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_AllRanges_t *structuredData);
bool_t BLPS_SerializeImageSegment(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_ImageSegment_t *structuredData);
bool_t BLPS_SerializeFailReport(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_FailReport_t *structuredData);

/* end */
#endif /* BLPS_Serializers_H */

