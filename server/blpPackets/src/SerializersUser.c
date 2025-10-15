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
#include <BLP_SerializersUser.h>

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
bool_t BLPSU_SerializeCCSDS_PrimaryHeader(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,CCSDS_PrimaryHeader_t *structuredData)
{
	bool_t isValid=M_TRUE;

	if (sizeof(CCSDS_PrimaryHeader_t)<=(targetNb-*totalDataSize))
	{

		//change endieness of needed ones
		//uint16_t sequenceCount:14;
		uint16_t sequenceCount=structuredData->sequenceCount;
		LEND_Host2Network((uint8_t*)&sequenceCount,sizeof(uint16_t));
		structuredData->sequenceCount=((0x3FFF)&sequenceCount);
		//uint16_t dataLength;
		//don not do this here because it is done in PUS_FinalizePacket, called afterwards//LEND_Host2Network((uint8_t*)&structuredData->dataLength,sizeof(uint16_t));

		//do all the rest that does not need to be swapped
		memcpy(&target[*totalDataSize],structuredData,sizeof(CCSDS_PrimaryHeader_t));
		*totalDataSize+=sizeof(CCSDS_PrimaryHeader_t);

		//uint16_t arBase=*totalDataSize-sizeof(CCSDS_PrimaryHeader_t);//sizeof(PUS_TmSecondaryHeader_t)+sizeof(CCSDS_PrimaryHeader_t);
		//printf("debug3 BLPSU_SerializeCCSDS_PrimaryHeader 0x%02X 0x%02X 0x%02X 0x%02X\n",target[arBase+0],target[arBase+1],target[arBase+2],target[arBase+3]);

	}
	else
	{
		printf("warning: BLPSU_SerializeCCSDS_PrimaryHeader not enough space left in target structure.\n");
		isValid=M_FALSE;
	}

	return isValid;
}

bool_t BLPSU_SerializePUS_TcSecondaryHeader(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,PUS_TcSecondaryHeader_t *structuredData)
{
	bool_t isValid=M_TRUE;

	if (sizeof(PUS_TcSecondaryHeader_t)<=(targetNb-*totalDataSize))
	{

		//change endieness of needed ones
		//uint16_t sourceId;
		LEND_Host2Network((uint8_t*)&structuredData->sourceId,sizeof(uint16_t));

		memcpy(&target[*totalDataSize],structuredData,sizeof(PUS_TcSecondaryHeader_t));
		*totalDataSize+=sizeof(PUS_TcSecondaryHeader_t);
	}
	else
	{
		printf("warning: BLPSU_SerializePUS_TcSecondaryHeader not enough space left in target structure.\n");
		isValid=M_FALSE;
	}

	return isValid;
}

bool_t BLPSU_SerializePUS_TmSecondaryHeader(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,PUS_TmSecondaryHeader_t *structuredData)
{
	bool_t isValid=M_TRUE;

	if (sizeof(PUS_TmSecondaryHeader_t)<=(targetNb-*totalDataSize))
	{
		//change endieness of needed ones
		// uint16_t messageTypeCounter;//per pid, per type/subtype, or 0 if not supported NOTS
		LEND_Host2Network((uint8_t*)&structuredData->messageTypeCounter,sizeof(uint16_t));
		//uint16_t destinationId;
		LEND_Host2Network((uint8_t*)&structuredData->destinationId,sizeof(uint16_t));
		//uint32_t time;
		LEND_Host2Network((uint8_t*)&structuredData->time,sizeof(uint32_t));

		memcpy(&target[*totalDataSize],structuredData,sizeof(PUS_TmSecondaryHeader_t));
		*totalDataSize+=sizeof(PUS_TmSecondaryHeader_t);
	}
	else
	{
		printf("warning: BLPSU_SerializePUS_TmSecondaryHeader not enough space left in target structure.\n");
		isValid=M_FALSE;
	}

	return isValid;
}

bool_t BLPSU_SerializePUS_AcceptanceReport(uint8_t *target,uint16_t targetNb,uint16_t *totalDataSize,PUS_AcceptanceReport_t *structuredData)
{
	bool_t isValid=M_TRUE;

	if (sizeof(PUS_AcceptanceReport_t)<=(targetNb-*totalDataSize))
	{
		//change endieness of needed ones
		//uint16_t applicationProcessId:11;
		//uint16_t applicationProcessId=structuredData->applicationProcessId;

		//uint8_t debug1[2];
		//memcpy(&debug1,&applicationProcessId,sizeof(uint16_t));
		//printf("debug2 structuredData->applicationProcessId 0x%X 0x%X\n",debug1[0],debug1[1]);

		//TODO LEND_Host2Network((uint8_t*)&applicationProcessId,sizeof(uint16_t));
		//TODO structuredData->applicationProcessId=((0x7FF)&(applicationProcessId>>3));

		//memcpy(&debug1,&applicationProcessId,sizeof(uint16_t));
		//printf("debug2 structuredData->applicationProcessId 0x%X 0x%X\n",debug1[0],debug1[1]);

		//uint16_t packetSequenceCount:14;
		//TODO uint16_t sequenceCount=structuredData->packetSequenceCount;
		//TODO LEND_Host2Network((uint8_t*)&sequenceCount,sizeof(uint16_t));
		//TODO structuredData->packetSequenceCount=((0x3FFF)&sequenceCount);

		//((uint8_t*)(&structuredData))[0]=0xAB;

		memcpy(&target[*totalDataSize],structuredData,sizeof(PUS_AcceptanceReport_t));
		*totalDataSize+=sizeof(PUS_AcceptanceReport_t);

		//uint16_t arBase=*totalDataSize-sizeof(PUS_AcceptanceReport_t);//sizeof(PUS_TmSecondaryHeader_t)+sizeof(CCSDS_PrimaryHeader_t);
		//printf("debug3 BLPSU_SerializePUS_AcceptanceReport 0x%02X 0x%02X 0x%02X 0x%02X\n",target[arBase+0],target[arBase+1],target[arBase+2],target[arBase+3]);
	}
	else
	{
		printf("warning: BLPSU_SerializePUS_AcceptanceReport not enough space left in target structure.\n");
		isValid=M_FALSE;
	}

	return isValid;
}
/* local functions ------------------------------------------------------------*/
/* none */

/* end */
