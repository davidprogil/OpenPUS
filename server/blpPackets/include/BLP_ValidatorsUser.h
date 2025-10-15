/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPVU_Template_H
#define BLPVU_Template_H

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
typedef bool_t BLPV_ValidatorFunction_t(void *structuredData,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter);

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
BLPV_ValidatorFunction_t BLPVU_ValidateCCSDS_PrimaryHeader;
BLPV_ValidatorFunction_t BLPVU_ValidatePUS_TcSecondaryHeader;
BLPV_ValidatorFunction_t BLPVU_ValidatePUS_TmSecondaryHeader;

/* end */
#endif /* BLPVU_Template_H */

