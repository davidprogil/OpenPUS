/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPSU_SerializersUser_H
#define BLPSU_SerializersUser_H

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
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
bool_t BLPSU_SerializeCCSDS_PrimaryHeader(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,CCSDS_PrimaryHeader_t *structuredData);
bool_t BLPSU_SerializePUS_TcSecondaryHeader(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,PUS_TcSecondaryHeader_t *structuredData);
bool_t BLPSU_SerializePUS_TmSecondaryHeader(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,PUS_TmSecondaryHeader_t *structuredData);
bool_t BLPSU_SerializePUS_AcceptanceReport(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,PUS_AcceptanceReport_t *structuredData);

/* end */
#endif /* BLPSU_SerializersUser_H */

