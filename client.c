
/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* application includes--------------------------------------------------------*/
#include <configuration.h>
#include <ABOS_Osal.h>
#include <ABDL_DataLink.h>
#include <SBCC_CcsdsUtils.h>
#include <LIB_PusUtils.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
#define MAIN_INFINITE_CYCLE_PERIOD_MS (1000)

#define DPDU_PUS_SERVICE_ID (140)
#define DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID (1)
#define DPDU_PUS_CHANNELSTATUS_TC_SUBSERVICE_ID (2)
#define DPDU_PUS_CHANNELSTATUS_TM_SUBSERVICE_ID (3)

/* local types ----------------------------------------------------------------*/
typedef struct _DPDU_TmPduStatus_t_
{
	float32_t batteryLevel;
	uint8_t ch1isOn;
	float32_t ch1v;
	float32_t ch1ma;
	uint8_t ch2isOn;
	float32_t ch2v;
	float32_t ch2ma;
	uint8_t ch3isOn;
	float32_t ch3v;
	float32_t ch3ma;
	uint8_t ch4isOn;
	float32_t ch4v;
	float32_t ch4ma;
}DPDU_TmPduStatus_t;

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
ABOS_Osal_t osal;
ABDL_DataLink_t dataLink;
uint16_t sequenceCount=0;
bool_t isRunAgain=M_TRUE;
uint32_t upTime=0;
uint32_t upTimeSub=0;

/* local prototypes -----------------------------------------------------------*/
/* none */


/* public functions -----------------------------------------------------------*/
int main(int argc, char *argv[])
{
	printf("CLIENT\n");

	//hardware initialization
	//not applicable in standard linux pc

	//checks
	printf("size of CCSDS_PrimaryHeader_t: %ld\n", sizeof(CCSDS_PrimaryHeader_t));
	printf("size of PUS_TmSecondaryHeader_t: %ld\n",sizeof(PUS_TmSecondaryHeader_t));
	printf("size of PUS_TcSecondaryHeader_t: %ld\n",sizeof(PUS_TcSecondaryHeader_t));

	//library initializations
	//N/A

	//abstraction initialization
	ABOS_Init(&osal);
	ABDL_Init(&dataLink,M_FALSE);

	//other starts
	//N/A

	//Infinite Cycle
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];
	uint16_t receivedNb;
	uint8_t tcPacketData[sizeof(PUS_TcSecondaryHeader_t)+2];
	uint64_t dataSize;
	bool_t isError=M_FALSE;
	uint8_t channelIx=0;
	while (isRunAgain==M_TRUE)
	{

		printf("client %d\n",upTime);

		//send packets
		if ((upTimeSub==5)||(upTimeSub==10)||(upTimeSub==15)||(upTimeSub==20)||(upTimeSub==25))
		{
			printf("time to send packet\n");
			//data
			uint8_t dummyDataToSend[2] = {channelIx++,1};
			if (channelIx==4) channelIx=0;

			if (upTimeSub!=25)
			{
				dataSize=sizeof(PUS_TcSecondaryHeader_t)+2;
				isError=PUS_CreateTcDataField(
						tcPacketData,//uint8_t *target
						sizeof(tcPacketData),//uint16_t targetMaxNb
						dummyDataToSend,//uint8_t *data
						sizeof(dummyDataToSend),//uint16_t dataNb
						M_FALSE,//bool_t isWantedAcknowledgment
						M_FALSE,//bool_t isWantedExecutionResul
						DPDU_PUS_SERVICE_ID/*17*/,//uint8_t serviceType
						DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID,//uint8_t serviceSubType
						GROUND_APID);//uint16_t sourceId

			}
			else //instead of switching channels request status
			{
				dataSize=sizeof(PUS_TcSecondaryHeader_t);
				isError=PUS_CreateTcDataField(
						tcPacketData,//uint8_t *target
						sizeof(tcPacketData),//uint16_t targetMaxNb
						NULL,//uint8_t *data
						0,//uint16_t dataNb
						M_FALSE,//bool_t isWantedAcknowledgment
						M_FALSE,//bool_t isWantedExecutionResul
						DPDU_PUS_SERVICE_ID/*17*/,//uint8_t serviceType
						DPDU_PUS_CHANNELSTATUS_TC_SUBSERVICE_ID,//uint8_t serviceSubType
						GROUND_APID);//uint16_t sourceId
			}

			if(M_FALSE==isError)
			{
				//printf("size of packet to send: %ld\n",sizeof(packetBuffer));

				if (CCSDS_CreatePacket(
						packetBuffer, //target
						sizeof(packetBuffer), //targetNb
						M_TRUE, //isTc
						M_TRUE, //hasSecondaryHeader,
						DEV_APID,//apid,
						sequenceCount,
						dataSize,
						tcPacketData) ==M_FALSE)
				{

					//CCSDS_PrintPacket((CCSDS_Packet_t*) packetBuffer);
					PUS_PrintTc(packetBuffer,sizeof(packetBuffer));

					//send the packet
					ABDL_Send(&dataLink,packetBuffer,CCSDS_PACKET_TOTAL_LENGHT((CCSDS_Packet_t*)packetBuffer));

					//increment counter of sent packets, note, in CCSDS standard this counter is to be maintained for each PID
					sequenceCount++;
				}
				else
				{
					printf("warning: main, error creating packet\n");
				}
			}
			else
			{
				printf("warning: main, error creating PUS packet\n");
			}
		}
		//receive packets
		if (ABDL_GetOnePacket(&dataLink,packetBuffer,&receivedNb))
		{
			//CCSDS_PrintPacket((CCSDS_Packet_t*) packetBuffer);
			PUS_PrintPacket(packetBuffer,sizeof(packetBuffer));
			CCSDS_Packet_t *packet = (CCSDS_Packet_t *)packetBuffer;
			PUS_TmSecondaryHeader_t *tmHeader=PUS_GetTmHeader(packetBuffer,receivedNb);
			if (tmHeader!=NULL)
			{
				if ((tmHeader->serviceType==DPDU_PUS_SERVICE_ID) && (tmHeader->serviceSubType==DPDU_PUS_CHANNELSTATUS_TM_SUBSERVICE_ID))
				{
					DPDU_TmPduStatus_t *pduStatus;
					uint16_t packetDataSize;
					pduStatus=(DPDU_TmPduStatus_t*)PUS_GetTmDataPointer(&packetDataSize,packetBuffer,packet->primaryHeader.dataLength);
					printf("pdu status telemetry:\n");
					//float32_t batteryLevel;
					printf("\t batteryLevel: %f \n",pduStatus->batteryLevel);
					//uint8_t ch1isOn;
					printf("\t ch1: %d %f v %f ma \n",pduStatus->ch1isOn, pduStatus->ch1v, pduStatus->ch1ma);
					//float32_t ch1v;
					//float32_t ch1ma;
					//uint8_t ch2isOn;
					printf("\t ch1: %d %f v %f ma \n",pduStatus->ch2isOn, pduStatus->ch2v, pduStatus->ch2ma);
					//float32_t ch2v;
					//float32_t ch2ma;
					//uint8_t ch3isOn;
					printf("\t ch3: %d %f v %f ma \n",pduStatus->ch3isOn, pduStatus->ch3v, pduStatus->ch3ma);
					//float32_t ch3v;
					//float32_t ch3ma;
					//uint8_t ch4isOn;
					printf("\t ch4: %d %f v %f ma \n",pduStatus->ch4isOn, pduStatus->ch4v, pduStatus->ch4ma);
					//float32_t ch4v;
					//float32_t ch4ma;

				}
				else
				{
					printf("warning: received unknown telemetry\n");
				}

			}
			else
			{
				printf("warning: received invalid telemetry\n");
			}
		}

		//wait
		ABOS_Sleep(MAIN_INFINITE_CYCLE_PERIOD_MS);
		upTime++;
		upTimeSub++;
		if (upTimeSub==30) upTimeSub=0;

	}
	//wait for all tasks to stop hopefully
	ABOS_Sleep(1000);
	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





