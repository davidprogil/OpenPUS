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
#include <BLP_DeserializersUser.h>

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
bool_t BLPDU_DeserializeCCSDS_PrimaryHeader(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	CCSDS_PrimaryHeader_t *structuredData=(CCSDS_PrimaryHeader_t*)output;

	if ((outputNb-*walkingNb)<sizeof(CCSDS_PrimaryHeader_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		memcpy(structuredData,&packetRaw[*walkingNb],sizeof(CCSDS_PrimaryHeader_t));
		*walkingNb+=sizeof(CCSDS_PrimaryHeader_t);
	}
	//change endieness of needed ones
	//uint16_t sequenceCount:14;
	uint16_t sequenceCount=structuredData->sequenceCount;
	LEND_Network2Host((uint8_t*)&sequenceCount,sizeof(uint16_t));
	structuredData->sequenceCount=((0x3FFF)&sequenceCount);
	//uint16_t dataLength; ;//done in packet validation which occurs prior
	//LEND_Host2Network((uint8_t*)&structureData->dataLength,sizeof(uint16_t))


	return isValid;
}
bool_t BLPDU_DeserializePUS_TcSecondaryHeader(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	PUS_TcSecondaryHeader_t *structuredData=(PUS_TcSecondaryHeader_t*)output;

	if ((outputNb-*walkingNb)<sizeof(PUS_TcSecondaryHeader_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		memcpy(structuredData,&packetRaw[*walkingNb],sizeof(PUS_TcSecondaryHeader_t));
		*walkingNb+=sizeof(PUS_TcSecondaryHeader_t);
	}

	//change endieness of needed ones
	LEND_Network2Host((uint8_t*)&structuredData->sourceId,sizeof(uint16_t));

	return isValid;
}

bool_t BLPDU_DeserializePUS_TmSecondaryHeader(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	PUS_TmSecondaryHeader_t *structuredData=(PUS_TmSecondaryHeader_t*)output;

	if ((outputNb-*walkingNb)<sizeof(PUS_TmSecondaryHeader_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		memcpy(structuredData,&packetRaw[*walkingNb],sizeof(PUS_TmSecondaryHeader_t));
		*walkingNb+=sizeof(PUS_TmSecondaryHeader_t);
	}

	//change endieness of needed ones
	//uint16_t messageTypeCounter;//per pid, per type/subtype, or 0 if not supported NOTS
	LEND_Network2Host((uint8_t*)&structuredData->messageTypeCounter,sizeof(uint16_t));
	//uint16_t destinationId;
	LEND_Network2Host((uint8_t*)&structuredData->destinationId,sizeof(uint16_t));
	//uint32_t time;
	LEND_Network2Host((uint8_t*)&structuredData->time,sizeof(uint32_t));


	return isValid;
}

bool_t BLPDU_DeserializePUS_AcceptanceReport(void *output,uint16_t outputNb,uint16_t *walkingNb,uint8_t *packetRaw,uint16_t packetRawNb)
{
	bool_t isValid=M_TRUE;
	uint16_t myWalkingNb=0;
	if (walkingNb==NULL) walkingNb=&myWalkingNb;
	PUS_AcceptanceReport_t *structuredData=(PUS_AcceptanceReport_t*)output;

	if ((outputNb-*walkingNb)<sizeof(PUS_AcceptanceReport_t))
	{
		isValid=M_FALSE;
	}
	else
	{
		memcpy(structuredData,&packetRaw[*walkingNb],sizeof(PUS_AcceptanceReport_t));
		*walkingNb+=sizeof(PUS_AcceptanceReport_t);
	}

	//change endieness of needed ones
	//uint16_t applicationProcessId:11;
	//uint16_t applicationProcessId=structuredData->applicationProcessId;
	//printf("debug BLPDU_DeserializePUS_AcceptanceReport 0x%X\n",applicationProcessId);
	//TODO LEND_Network2Host((uint8_t*)&applicationProcessId,sizeof(uint16_t));
	//TODO structuredData->applicationProcessId=((0x7FF)&applicationProcessId);
	//uint16_t packetSequenceCount:14;
	//TODO uint16_t packetSequenceCount=structuredData->packetSequenceCount;
	//TODO LEND_Network2Host((uint8_t*)&packetSequenceCount,sizeof(uint16_t));
	//TODO structuredData->packetSequenceCount=((0x3FFF)&packetSequenceCount);


	return isValid;
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
