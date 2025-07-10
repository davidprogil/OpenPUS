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
#include <configuration.h>
#include <LIB_PusUtils.h>

/* component includes----------------------------------------------------------*/
#include <SBCC_CcsdsUtils.h>
#include <DEV_Pdu.h>

/* local macros ---------------------------------------------------------------*/
#define PDU_SIM_BATT_DEFAULT (14.1)
#define PDU_SIM_CH1_V_DEFAULT (12.0)
#define PDU_SIM_CH2_V_DEFAULT (5.0)
#define PDU_SIM_CH3_V_DEFAULT (5.3)
#define PDU_SIM_CH4_V_DEFAULT (3.3)
#define PDU_SIM_CH1_MA_DEFAULT (200.0)
#define PDU_SIM_CH2_MA_DEFAULT (300.0)
#define PDU_SIM_CH3_MA_DEFAULT (400.0)
#define PDU_SIM_CH4_MA_DEFAULT (500.0)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
float32_t channelsVoltagesDefault[DPDU_CHANNELS_NO] =
{
		PDU_SIM_CH1_V_DEFAULT,
		PDU_SIM_CH2_V_DEFAULT,
		PDU_SIM_CH3_V_DEFAULT,
		PDU_SIM_CH4_V_DEFAULT
};
float32_t channelsCurrentsDefault[DPDU_CHANNELS_NO] =
{
		PDU_SIM_CH1_MA_DEFAULT,
		PDU_SIM_CH2_MA_DEFAULT,
		PDU_SIM_CH3_MA_DEFAULT,
		PDU_SIM_CH4_MA_DEFAULT
};

/* local prototypes -----------------------------------------------------------*/
void DPDU_CreateTmAndSend(DPDU_Pdu_t *this,uint8_t *data,uint16_t dataNb,uint16_t destinationId);

/* public functions -----------------------------------------------------------*/
void DPDU_Init(DPDU_Pdu_t *this,uint16_t *pidMsgCounter_p)
{
	printf("DPDU_Init\n");
	memset(this,0,sizeof(DPDU_Pdu_t));

	//battery
	this->batteryLevel=0.0;
	//channels
	for (uint8_t channelIx=0;channelIx<DPDU_CHANNELS_NO;channelIx++)
	{
		this->channels[channelIx].isOn=M_FALSE;
		this->channels[channelIx].voltage_v=0.0;
		this->channels[channelIx].current_mA=0.0;
	}
	//status
	this->pidMsgCounter=pidMsgCounter_p;
}

void DPDU_Execute(DPDU_Pdu_t *this)
{
	printf("DPDU_Execute\n");

	//simulation - apply defaults and errors TODO

	this->batteryLevel=PDU_SIM_BATT_DEFAULT;
	for (uint8_t channelIx=0;channelIx<DPDU_CHANNELS_NO;channelIx++)
	{
		if (this->channels[channelIx].isOn==M_TRUE)
		{
			this->channels[channelIx].voltage_v=channelsVoltagesDefault[channelIx];
			this->channels[channelIx].current_mA=channelsCurrentsDefault[channelIx];
		}
		else
		{
			this->channels[channelIx].voltage_v=0.0;
			this->channels[channelIx].current_mA=0.0;
		}
	}

}

void DPDU_HandleTc(DPDU_Pdu_t *this,uint8_t *packetBuffer,uint16_t packetSize)
{
	printf("debug DPDU_HandleTc\n");

	PUS_TcSecondaryHeader_t *tcSecondaryHeader=PUS_GetTcHeader(packetBuffer, packetSize);

	//1 - on off channel
	if (tcSecondaryHeader->serviceSubType==DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID)
	{
		printf("DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID\n");
		uint16_t dataSize;
		DPDU_TcChannelOnOff_t *tcChannelOnOffData;
		tcChannelOnOffData=(DPDU_TcChannelOnOff_t*)PUS_GetTcDataPointer(&dataSize,packetBuffer,packetSize-sizeof(CCSDS_PrimaryHeader_t));
		if (dataSize!=sizeof(DPDU_TcChannelOnOff_t))
		{
			printf("warning: DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID data size mismatch %d %ld\n",dataSize,sizeof(DPDU_TcChannelOnOff_t));
		}
		else
		{
			printf("info: DPDU_HandleTc Switch %d to %d\n",tcChannelOnOffData->channelNo,tcChannelOnOffData->isOn);
			this->channels[tcChannelOnOffData->channelNo].isOn=tcChannelOnOffData->isOn;
		}
	}
	//2 - get channel statuses
	else if (tcSecondaryHeader->serviceSubType==DPDU_PUS_CHANNELSTATUS_TC_SUBSERVICE_ID)
	{
		printf("DPDU_PUS_CHANNELSTATUS_TC_SUBSERVICE_ID\n");
		DPDU_TmPduStatus_t tmPduStatus;
		tmPduStatus.batteryLevel=this->batteryLevel;
		tmPduStatus.ch1isOn=this->channels[0].isOn;		tmPduStatus.ch1v=this->channels[0].voltage_v;		tmPduStatus.ch1ma=this->channels[0].current_mA;
		tmPduStatus.ch2isOn=this->channels[1].isOn;		tmPduStatus.ch2v=this->channels[1].voltage_v;		tmPduStatus.ch2ma=this->channels[1].current_mA;
		tmPduStatus.ch3isOn=this->channels[2].isOn;		tmPduStatus.ch3v=this->channels[2].voltage_v;		tmPduStatus.ch3ma=this->channels[2].current_mA;
		tmPduStatus.ch4isOn=this->channels[3].isOn;		tmPduStatus.ch4v=this->channels[3].voltage_v;		tmPduStatus.ch4ma=this->channels[3].current_mA;
		DPDU_CreateTmAndSend(this,(uint8_t*)&tmPduStatus,sizeof(DPDU_TmPduStatus_t),tcSecondaryHeader->sourceId);
	}
	else
	{
		//TODO
		printf("warning: DPDU_HandleTc unknown subservice\n");
	}
}

/* local functions ------------------------------------------------------------*/
void DPDU_CreateTmAndSend(DPDU_Pdu_t *this,uint8_t *data,uint16_t dataNb,uint16_t destinationId)
{
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];  // Temporary buffer for one packet
	bool_t isError=M_FALSE;

	//printf("debug %d %d %d,\n",data[0],data[1],dataNb);
	//create tm and data field
	if (isError!=M_TRUE)
	{
		isError=PUS_CreateTmDataField(
				&packetBuffer[CCSDS_PACKET_START_DATA],sizeof(packetBuffer)-sizeof(CCSDS_PrimaryHeader_t), //target and size
				data,dataNb, //data
				17, 2, //service, subservice
				this->messageType17s2Counter,
				destinationId);
	}

	if (isError!=M_TRUE)
	{
		isError=CCSDS_CreatePacket(
				packetBuffer, //target
				sizeof(packetBuffer), //targetNb
				M_FALSE, //isTc
				M_TRUE, //hasSecondaryHeader,
				DEV_APID,//apid,
				*this->pidMsgCounter,
				dataNb+sizeof(PUS_TmSecondaryHeader_t),
				&packetBuffer[CCSDS_PACKET_START_DATA]);
	}

	//Send
	if (isError!=M_TRUE)
	{
		//CCSDS_PrintPacket(packet);
		PUS_PrintTm(packetBuffer, sizeof(packetBuffer));
		//print TC
		SBRO_Publish(this->router, packetBuffer, CCSDS_PACKET_TOTAL_LENGHT((CCSDS_Packet_t*)packetBuffer));//temp
		this->messageType17s2Counter++;
		*this->pidMsgCounter++;
	}
}

/* end */
