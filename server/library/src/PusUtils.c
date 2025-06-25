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
#include <SBCC_CcsdsUtils.h>
#include <LIB_PusUtils.h>

/* local macros ---------------------------------------------------------------*/
/* none */

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
uint32_t pusTmTimeStamp=0;

/* local prototypes -----------------------------------------------------------*/
/* none */

/* public functions -----------------------------------------------------------*/
bool_t PUS_CreateTcDataField(uint8_t *target,uint16_t targetMaxNb,uint8_t *data, uint16_t dataNb,bool_t isWantedAcknowledgment, bool_t isWantedExecutionResult, uint8_t serviceType, uint8_t serviceSubType, uint16_t sourceId)
{
	bool_t isError=M_FALSE;

	PUS_TcSecondaryHeader_t header;
	PUS_CreateTcHeader(&header,isWantedAcknowledgment,isWantedExecutionResult,serviceType,serviceSubType,sourceId);

	isError=PUS_JoinTcHeaderAndData(target,targetMaxNb,&header,data,dataNb);

	return isError;

}

bool_t PUS_CreateTmDataField(uint8_t *target,uint16_t targetMaxNb,uint8_t *data, uint16_t dataNb, uint8_t serviceType, uint8_t serviceSubType,uint16_t messageTypeCounter,uint16_t destinationId)
{
	bool_t isError=M_FALSE;

	PUS_TmSecondaryHeader_t header;
	PUS_CreateTmHeader(&header,serviceType,serviceSubType,messageTypeCounter,destinationId);

	isError=PUS_JoinTmHeaderAndData(target,targetMaxNb,&header,data,dataNb);

	return isError;
}

void PUS_CreateTcHeader(PUS_TcSecondaryHeader_t *self, bool_t isWantedAcknowledgment, bool_t isWantedExecutionResult, uint8_t serviceType, uint8_t serviceSubType, uint16_t sourceId)
{
	memset(self,0,sizeof(PUS_TcSecondaryHeader_t));
	//uint8_t versionTcPus:4; //should be = 1 for ECSS-E-70-41A
	self->versionTcPus=PUS_VERSION_NO;
	//uint8_t acknowledgementFlags:4; //bit 3 = successful acknowledgment //bit 2 = successful start of execution //bit 1 = successful progress of execution // successful end of execution
	self->acknowledgementFlags= (self->acknowledgementFlags) | ( isWantedAcknowledgment << 3);
	self->acknowledgementFlags= (self->acknowledgementFlags) | ( isWantedExecutionResult << 0);
	//uint8_t serviceType;
	self->serviceType=serviceType;
	//uint8_t serviceSubType;
	self->serviceSubType=serviceSubType;
	//uint16_t sourceId;
	self->sourceId=sourceId;
	//uint8_t spare0; //total size of header needs to be of a integer word size
}
void PUS_CreateTmHeader(PUS_TmSecondaryHeader_t *self, uint8_t serviceType, uint8_t serviceSubType,uint16_t messageTypeCounter,uint16_t destinationId)
{
	memset(self,0,sizeof(PUS_TmSecondaryHeader_t));
	//uint8_t versionTmPus:4; //should be = 1 for ECSS-E-70-41A
	self->versionTmPus=1;
	//uint8_t scTimeReferenceStatus:4; //0 when not supported NOTS
	self->scTimeReferenceStatus=0;
	//uint8_t serviceType;
	self->serviceType=serviceType;
	//uint8_t serviceSubType;
	self->serviceSubType=serviceSubType;
	//uint16_t messageTypeCounter;//per pid, per type/subtype, or 0 if not supported NOTS
	self->messageTypeCounter=messageTypeCounter;
	//uint16_t destinationId;
	self->destinationId=destinationId;
	//uint32_t time;
	self->time=pusTmTimeStamp;
	//uint8_t spare0; //total size of header needs to be of a integer word size
}

PUS_TcSecondaryHeader_t *PUS_GetTcHeader(uint8_t *packetBuffer,uint16_t packetNb)
{
	CCSDS_Packet_t *packet = (CCSDS_Packet_t *)packetBuffer;
	PUS_TcSecondaryHeader_t *tcHeader=NULL;
	if (packet->primaryHeader.secondaryHeader==M_FALSE)
	{
		printf("warning: APP1_DataHandler received non PUS packet\n");
	}
	else
	{
		//validate
		if (PUS_IS_TC_HEADER_SIZE(packet))
		{
			//map tcHeader
			tcHeader=(PUS_TcSecondaryHeader_t *)&packetBuffer[sizeof(CCSDS_PrimaryHeader_t)];
		}
		else
		{
			printf("warning: APP1_DataHandler received non PUS packet\n");
		}
	}

	return tcHeader;
}

uint8_t *PUS_GetTcDataPointer(uint16_t *dataSize,uint8_t *packet,uint16_t pusDataLength)
{
	uint8_t *dataPointer=&packet[sizeof(CCSDS_PrimaryHeader_t)+sizeof(PUS_TcSecondaryHeader_t)];
	*dataSize=pusDataLength-sizeof(PUS_TcSecondaryHeader_t);

	return dataPointer;
}

void PUS_PrintTcHeader(PUS_TcSecondaryHeader_t *self)
{
	printf("TC Secondary Header packet:\n");
	printf("\t versionTcPus: %d\n",self->versionTcPus);
	printf("\t acknowledgementFlags: %d\n",self->acknowledgementFlags);
	printf("\t serviceType: %d\n",self->serviceType);
	printf("\t serviceSubType: %d\n",self->serviceSubType);
	printf("\t sourceId: %d\n",self->sourceId);
}

void PUS_PrintTmHeader(PUS_TmSecondaryHeader_t *self)
{
	printf("TM Secondary Header packet:\n");
	printf("\t versionTmPus: %d\n",self->versionTmPus);
	printf("\t scTimeReferenceStatus: %d\n",self->scTimeReferenceStatus);
	printf("\t serviceType: %d\n",self->serviceType);
	printf("\t serviceSubType: %d\n",self->serviceSubType);
	printf("\t messageTypeCounter: %d\n",self->messageTypeCounter);
	printf("\t destinationId: %d\n",self->destinationId);
	printf("\t time: %d\n",self->time);
}

bool_t PUS_JoinTcHeaderAndData(uint8_t *target,uint16_t targetMaxNb,PUS_TcSecondaryHeader_t *header,uint8_t *data, uint16_t dataNb)
{
	bool_t isError=M_FALSE;
	if (targetMaxNb<dataNb+sizeof(PUS_TcSecondaryHeader_t))
	{
		isError=M_TRUE;
		printf("warning: PUS_JoinTmHeaderAndData expected buffer space: %ld found: %d\n",dataNb+sizeof(PUS_TcSecondaryHeader_t),targetMaxNb);
	}
	else
	{
		memcpy(&target[0],header,sizeof(PUS_TcSecondaryHeader_t));
		memcpy(&target[sizeof(PUS_TcSecondaryHeader_t)],data,dataNb);
	}

	return isError;
}

bool_t PUS_JoinTmHeaderAndData(uint8_t *target,uint16_t targetMaxNb,PUS_TmSecondaryHeader_t *header,uint8_t *data, uint16_t dataNb)
{
	bool_t isError=M_FALSE;
	if (targetMaxNb<dataNb+sizeof(PUS_TmSecondaryHeader_t))
	{
		isError=M_TRUE;
		printf("warning: PUS_JoinTmHeaderAndData expected buffer space: %ld found: %d\n",dataNb+sizeof(PUS_TmSecondaryHeader_t),targetMaxNb);
	}
	else
	{
		memcpy(&target[0],header,sizeof(PUS_TmSecondaryHeader_t));
		memcpy(&target[sizeof(PUS_TmSecondaryHeader_t)],data,dataNb);
	}

	return isError;
}

void PUS_PrintPacket(uint8_t *packet, uint16_t packetNb)
{
	CCSDS_Packet_t *self=(CCSDS_Packet_t*) packet;
	if (M_TRUE==PUS_IsPacketSizeValid(packet,packetNb))
	{
		if (self->primaryHeader.packetType==1)
		{
			PUS_PrintTc(packet,packetNb);
		}
		else
		{
			PUS_PrintTm(packet,packetNb);
		}
	}
}

void PUS_PrintTc(uint8_t *packet, uint16_t packetNb)
{
	CCSDS_Packet_t *self=(CCSDS_Packet_t*) packet;
	//validation
	if (M_TRUE==PUS_IsPacketSizeValid(packet,packetNb))
	{
		//primary header
		CCSDS_PrintPrimaryHeader(self);
		uint16_t remainingData=CCSDS_PACKET_DATA_LENGHT(self);
		//secondary header
		if (self->primaryHeader.secondaryHeader)
		{
			PUS_PrintTcHeader((PUS_TcSecondaryHeader_t *)&packet[sizeof(CCSDS_PrimaryHeader_t)]);
			remainingData-=sizeof(PUS_TcSecondaryHeader_t);
		}
		//data
		printf("data(%d): \n\t",remainingData);
		for (uint16_t bIx=0;bIx<remainingData;bIx++)
		{
			printf(" %d",((uint8_t*)&self->data)[bIx+sizeof(PUS_TcSecondaryHeader_t)]);
		}
		printf("\n");
	}

}

void PUS_PrintTm(uint8_t *packet, uint16_t packetNb)
{
	CCSDS_Packet_t *self=(CCSDS_Packet_t*) packet;
	//validation
	if (M_TRUE==PUS_IsPacketSizeValid(packet,packetNb))
	{
		//primary header
		CCSDS_PrintPrimaryHeader(self);
		uint16_t remainingData=CCSDS_PACKET_DATA_LENGHT(self);
		//secondary header
		if (self->primaryHeader.secondaryHeader)
		{
			PUS_PrintTmHeader((PUS_TmSecondaryHeader_t *)&packet[sizeof(CCSDS_PrimaryHeader_t)]);
			remainingData-=sizeof(PUS_TmSecondaryHeader_t);
		}
		//data

		printf("data(%d): \n\t",remainingData);
		for (uint16_t bIx=0;bIx<remainingData;bIx++)
		{
			printf(" %d",((uint8_t*)&self->data)[bIx+sizeof(PUS_TmSecondaryHeader_t)]);
		}
		printf("\n");
	}

}

bool_t PUS_IsPacketSizeValid(uint8_t *packet, uint16_t packetNb)
{
	bool_t isValid=M_TRUE;
	CCSDS_Packet_t *packetStructured = (CCSDS_Packet_t *)packet;

	//cssds size
	isValid=CCSDS_IsPacketSizeValid(packetStructured,packetNb);

	//pus header size
	if (isValid)
	{
		if (packetStructured->primaryHeader.secondaryHeader)
		{
			uint16_t expectedSize=sizeof(CCSDS_PrimaryHeader_t);
			if (packetStructured->primaryHeader.packetType==CCSDS_PRIMARY_HEADER_IS_TM)
			{
				expectedSize+=sizeof(PUS_TmSecondaryHeader_t);
			}
			else
			{
				expectedSize+=sizeof(PUS_TcSecondaryHeader_t);
			}
			//printf("debug %d %d\n",packetNb,expectedSize);
			if (packetNb<expectedSize)
			{
				isValid=M_FALSE;
			}
		}
	}

	return isValid;
}

void PUS_SetTmTimeStamp(uint32_t timeStamp_p)
{
	pusTmTimeStamp=timeStamp_p;
}
/* local functions ------------------------------------------------------------*/
/* none */

/* end */
