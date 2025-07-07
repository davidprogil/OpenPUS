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
#include <SBCC_CcsdsUtils.h>

/* component includes----------------------------------------------------------*/
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
/* none */

/* public functions -----------------------------------------------------------*/
void DPDU_Init(DPDU_Pdu_t *this)
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

void DPDU_HandleTc(uint8_t *packetBuffer,uint16_t packetSize)
{
	printf("debug DPDU_HandleTc\n");

	PUS_TcSecondaryHeader_t *tcSecondaryHeader=PUS_GetTcHeader(packetBuffer, packetSize);

	//1 - on off channel
	if (tcSecondaryHeader->serviceSubType==DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID)
	{
		//TODO
	}
	//2 - get channel statuses
	else if (tcSecondaryHeader->serviceSubType==DPDU_PUS_CHANNELSTATUS_TC_SUBSERVICE_ID)
	{
		//TODO
	}
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
