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
#include <BLP_Printers.h>

/* local macros ---------------------------------------------------------------*/
#define BLPP_LABELSIZE_NB (255)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
void BLPP_PrintUnexpectedValueUint16(BLP_UnexpectedValueUint16_t *structureData);
void BLPP_PrintInvalidParameterValue(BLP_InvalidParameterValue_t *structureData);

/* public functions -----------------------------------------------------------*/
//type functions
void BLPP_PrintEnumMode(uint8_t *target,BLP_EnumMode_t mode)
{
	strcpy((char*)target,"Unk.");
	switch (mode)
	{
	case BLP_MODE_SAFE:
		strcpy((char*)target,"MODE_SAFE");
		break;
	case BLP_MODE_ALIVENESS:
		strcpy((char*)target,"MODE_ALIVENESS");
		break;
	case BLP_MODE_FLYBY:
		strcpy((char*)target,"MODE_FLYBY");
		break;
	case BLP_MODE_LANDING:
		strcpy((char*)target,"MODE_LANDING");
		break;
	default:
		strcpy((char*)target,"Unk.");
		break;
	}
}

//universal printer
void BLPP_Print(uint8_t *target,uint16_t targetNb)
{
	uint16_t packetId=PUS_GetServiceSubServiceCompound(target,targetNb);
	switch (packetId)
	{
	case BLP_SETMODE_PACKETID:
		BLPP_PrintSetMode((BLP_SetMode_t*)target);
		break;
	case BLP_ALLTYPES_PACKETID:
		BLPP_PrintAllTypes((BLP_AllTypes_t*)target);
		break;
	case BLP_ALLRANGES_PACKETID:
		BLPP_PrintAllRanges((BLP_AllRanges_t*)target);
		break;
	case BLP_IMAGESEGMENT_PACKETID:
		BLPP_PrintImageSegment((BLP_ImageSegment_t*)target);
		break;
	case BLP_FAILREPORT_PACKETID:
		BLPP_PrintFailReport((BLP_FailReport_t*)target);
		break;
	default:
		printf("warning BLPP_Print unknown packet, can not print\n");
	}
}

//packet functions
void BLPP_PrintSetMode(BLP_SetMode_t *structureData)
{
	uint8_t modeLabel[BLPP_LABELSIZE_NB];

	printf("\t SetMode \n");
	BLPPU_PrintCCSDS_PrimaryHeader(&structureData->ccsdsPrimaryHeader);
	BLPPU_PrintPUS_TcSecondaryHeader(&structureData->pusTcSecondaryHeader);

	BLPP_PrintEnumMode(modeLabel,structureData->mode);
	printf("\t mode: %d - %s\n",structureData->mode,modeLabel);

}

void BLPP_PrintAllTypes(BLP_AllTypes_t *structureData)
{
	printf("\t AllTypes \n");
	BLPPU_PrintCCSDS_PrimaryHeader(&structureData->ccsdsPrimaryHeader);
	BLPPU_PrintPUS_TcSecondaryHeader(&structureData->pusTcSecondaryHeader);

	printf("\t fieldUint8: %d\n",structureData->fieldUint8);
	printf("\t fieldInt8: %d\n",structureData->fieldInt8);
	printf("\t fieldUin16: %d\n",structureData->fieldUint16);
	printf("\t fieldInt16: %d\n",structureData->fieldInt16);
	printf("\t fieldUin32: %d\n",structureData->fieldUint32);
	printf("\t fieldInt32: %d\n",structureData->fieldInt32);
	printf("\t fieldUin64: %ld\n",structureData->fieldUint64);
	printf("\t fieldInt64: %ld\n",structureData->fieldInt64);
	printf("\t fieldFloat32: %f\n",structureData->fieldFloat32);
	printf("\t fieldFloat64: %f\n",structureData->fieldFloat64);
}

void BLPP_PrintAllRanges(BLP_AllRanges_t *structureData)
{
	printf("\t AllRanges \n");
	BLPPU_PrintCCSDS_PrimaryHeader(&structureData->ccsdsPrimaryHeader);
	BLPPU_PrintPUS_TcSecondaryHeader(&structureData->pusTcSecondaryHeader);

	//uint32_t maxIncUint32;
	printf("\t maxIncUint32: %d\n",structureData->maxIncUint32);
	//uint32_t maxExcUint32;
	printf("\t maxExcUint32: %d\n",structureData->maxExcUint32);
	//uint32_t minIncUint32;
	printf("\t minIncUint32: %d\n",structureData->minIncUint32);
	//uint32_t minExcUint32;
	printf("\t minExcUint32: %d\n",structureData->minExcUint32);
	//uint32_t fixedUint32;
	printf("\t fixedUint32: %d\n",structureData->fixedUint32);
	//uint32_t minMaxUint32;
	printf("\t minMaxUint32: %d\n",structureData->minMaxUint32);
}

void BLPP_PrintImageSegment(BLP_ImageSegment_t *structureData)
{
	printf("\t ImageSegment \n");
	BLPPU_PrintCCSDS_PrimaryHeader(&structureData->ccsdsPrimaryHeader);
	BLPPU_PrintPUS_TmSecondaryHeader(&structureData->pusTmSecondaryHeader);
	//uint16_t numberOfPixels;
	printf("\t numberOfPixels: %d\n",structureData->numberOfPixels);
	//uint8_t pixel[20];
	printf("\t pixel: ");
	for (uint16_t pixelIx=0;pixelIx<structureData->numberOfPixels;pixelIx++)
	{
		printf("%d ",structureData->pixel[pixelIx]);
	}
	printf("\n");
}

void BLPP_PrintFailReport(BLP_FailReport_t *structureData)
{
	BLPPU_PrintCCSDS_PrimaryHeader(&structureData->ccsdsPrimaryHeader);
	BLPPU_PrintPUS_TmSecondaryHeader(&structureData->pusTmSecondaryHeader);
	BLPPU_PrintPUS_AcceptanceReport(&structureData->pusAcceptanceReport);

	printf("\t failureId: %d\n",structureData->failureId);

	//BLP_UnexpectedValueUint16_t unexpectedValueUint16;
	if (structureData->failureId==BLP_FID_INVALID_PARAMETER_VALUE)
	{
		BLPP_PrintInvalidParameterValue((BLP_InvalidParameterValue_t*)&structureData->failureInfo);
	}
	//BLP_InvalidParameterValue_t invalidParameterValue;
	else if (structureData->failureId==BLP_FID_INCONSISTENT_SIZE)
	{
		BLPP_PrintUnexpectedValueUint16((BLP_UnexpectedValueUint16_t*)&structureData->failureInfo);
	}
	else
	{
		printf("\t failureInfo: null\n");
	}
}
/* local functions ------------------------------------------------------------*/
void BLPP_PrintUnexpectedValueUint16(BLP_UnexpectedValueUint16_t *structureData)
{
	printf("\t foundValue: %d\n",structureData->foundValue);
	printf("\t expectedValue: %d\n",structureData->expectedValue);
}

void BLPP_PrintInvalidParameterValue(BLP_InvalidParameterValue_t *structureData)
{
	printf("\t parameterCounter: %d\n",structureData->parameterCounter);
}

/* end */
