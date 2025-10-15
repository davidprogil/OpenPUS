/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPDU_DeserializersUser_H
#define BLPDU_DeserializersUser_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <SBCC_CcsdsUtils.h>
#include <LIB_PusUtils.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
typedef bool_t BLP_DeserializerFunction_t(void *structureData,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb);

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
BLP_DeserializerFunction_t BLPDU_DeserializeCCSDS_PrimaryHeader;
BLP_DeserializerFunction_t BLPDU_DeserializePUS_TcSecondaryHeader;
BLP_DeserializerFunction_t BLPDU_DeserializePUS_TmSecondaryHeader;
BLP_DeserializerFunction_t BLPDU_DeserializePUS_AcceptanceReport;

/* end */
#endif /* BLPDU_DeserializersUser_H */

