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
#include <LIB_Endian.h>

/* component includes----------------------------------------------------------*/
#include <BLP_Deserializers.h>
#include <BLP_DeserializersUser.h>

/* local macros ---------------------------------------------------------------*/
#define BLPD_DESERIALIZER_FUNCTION_NO (5)

/* local types ----------------------------------------------------------------*/
typedef struct _BLP_DeserializerFunctionLut_t_
{
	uint16_t packetId;
	BLP_DeserializerFunction_t *deserializer;
}BLPD_DeserializerFunctionLut_t;

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
BLPD_DeserializerFunctionLut_t BLP_DeserializerFunctionLut[BLPD_DESERIALIZER_FUNCTION_NO] =
{
		{BLP_SETMODE_PACKETID,BLPD_DeserializeSetMode},
		{BLP_ALLTYPES_PACKETID,BLPD_DeserializeAllTypes},
		{BLP_ALLRANGES_PACKETID,BLPD_DeserializeAllRanges},
		{BLP_IMAGESEGMENT_PACKETID,BLPD_DeserializeImageSegment},
		{BLP_FAILREPORT_PACKETID,BLPD_DeserializeFailReport}
};

/* local prototypes -----------------------------------------------------------*/
BLP_DeserializerFunction_t BLPD_DeserializeUnexpectedValueUint16;
BLP_DeserializerFunction_t BLPD_DeserializeInvalidParameterValue;

/* public functions -----------------------------------------------------------*/
BLP_DeserializerFunction_t *BLPD_GetDeserializerFunction(uint16_t packetId)
{
	BLP_DeserializerFunction_t *deserializer=NULL;

	for (uint16_t fIx=0;fIx<BLPD_DESERIALIZER_FUNCTION_NO;fIx++)
	{
		if (packetId==BLP_DeserializerFunctionLut[fIx].packetId)
		{
			deserializer=BLP_DeserializerFunctionLut[fIx].deserializer;
		}
	}

	return deserializer;
}

bool_t BLPD_DeserializeSetMode(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_SetMode_t *structuredData=(BLP_SetMode_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_SetMode_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		///CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
		isValid=BLPDU_DeserializeCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
		isValid=BLPDU_DeserializePUS_TcSecondaryHeader(&structuredData->pusTcSecondaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//uint8_t mode;
		structuredData->mode=(uint8_t)packetRaw[*walkingNb];
		*walkingNb+=sizeof(uint8_t);
	}

	return isValid;
}


bool_t BLPD_DeserializeAllTypes(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_AllTypes_t *structuredData=(BLP_AllTypes_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_AllTypes_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		///CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
		isValid=BLPDU_DeserializeCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
		isValid=BLPDU_DeserializePUS_TcSecondaryHeader(&structuredData->pusTcSecondaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//uint8_t fieldUint8;
		structuredData->fieldUint8=(uint8_t)packetRaw[*walkingNb];
		*walkingNb+=sizeof(uint8_t);
		//int8_t fieldInt8;
		structuredData->fieldInt8=(int8_t)packetRaw[*walkingNb];
		*walkingNb+=sizeof(int8_t);
		//uint16_t fieldUint16;
		memcpy((uint8_t*)&structuredData->fieldUint16,&packetRaw[*walkingNb],sizeof(uint16_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldUint16,sizeof(uint16_t));
		*walkingNb+=sizeof(uint16_t);
		//int16_t fieldInt16;
		memcpy((uint8_t*)&structuredData->fieldInt16,&packetRaw[*walkingNb],sizeof(int16_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldInt16,sizeof(int16_t));
		*walkingNb+=sizeof(int16_t);
		//uint32_t fieldUint32;
		memcpy((uint8_t*)&structuredData->fieldUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
		//int32_t fieldInt32;
		memcpy((uint8_t*)&structuredData->fieldInt32,&packetRaw[*walkingNb],sizeof(int32_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldInt32,sizeof(int32_t));
		*walkingNb+=sizeof(int32_t);
		//uint64_t fieldUint64;
		memcpy((uint8_t*)&structuredData->fieldUint64,&packetRaw[*walkingNb],sizeof(uint64_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldUint64,sizeof(uint64_t));
		*walkingNb+=sizeof(uint64_t);
		//int64_t fieldInt64;
		memcpy((uint8_t*)&structuredData->fieldInt64,&packetRaw[*walkingNb],sizeof(int64_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldInt64,sizeof(int64_t));
		*walkingNb+=sizeof(int64_t);
		//float32_t fieldFloat32;
		memcpy((uint8_t*)&structuredData->fieldFloat32,&packetRaw[*walkingNb],sizeof(float32_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldFloat32,sizeof(float32_t));
		*walkingNb+=sizeof(float32_t);
		//float64_t fieldFloat64;
		memcpy((uint8_t*)&structuredData->fieldFloat64,&packetRaw[*walkingNb],sizeof(float64_t));
		LEND_Network2Host((uint8_t*)&structuredData->fieldFloat64,sizeof(float64_t));
		*walkingNb+=sizeof(float64_t);

	}

	return isValid;
}

bool_t BLPD_DeserializeAllRanges(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_AllRanges_t *structuredData=(BLP_AllRanges_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_AllRanges_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		///CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
		isValid=BLPDU_DeserializeCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
		isValid=BLPDU_DeserializePUS_TcSecondaryHeader(&structuredData->pusTcSecondaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);

		//uint32_t maxIncUint32;
		memcpy((uint8_t*)&structuredData->maxIncUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->maxIncUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
		//uint32_t maxExcUint32;
		memcpy((uint8_t*)&structuredData->maxExcUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->maxExcUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
		//uint32_t minIncUint32;
		memcpy((uint8_t*)&structuredData->minIncUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->minIncUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
		//uint32_t minExcUint32;
		memcpy((uint8_t*)&structuredData->minExcUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->minExcUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
		//uint32_t fixedUint32;
		memcpy((uint8_t*)&structuredData->fixedUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->fixedUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
		//uint32_t minMaxUint32;
		memcpy((uint8_t*)&structuredData->minMaxUint32,&packetRaw[*walkingNb],sizeof(uint32_t));
		LEND_Network2Host((uint8_t*)&structuredData->minMaxUint32,sizeof(uint32_t));
		*walkingNb+=sizeof(uint32_t);
	}

	return isValid;
}

bool_t BLPD_DeserializeImageSegment(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_ImageSegment_t *structuredData=(BLP_ImageSegment_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_ImageSegment_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		///CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
		isValid=BLPDU_DeserializeCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
		isValid=BLPDU_DeserializePUS_TmSecondaryHeader(&structuredData->pusTmSecondaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);

		//uint16_t numberOfPixels;
		memcpy((uint8_t*)&structuredData->numberOfPixels,&packetRaw[*walkingNb],sizeof(uint16_t));
		LEND_Network2Host((uint8_t*)&structuredData->numberOfPixels,sizeof(uint16_t));
		*walkingNb+=sizeof(uint16_t);

		//uint8_t pixel[20];
		for (uint16_t pixelIx=0;pixelIx<structuredData->numberOfPixels;pixelIx++)
		{
			memcpy((uint8_t*)&structuredData->pixel[pixelIx],&packetRaw[*walkingNb],sizeof(uint8_t));
			*walkingNb+=sizeof(uint8_t);
		}

	}

	return isValid;
}

bool_t BLPD_DeserializeFailReport(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_FailReport_t *structuredData=(BLP_FailReport_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_FailReport_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		///CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
		isValid=BLPDU_DeserializeCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
		isValid=BLPDU_DeserializePUS_TmSecondaryHeader(&structuredData->pusTmSecondaryHeader,outputNb,walkingNb,packetRaw,packetRawNb);
		//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
		isValid=BLPDU_DeserializePUS_AcceptanceReport(&structuredData->pusAcceptanceReport,outputNb,walkingNb,packetRaw,packetRawNb);

		//uint16_t failureId;
		memcpy((uint16_t*)&structuredData->failureId,&packetRaw[*walkingNb],sizeof(uint16_t));
		LEND_Network2Host((uint8_t*)&structuredData->failureId,sizeof(uint16_t));
		*walkingNb+=sizeof(uint16_t);

		if (structuredData->failureId==BLP_FID_INVALID_PARAMETER_VALUE)
		{
			isValid=BLPD_DeserializeInvalidParameterValue((BLP_InvalidParameterValue_t*)&structuredData->failureInfo,outputNb,walkingNb,packetRaw,packetRawNb);
		}
		//BLP_InvalidParameterValue_t invalidParameterValue;
		if (structuredData->failureId==BLP_FID_INCONSISTENT_SIZE)
		{
			isValid=BLPD_DeserializeUnexpectedValueUint16((BLP_UnexpectedValueUint16_t*)&structuredData->failureInfo,outputNb,walkingNb,packetRaw,packetRawNb);
		}
	}

	return isValid;
}
/* local functions ------------------------------------------------------------*/
bool_t BLPD_DeserializeUnexpectedValueUint16(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_UnexpectedValueUint16_t *structuredData=(BLP_UnexpectedValueUint16_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_UnexpectedValueUint16_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		//uint16_t expectedValue;
		memcpy((uint8_t*)&structuredData->expectedValue,&packetRaw[*walkingNb],sizeof(uint16_t));
		LEND_Network2Host((uint8_t*)&structuredData->expectedValue,sizeof(uint16_t));
		*walkingNb+=sizeof(uint16_t);
		//uint16_t foundValue;
		memcpy((uint8_t*)&structuredData->foundValue,&packetRaw[*walkingNb],sizeof(uint16_t));
		LEND_Network2Host((uint8_t*)&structuredData->foundValue,sizeof(uint16_t));
		*walkingNb+=sizeof(uint16_t);
	}

	return isValid;
}

bool_t BLPD_DeserializeInvalidParameterValue(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	BLP_InvalidParameterValue_t *structuredData=(BLP_InvalidParameterValue_t*)output;

	if ((outputNb-*walkingNb)<sizeof(BLP_InvalidParameterValue_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		//uint16_t numberOfPixels;
		memcpy((uint8_t*)&structuredData->parameterCounter,&packetRaw[*walkingNb],sizeof(uint16_t));
		LEND_Network2Host((uint8_t*)&structuredData->parameterCounter,sizeof(uint16_t));
		*walkingNb+=sizeof(uint16_t);
	}

	return isValid;
}

/* end */
