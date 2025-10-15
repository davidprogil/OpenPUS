/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPPU_PrintersUser_H
#define BLPPU_PrintersUser_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <SBCC_CcsdsUtils.h>
#include <LIB_PusUtils.h>

/* component includes----------------------------------------------------------*/
#include <BLP_PrintersUser.h>

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void BLPPU_PrintCCSDS_PrimaryHeader(CCSDS_PrimaryHeader_t *dataStructure);
void BLPPU_PrintPUS_TcSecondaryHeader(PUS_TcSecondaryHeader_t *dataStructure);
void BLPPU_PrintPUS_TmSecondaryHeader(PUS_TmSecondaryHeader_t *dataStructure);
void BLPPU_PrintPUS_AcceptanceReport(PUS_AcceptanceReport_t *dataStructure);

/* end */
#endif /* BLPPU_PrintersUser_H */

