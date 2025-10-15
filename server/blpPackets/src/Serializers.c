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
#include <BLP_Serializers.h>

/* local macros ---------------------------------------------------------------*/
/* none */

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
bool_t BLPS_UnexpectedValueUint16(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_UnexpectedValueUint16_t *structuredData);
bool_t BLPS_InvalidParameterValue(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_InvalidParameterValue_t *structuredData);

/* local prototypes -----------------------------------------------------------*/
/* none */

/* public functions -----------------------------------------------------------*/
bool_t BLPS_SerializeSetMode(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_SetMode_t *structuredData)
{
	bool_t isValid=M_TRUE;

	*totalDataSize=0;

	//CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	BLPSU_SerializeCCSDS_PrimaryHeader(target,targetNb,totalDataSize,&structuredData->ccsdsPrimaryHeader);
	//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	BLPSU_SerializePUS_TcSecondaryHeader(target,targetNb,totalDataSize,&structuredData->pusTcSecondaryHeader);
	//uint8_t mode;
	memcpy(&target[*totalDataSize],&structuredData->mode,sizeof(uint8_t));
	*totalDataSize+=sizeof(uint8_t);

	return isValid;
}

bool_t BLPS_SerializeAllTypes(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_AllTypes_t *structuredData)
{
	bool_t isValid=M_TRUE;

	*totalDataSize=0;

	//CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	BLPSU_SerializeCCSDS_PrimaryHeader(target,targetNb,totalDataSize,&structuredData->ccsdsPrimaryHeader);
	//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	BLPSU_SerializePUS_TcSecondaryHeader(target,targetNb,totalDataSize,&structuredData->pusTcSecondaryHeader);
	//uint8_t fieldUint8;
	memcpy(&target[*totalDataSize],&structuredData->fieldUint8,sizeof(uint8_t));
	*totalDataSize+=sizeof(uint8_t);
	//int8_t fieldInt8;
	memcpy(&target[*totalDataSize],&structuredData->fieldInt8,sizeof(int8_t));
	*totalDataSize+=sizeof(int8_t);
	//uint16_t fieldUint16;
	memcpy(&target[*totalDataSize],&structuredData->fieldUint16,sizeof(uint16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint16_t));
	*totalDataSize+=sizeof(uint16_t);
	//int16_t fieldInt16;
	memcpy(&target[*totalDataSize],&structuredData->fieldInt16,sizeof(int16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(int16_t));
	*totalDataSize+=sizeof(int16_t);
	//uint32_t fieldUint32;
	memcpy(&target[*totalDataSize],&structuredData->fieldUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);
	//int32_t fieldInt32;
	memcpy(&target[*totalDataSize],&structuredData->fieldInt32,sizeof(int32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(int32_t));
	*totalDataSize+=sizeof(int32_t);
	//uint64_t fieldUint64;
	memcpy(&target[*totalDataSize],&structuredData->fieldUint64,sizeof(uint64_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint64_t));
	*totalDataSize+=sizeof(uint64_t);
	//int64_t fieldInt64;
	memcpy(&target[*totalDataSize],&structuredData->fieldInt64,sizeof(int64_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(int64_t));
	*totalDataSize+=sizeof(int64_t);
	//float32_t fieldFloat32;
	memcpy(&target[*totalDataSize],&structuredData->fieldFloat32,sizeof(float32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(float32_t));
	*totalDataSize+=sizeof(float32_t);
	//float64_t fieldFloat64;
	memcpy(&target[*totalDataSize],&structuredData->fieldFloat64,sizeof(float64_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(float64_t));
	*totalDataSize+=sizeof(float64_t);


	return isValid;
}

bool_t BLPS_SerializeAllRanges(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_AllRanges_t *structuredData)
{
	bool_t isValid=M_TRUE;

	*totalDataSize=0;

	//CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	BLPSU_SerializeCCSDS_PrimaryHeader(target,targetNb,totalDataSize,&structuredData->ccsdsPrimaryHeader);
	//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	BLPSU_SerializePUS_TcSecondaryHeader(target,targetNb,totalDataSize,&structuredData->pusTcSecondaryHeader);

	//uint32_t maxIncUint32;
	memcpy(&target[*totalDataSize],&structuredData->maxIncUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);

	//uint32_t maxExcUint32;
	memcpy(&target[*totalDataSize],&structuredData->maxExcUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);

	//uint32_t minIncUint32;
	memcpy(&target[*totalDataSize],&structuredData->minIncUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);

	//uint32_t minExcUint32;
	memcpy(&target[*totalDataSize],&structuredData->minExcUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);

	//uint32_t fixedUint32;
	memcpy(&target[*totalDataSize],&structuredData->fixedUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);

	//uint32_t minMaxUint32;
	memcpy(&target[*totalDataSize],&structuredData->minMaxUint32,sizeof(uint32_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint32_t));
	*totalDataSize+=sizeof(uint32_t);

	return isValid;
}

bool_t BLPS_SerializeImageSegment(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_ImageSegment_t *structuredData)
{
	bool_t isValid=M_TRUE;

	//CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	BLPSU_SerializeCCSDS_PrimaryHeader(target,targetNb,totalDataSize,&structuredData->ccsdsPrimaryHeader);
	//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	BLPSU_SerializePUS_TmSecondaryHeader(target,targetNb,totalDataSize,&structuredData->pusTmSecondaryHeader);

	//uint16_t numberOfPixels;
	memcpy(&target[*totalDataSize],&structuredData->numberOfPixels,sizeof(uint16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint16_t));
	*totalDataSize+=sizeof(uint16_t);

	//uint8_t pixel[20];
	for (uint16_t pixelIx=0;pixelIx<structuredData->numberOfPixels;pixelIx++)
	{
		memcpy(&target[*totalDataSize],&structuredData->pixel[pixelIx],sizeof(uint8_t));
		*totalDataSize+=sizeof(uint8_t);
	}

	return isValid;
}

bool_t BLPS_SerializeFailReport(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_FailReport_t *structuredData)
{
	bool_t isValid=M_TRUE;

	//CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	BLPSU_SerializeCCSDS_PrimaryHeader(target,targetNb,totalDataSize,&structuredData->ccsdsPrimaryHeader);
	//PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	BLPSU_SerializePUS_TmSecondaryHeader(target,targetNb,totalDataSize,&structuredData->pusTmSecondaryHeader);
	//PUS_AcceptanceReport_t pusAcceptanceReport;
	BLPSU_SerializePUS_AcceptanceReport(target,targetNb,totalDataSize,&structuredData->pusAcceptanceReport);
	//uint16_t failureId;
	memcpy(&target[*totalDataSize],&structuredData->failureId,sizeof(uint16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint16_t));
	*totalDataSize+=sizeof(uint16_t);
	//BLP_UnexpectedValueUint16_t unexpectedValueUint16;
	if (structuredData->failureId==BLP_FID_INCONSISTENT_SIZE)
	{
		BLPS_UnexpectedValueUint16(target,targetNb,totalDataSize,(BLP_UnexpectedValueUint16_t*)&structuredData->failureInfo);
	}
	//BLP_InvalidParameterValue_t invalidParameterValue;
	if (structuredData->failureId==BLP_FID_INVALID_PARAMETER_VALUE)
	{
		BLPS_InvalidParameterValue(target,targetNb,totalDataSize,(BLP_InvalidParameterValue_t*)&structuredData->failureInfo);
	}

	return isValid;
}
/* local functions ------------------------------------------------------------*/
bool_t BLPS_UnexpectedValueUint16(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_UnexpectedValueUint16_t *structuredData)
{
	bool_t isValid=M_TRUE;

	//uint16_t expectedValue;
	memcpy(&target[*totalDataSize],&structuredData->expectedValue,sizeof(uint16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint16_t));
	*totalDataSize+=sizeof(uint16_t);
	//uint16_t foundValue;
	memcpy(&target[*totalDataSize],&structuredData->foundValue,sizeof(uint16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint16_t));
	*totalDataSize+=sizeof(uint16_t);

	return isValid;
}
bool_t BLPS_InvalidParameterValue(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,BLP_InvalidParameterValue_t *structuredData)
{
	bool_t isValid=M_TRUE;

	//uint16_t parameterCounter;
	memcpy(&target[*totalDataSize],&structuredData->parameterCounter,sizeof(uint16_t));
	LEND_Host2Network(&target[*totalDataSize],sizeof(uint16_t));
	*totalDataSize+=sizeof(uint16_t);

	return isValid;
}

/* end */
