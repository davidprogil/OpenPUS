/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
/* none */

/* component includes----------------------------------------------------------*/
#include <BLP_PrintersUser.h>

/* local macros ---------------------------------------------------------------*/
/* none */

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
/* none */

/* public functions -----------------------------------------------------------*/
void BLPPU_PrintCCSDS_PrimaryHeader(CCSDS_PrimaryHeader_t *dataStructure)
{
	CCSDS_PrintCccsdsPrimaryHeader(dataStructure);
}

void BLPPU_PrintPUS_TcSecondaryHeader(PUS_TcSecondaryHeader_t *dataStructure)
{
	PUS_PrintTcHeader(dataStructure);
}

void BLPPU_PrintPUS_TmSecondaryHeader(PUS_TmSecondaryHeader_t *dataStructure)
{
	PUS_PrintTmHeader(dataStructure);
}
void BLPPU_PrintPUS_AcceptanceReport(PUS_AcceptanceReport_t *dataStructure)
{
	PUS_PrintAcceptanceReport(dataStructure);
}
/* local functions ------------------------------------------------------------*/
/* none */

/* end */
