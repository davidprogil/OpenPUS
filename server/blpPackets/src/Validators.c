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
#include <LIB_Crc.h>
#include <BLP_Deserializers.h>
#include <BLP_Validators.h>
#include <BLP_Fillers.h>

/* local macros ---------------------------------------------------------------*/
#define BLP_VALIDATOR_FUNCTION_NO (5)

/* local types ----------------------------------------------------------------*/
typedef struct _BLPV_ValidatorFunctionLut_t_
{
	uint16_t packetId;
	BLPV_ValidatorFunction_t *validator;
}BLPV_ValidatorFunctionLut_t;

uint32_t BLPV_EnumMode_AllowedValues[BLP_MODE_NB]={BLP_MODE_SAFE,BLP_MODE_ALIVENESS,BLP_MODE_FLYBY,BLP_MODE_LANDING};

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
BLPV_ValidatorFunctionLut_t BLP_ValidatorFunctionLut[BLP_VALIDATOR_FUNCTION_NO] =
{
		{BLP_SETMODE_PACKETID,BLPVU_ValidateSetMode},
		{BLP_ALLTYPES_PACKETID,BLPVU_ValidateAllTypes},
		{BLP_ALLRANGES_PACKETID,BLPVU_ValidateAllRanges},
		{BLP_IMAGESEGMENT_PACKETID,BLPVU_ValidateImageSegment},
		{BLP_FAILREPORT_PACKETID,BLPVU_ValidateFailureReport}
};

/* local prototypes -----------------------------------------------------------*/
BLPV_ValidatorFunction_t *BLPD_GetValidatorFunction(uint16_t packetId);
bool_t BLPV_IsEnumerationValueValid(uint32_t *allowedValues,uint16_t allowedValuesNb,uint32_t value);
BLPV_ValidatorFunction_t BLPV_ValidateInvalidParameterValue;
BLPV_ValidatorFunction_t BLPV_ValidateUnexpectedValueUint16;

/* public functions -----------------------------------------------------------*/
bool_t BLPV_ValidatePacket(uint8_t *packetRaw,uint16_t totalLength, void *structuredData,uint16_t outputNb, uint16_t *packetId, uint16_t *failureId, uint8_t *failureInfo)
{
	bool_t isValid=M_TRUE;
	CCSDS_Packet_t *packetStructured = (CCSDS_Packet_t *)packetRaw;
	BLP_DeserializerFunction_t *deserializer=NULL;
	*failureId=BLP_FID_OK;
	uint16_t parameterCounter;
	PUS_Crc_t expectedCrc=0;

	//calculate CRC
	if (totalLength>sizeof(uint16_t))
	{
		expectedCrc=CRC_CcsdsCrc16Get(PUS_DEFAULT_CRC_SEED, PUS_DEFAULT_CRC_OFFSET, packetRaw, totalLength-sizeof(PUS_Crc_t));
	}
	//if it is big enough to have primary header
	//if data length is correct
	if (isValid)
	{
		isValid=CCSDS_IsPacketSizeValid((CCSDS_Packet_t *)packetRaw,totalLength);
		if (isValid==M_FALSE)
		{
			*failureId=BLP_FID_BAD_LENGTH;
			printf("Warning BLPV_ValidatePacket bad length\n");
		}
	}

	//if it has secondary header
	if (isValid)
	{
		isValid=(packetStructured->primaryHeader.secondaryHeader==M_TRUE);
		if (isValid==M_FALSE)
		{
			*failureId=BLP_FID_NO_PUS;
			printf("Warning BLPV_ValidatePacket not a PUS packet \n");
		}
	}

	//if CRC is correct
	if (isValid)
	{
		PUS_Crc_t foundCrc=0;
		isValid=PUS_IsCrcValid(packetRaw,totalLength,&expectedCrc,&foundCrc);
		if (isValid==M_FALSE)
		{
			*failureId=BLP_FID_BAD_CRC;
			BLP_UnexpectedValueUint16_t unexpectedValue;
			memcpy((uint8_t*)&failureInfo,&unexpectedValue,sizeof(unexpectedValue));
			printf("Warning BLPV_ValidatePacket CRC incorrect\n");
		}
	}

	//if service and sub-service are recognized
	if (isValid)
	{
		//get packet ID
		*packetId=PUS_GetServiceSubServiceCompound(packetRaw,totalLength);
		//get deserializer function
		deserializer=BLPD_GetDeserializerFunction(*packetId);
		if (deserializer==NULL)
		{
			isValid=M_FALSE;
		}
		if (isValid==M_FALSE)
		{
			*failureId=BLP_FID_BAD_PACKET_ID;
			printf("Warning BLPV_ValidatePacket service and/or subservice unknown \n");
		}
	}

	//if specific packet type size is correct and parameters validated 1
	if (isValid)
	{
		//deserialize
		isValid=deserializer(structuredData,outputNb,NULL,packetRaw,totalLength);

		BLP_UnexpectedValueUint16_t unexpectedValue;
		unexpectedValue.foundValue=totalLength;
		unexpectedValue.expectedValue=CCSDS_PACKET_TOTAL_LENGHT((CCSDS_Packet_t*)packetRaw);

		if (unexpectedValue.foundValue!=unexpectedValue.expectedValue)
		{
			isValid=M_FALSE;
		}

		if (isValid==M_FALSE)
		{
			*failureId=BLP_FID_INCONSISTENT_SIZE;

			memcpy((uint8_t*)&failureInfo,&unexpectedValue,sizeof(unexpectedValue));
			printf("Warning BLPV_ValidatePacket inconsistent size found: %d expected: %d \n",unexpectedValue.foundValue,unexpectedValue.expectedValue);
		}
	}

	//if specific packet type size is correct and parameters validated 2
	if (isValid)
	{
		//get validator and validate
		BLPV_ValidatorFunction_t *validatorFunction=BLPD_GetValidatorFunction(*packetId);

		if (validatorFunction!=NULL)
		{
			isValid=validatorFunction(structuredData,failureId,failureInfo,&parameterCounter);
		}
		else
		{
			*failureId=BLP_FID_BAD_PACKET_ID;
			isValid=M_FALSE;
		}

		if (isValid==M_FALSE)
		{
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
			((BLP_InvalidParameterValue_t *)failureInfo)->parameterCounter=parameterCounter;
			printf("Warning BLPV_ValidatePacket bad packet format 2 \n");
		}
	}

	return isValid;
}

bool_t BLPVU_ValidateSetMode(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	BLP_SetMode_t *structuredData=(BLP_SetMode_t *)input;

	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidateCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,failureId,failureInfo,parameterCounter);
	}
	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidatePUS_TcSecondaryHeader(&structuredData->pusTcSecondaryHeader,failureId,failureInfo,parameterCounter);
	}
	if (isValid==M_TRUE)
	{
		isValid=BLPV_IsEnumerationValueValid(BLPV_EnumMode_AllowedValues,BLP_MODE_NB,structuredData->mode);
		*parameterCounter+=1;
	}

	return isValid;
}

bool_t BLPVU_ValidateAllTypes(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	BLP_SetMode_t *structuredData=(BLP_SetMode_t *)input;

	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidateCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,failureId,failureInfo,parameterCounter);
	}
	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidatePUS_TcSecondaryHeader(&structuredData->pusTcSecondaryHeader,failureId,failureInfo,parameterCounter);
	}
	//no other fields to validate

	return isValid;
}

bool_t BLPVU_ValidateAllRanges(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	BLP_AllRanges_t *structuredData=(BLP_AllRanges_t *)input;

	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidateCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,failureId,failureInfo,parameterCounter);
	}
	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidatePUS_TcSecondaryHeader(&structuredData->pusTcSecondaryHeader,failureId,failureInfo,parameterCounter);
	}

	//uint32_t maxIncUint32;
	if (isValid==M_TRUE)
	{
		if (structuredData->maxIncUint32>17)
		{
			isValid=M_FALSE;
			*failureId = BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}
	//uint32_t maxExcUint32;
	if (isValid==M_TRUE)
	{
		if (structuredData->maxExcUint32>=17)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}
	//uint32_t minIncUint32;
	if (isValid==M_TRUE)
	{
		if (structuredData->minIncUint32<17)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}
	//uint32_t minExcUint32;
	if (isValid==M_TRUE)
	{
		if (structuredData->minExcUint32<=17)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}
	//uint32_t fixedUint32;
	if (isValid==M_TRUE)
	{
		if (structuredData->fixedUint32!=17)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}
	//uint32_t minMaxUint32;
	if (isValid==M_TRUE)
	{
		if (structuredData->minMaxUint32>18)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		if (structuredData->minMaxUint32<16)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}

	return isValid;
}

bool_t BLPVU_ValidateImageSegment(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	BLP_ImageSegment_t *structuredData=(BLP_ImageSegment_t *)input;

	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidateCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,failureId,failureInfo,parameterCounter);
	}
	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidatePUS_TmSecondaryHeader(&structuredData->pusTmSecondaryHeader,failureId,failureInfo,parameterCounter);
	}

	if (isValid==M_TRUE)
	{
		if (structuredData->numberOfPixels>20)
		{
			isValid=M_FALSE;
			*failureId=BLP_FID_INVALID_PARAMETER_VALUE;
		}
		*parameterCounter+=1;
	}
	//no other fields to validate

	return isValid;
}


bool_t BLPVU_ValidateFailureReport(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	BLP_FailReport_t *structuredData=(BLP_FailReport_t *)input;

	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidateCCSDS_PrimaryHeader(&structuredData->ccsdsPrimaryHeader,failureId,failureInfo,parameterCounter);
	}
	if (isValid==M_TRUE)
	{
		isValid=BLPVU_ValidatePUS_TmSecondaryHeader(&structuredData->pusTmSecondaryHeader,failureId,failureInfo,parameterCounter);
	}

	if (structuredData->failureId==BLP_FID_INVALID_PARAMETER_VALUE)
	{
		BLPV_ValidateInvalidParameterValue((BLP_InvalidParameterValue_t*)&structuredData->failureInfo,failureId,failureInfo,parameterCounter);
	}

	if (structuredData->failureId==BLP_FID_INCONSISTENT_SIZE)
	{
		BLPV_ValidateUnexpectedValueUint16((BLP_UnexpectedValueUint16_t*)&structuredData->failureInfo,failureId,failureInfo,parameterCounter);
	}
	//no other fields to validate

	return isValid;
}

bool_t BLPV_ValidateInvalidParameterValue(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	//no other fields to validate

	return isValid;
}

bool_t BLPV_ValidateUnexpectedValueUint16(void *input,uint16_t *failureId, uint8_t *failureInfo,uint16_t *parameterCounter)
{
	bool_t isValid=M_TRUE;
	*failureId = BLP_FID_OK;

	//no other fields to validate

	return isValid;
}

/* local functions ------------------------------------------------------------*/
BLPV_ValidatorFunction_t *BLPD_GetValidatorFunction(uint16_t packetId)
{
	BLPV_ValidatorFunction_t *validator=NULL;

	for (uint16_t fIx=0;fIx<BLP_VALIDATOR_FUNCTION_NO;fIx++)
	{
		if (packetId==BLP_ValidatorFunctionLut[fIx].packetId)
		{
			validator=BLP_ValidatorFunctionLut[fIx].validator;
		}
	}

	return validator;
}

bool_t BLPV_IsEnumerationValueValid(uint32_t *allowedValues,uint16_t allowedValuesNb,uint32_t value)
{
	bool_t isFound=M_FALSE;

	for (uint16_t aIx=0;aIx<allowedValuesNb;aIx++)
	{
		if (value==allowedValues[aIx])
		{
			isFound=M_TRUE;
		}
	}

	return (isFound==M_TRUE);
}

/* end */
