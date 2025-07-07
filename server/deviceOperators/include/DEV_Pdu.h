/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef DPDU_Pdu_H
#define DPDU_Pdu_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define DPDU_PUS_SERVICE_ID (140)
#define DPDU_PUS_CHANNELONOFF_TC_SUBSERVICE_ID (1)
#define DPDU_PUS_CHANNELSTATUS_TC_SUBSERVICE_ID (2)
#define DPDU_PUS_CHANNELSTATUS_TM_SUBSERVICE_ID (3)
#define DPDU_CHANNELS_NO (4)

/* types------------------------------------------------------------------------*/
typedef struct _DPDU_Channel_t_
{
	bool_t isOn;
	float32_t voltage_v;
	float32_t current_mA;
}DPDU_Channel_t;

typedef struct _DPDU_Pdu_t_
{
	DPDU_Channel_t channels[DPDU_CHANNELS_NO];
	float32_t batteryLevel;
}DPDU_Pdu_t;

typedef struct _DPDU_TcChannelOnOff_t_
{
	uint8_t channelNo;
	uint8_t isOn;
}DPDU_TcChannelOnOff_t;

typedef struct _DPDU_TmChannel_t_
{
	uint32_t batteryLevel;
	uint8_t ch1isOn;
	uint8_t ch1v;
	uint8_t ch1ma;
	uint8_t ch2isOn;
	uint8_t ch2v;
	uint8_t ch2ma;
	uint8_t ch3isOn;
	uint8_t ch3v;
	uint8_t ch3ma;
	uint8_t ch4isOn;
	uint8_t ch4v;
	uint8_t ch4ma;
}DPDU_TmChannel_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void DPDU_Init(DPDU_Pdu_t *this);
void DPDU_Execute(DPDU_Pdu_t *this);

void DPDU_HandleTc(uint8_t *packetBuffer,uint16_t packetSize);


/* end */
#endif /* DPDU_Pdu_H */

