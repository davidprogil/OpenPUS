/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* application includes--------------------------------------------------------*/
/* none */

/* component includes----------------------------------------------------------*/
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
void BLPF_FillSetMode(BLP_SetMode_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TcSecondaryHeader_t *pusTcSecondaryHeader,BLP_EnumMode_t mode)
{
	memcpy(&target->ccsdsPrimaryHeader,ccsdsPrimaryHeader,sizeof(CCSDS_PrimaryHeader_t));
	memcpy(&target->pusTcSecondaryHeader,pusTcSecondaryHeader,sizeof(PUS_TcSecondaryHeader_t));
	target->mode=mode;

}

void BLPF_FillAllTypes(BLP_AllTypes_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TcSecondaryHeader_t *pusTcSecondaryHeader,uint8_t fieldUint8,int8_t fieldInt8,uint16_t fieldUint16,int16_t fieldInt16,uint32_t fieldUint32,int32_t fieldInt32,uint64_t fieldUint64,int64_t fieldInt64,float32_t fieldFloat32,float64_t fieldFloat64)
{
	memcpy(&target->ccsdsPrimaryHeader,ccsdsPrimaryHeader,sizeof(CCSDS_PrimaryHeader_t));
	memcpy(&target->pusTcSecondaryHeader,pusTcSecondaryHeader,sizeof(PUS_TcSecondaryHeader_t));

	target->fieldUint8=fieldUint8;target->fieldInt8=fieldInt8;
	target->fieldUint16=fieldUint16;target->fieldInt16=fieldInt16;
	target->fieldUint32=fieldUint32;target->fieldInt32=fieldInt32;
	target->fieldUint64=fieldUint64;target->fieldInt64=fieldInt64;
	target->fieldFloat32=fieldFloat32;target->fieldFloat64=fieldFloat64;
}

void BLPF_FillAllRanges(BLP_AllRanges_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TcSecondaryHeader_t *pusTcSecondaryHeader,uint32_t maxIncUint32,uint32_t maxExcUint32,uint32_t minIncUint32,uint32_t minExcUint32,uint32_t fixedUint32,uint32_t minMaxUint32)
{
	memcpy(&target->ccsdsPrimaryHeader,ccsdsPrimaryHeader,sizeof(CCSDS_PrimaryHeader_t));
	memcpy(&target->pusTcSecondaryHeader,pusTcSecondaryHeader,sizeof(PUS_TcSecondaryHeader_t));

	//uint32_t maxIncUint32;
	target->maxIncUint32=maxIncUint32;
	//uint32_t maxExcUint32;
	target->maxExcUint32=maxExcUint32;
	//uint32_t minIncUint32;
	target->minIncUint32=minIncUint32;
	//uint32_t minExcUint32;
	target->minExcUint32=minExcUint32;
	//uint32_t fixedUint32;
	target->fixedUint32=fixedUint32;
	//uint32_t minMaxUint32;
	target->minMaxUint32=minMaxUint32;
}

void BLPF_FillImageSegment(BLP_ImageSegment_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TmSecondaryHeader_t *pusTmSecondaryHeader,uint16_t numberOfPixels,uint8_t *pixel)
{
	memcpy(&target->ccsdsPrimaryHeader,ccsdsPrimaryHeader,sizeof(CCSDS_PrimaryHeader_t));
	memcpy(&target->pusTmSecondaryHeader,pusTmSecondaryHeader,sizeof(PUS_TmSecondaryHeader_t));

	target->numberOfPixels=numberOfPixels;
	memcpy(&target->pixel,pixel,sizeof(uint8_t)*numberOfPixels);
}

void BLPF_FillFailReport(BLP_FailReport_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TmSecondaryHeader_t *pusTmSecondaryHeader,PUS_AcceptanceReport_t *pusAcceptanceReport,uint16_t failureId,void *failureInfo,uint16_t failureInfoNb)
{
	memcpy(&target->ccsdsPrimaryHeader,ccsdsPrimaryHeader,sizeof(CCSDS_PrimaryHeader_t));
	memcpy(&target->pusTmSecondaryHeader,pusTmSecondaryHeader,sizeof(PUS_TmSecondaryHeader_t));
	memcpy(&target->pusAcceptanceReport,pusAcceptanceReport,sizeof(PUS_AcceptanceReport_t));

	target->failureId=failureId;

	memcpy(&target->failureInfo,failureInfo,failureInfoNb);
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
