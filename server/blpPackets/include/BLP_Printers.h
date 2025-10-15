/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPP_Template_H
#define BLPP_Template_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
#include <BLP_Fillers.h>
#include <BLP_PrintersUser.h>

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
//type functions
void BLPP_PrintEnumMode(uint8_t *target,BLP_EnumMode_t mode);
//packet printers
void BLPP_Print(uint8_t *target,uint16_t targetNb);
void BLPP_PrintSetMode(BLP_SetMode_t *structureData);
void BLPP_PrintAllTypes(BLP_AllTypes_t *structureData);
void BLPP_PrintAllRanges(BLP_AllRanges_t *structureData);
void BLPP_PrintImageSegment(BLP_ImageSegment_t *structureData);
void BLPP_PrintFailReport(BLP_FailReport_t *structureData);

/* end */
#endif /* BLPP_Template_H */

