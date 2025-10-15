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
#include <BLP_ValidatorsUser.h>
#include <BLP_Fillers.h>

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
bool_t BLPVU_ValidateCCSDS_PrimaryHeader(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;

	//no range validation in this datatype
	*failureId = BLP_FID_OK;
	CCSDS_PrimaryHeader_t *structuredData=(CCSDS_PrimaryHeader_t *)input;

	if (isValid==M_TRUE)
	{
		if (structuredData->versionNumber!=CCSDS_VERSION_NUMBER)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}

	return isValid;
}
bool_t BLPVU_ValidatePUS_TcSecondaryHeader(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;

	*failureId = BLP_FID_OK;
	PUS_TcSecondaryHeader_t *structuredData=(PUS_TcSecondaryHeader_t *)input;

	if (isValid==M_TRUE)
	{
		if (structuredData->versionTcPus!=PUS_VERSION_NO)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}

	return isValid;
}
bool_t BLPVU_ValidatePUS_TmSecondaryHeader(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;

	*failureId = BLP_FID_OK;
	PUS_TmSecondaryHeader_t *structuredData=(PUS_TmSecondaryHeader_t *)input;

	if (isValid==M_TRUE)
	{
		if (structuredData->versionTmPus!=PUS_VERSION_NO)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}

	return isValid;
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
