/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef LIB_PusUtils_H
#define LIB_PusUtils_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define PUS_VERSION_NO (1)
#define PUS_IS_TC_HEADER_SIZE(x) (CCSDS_PACKET_DATA_LENGHT(x)>=sizeof(PUS_TcSecondaryHeader_t)?M_TRUE:M_FALSE)

/* types------------------------------------------------------------------------*/
typedef struct __attribute__((packed)) _PUS_TmSecondaryHeader_t_
{
 uint8_t versionTmPus:4; //should be = 1 for ECSS-E-70-41A
 uint8_t scTimeReferenceStatus:4; //0 when not supported NOTS
 uint8_t serviceType;
 uint8_t serviceSubType;
 uint16_t messageTypeCounter;//per pid, per type/subtype, or 0 if not supported NOTS
 uint16_t destinationId;
 uint32_t time;
 uint8_t spare0; //total size of header needs to be of a integer word size
}PUS_TmSecondaryHeader_t;

typedef struct __attribute__((packed)) _PUS_TcSecondaryHeader_t_
{
	uint8_t versionTcPus:4; //should be = 1 for ECSS-E-70-41A
	uint8_t acknowledgementFlags:4; //NOTS //bit 3 = successful acknowledgment //bit 2 = successful start of execution //bit 1 = successful progress of execution // successful end of execution
	uint8_t serviceType;
	uint8_t serviceSubType;
	uint16_t sourceId;
	uint8_t spare0; //total size of header needs to be of a integer word size
}PUS_TcSecondaryHeader_t;


/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
bool_t PUS_CreateTcDataField(uint8_t *target,uint16_t targetMaxNb,uint8_t *data, uint16_t dataNb,bool_t isWantedAcknowledgment, bool_t isWantedExecutionResult, uint8_t serviceType, uint8_t serviceSubType, uint16_t sourceId);

void PUS_CreateTcHeader(PUS_TcSecondaryHeader_t *target, bool_t isWantedAcknowledgment, bool_t isWantedExecutionResult, uint8_t serviceType, uint8_t serviceSubType, uint16_t sourceId);

PUS_TcSecondaryHeader_t *PUS_GetTcHeader(uint8_t *packet,uint16_t packetNb);



bool_t PUS_JoinTcHeaderAndData(uint8_t *target,uint16_t targetMaxNb,PUS_TcSecondaryHeader_t *header,uint8_t *data, uint16_t dataNb);
bool_t PUS_JoinTmHeaderAndData(uint8_t *target,uint16_t targetMaxNb,PUS_TmSecondaryHeader_t *header,uint8_t *data, uint16_t dataNb);

void PUS_PrintTcHeader(PUS_TcSecondaryHeader_t *target);
void PUS_PrintTc(uint8_t *packet, uint16_t packetNb);

/* end */
#endif /* LIB_PusUtils_H */

