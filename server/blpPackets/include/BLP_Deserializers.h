/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPD_Template_H
#define BLPD_Template_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
#include <BLP_Fillers.h>
#include <BLP_DeserializersUser.h>

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
BLP_DeserializerFunction_t *BLPD_GetDeserializerFunction(uint16_t packetId);
//packet function
BLP_DeserializerFunction_t BLPD_DeserializeSetMode;
BLP_DeserializerFunction_t BLPD_DeserializeAllTypes;
BLP_DeserializerFunction_t BLPD_DeserializeAllRanges;
BLP_DeserializerFunction_t BLPD_DeserializeImageSegment;
BLP_DeserializerFunction_t BLPD_DeserializeFailReport;
/* end */
#endif /* BLPD_Template_H */

