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
#include <LIB_PusUtils.h>

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
bool_t PUS_CreateTcDataField(uint8_t *target,uint16_t targetMaxNb,uint8_t *data, uint16_t dataNb,bool_t isWantedAcknowledgment, bool_t isWantedExecutionResult, uint8_t serviceType, uint8_t serviceSubType, uint16_t sourceId)
{
	bool_t isError=M_FALSE;

	PUS_TcSecondaryHeader_t header;
	PUS_CreateTcHeader(&header,isWantedAcknowledgment,isWantedExecutionResult,serviceType,serviceSubType,sourceId);

	isError=PUS_JoinTcHeaderAndData(target,targetMaxNb,&header,data,dataNb);

	return isError;

}
void PUS_CreateTcHeader(PUS_TcSecondaryHeader_t *this, bool_t isWantedAcknowledgment, bool_t isWantedExecutionResult, uint8_t serviceType, uint8_t serviceSubType, uint16_t sourceId)
{
	memset(this,0,sizeof(PUS_TcSecondaryHeader_t));
	//uint8_t versionTcPus:4; //should be = 1 for ECSS-E-70-41A
	this->versionTcPus=PUS_VERSION_NO;
	//uint8_t acknowledgementFlags:4; //bit 3 = successful acknowledgment //bit 2 = successful start of execution //bit 1 = successful progress of execution // successful end of execution
	this->acknowledgementFlags= (this->acknowledgementFlags) | ( isWantedAcknowledgment << 3);
	this->acknowledgementFlags= (this->acknowledgementFlags) | ( isWantedExecutionResult << 0);
	//uint8_t serviceType;
	this->serviceType=serviceType;
	//uint8_t serviceSubType;
	this->serviceSubType=serviceSubType;
	//uint16_t sourceId;
	this->sourceId=sourceId;
	//uint8_t spare0; //total size of header needs to be of a integer word size
}

void PUS_PrintTcHeader(PUS_TcSecondaryHeader_t *this)
{
	printf("TC Secondary Header packet:\n");
	printf("\t versionTcPus: %d\n",this->versionTcPus);
	printf("\t acknowledgementFlags: %d\n",this->acknowledgementFlags);
	printf("\t serviceType: %d\n",this->serviceType);
	printf("\t serviceSubType: %d\n",this->serviceSubType);
	printf("\t sourceId: %d\n",this->sourceId);
}

bool_t PUS_JoinTcHeaderAndData(uint8_t *target,uint16_t targetMaxNb,PUS_TcSecondaryHeader_t *header,uint8_t *data, uint16_t dataNb)
{
	bool_t isError=M_FALSE;
	if (targetMaxNb<dataNb+sizeof(PUS_TcSecondaryHeader_t))
	{
		isError=M_TRUE;
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
	}
	else
	{
		memcpy(&target[0],header,sizeof(PUS_TmSecondaryHeader_t));
		memcpy(&target[sizeof(PUS_TmSecondaryHeader_t)],data,dataNb);
	}

	return isError;
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
