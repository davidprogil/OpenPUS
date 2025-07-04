/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <LIB_PusUtils.h>

/* component includes----------------------------------------------------------*/
#include <APP1_App1Main.h>

/* local macros ---------------------------------------------------------------*/
/* none */


/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
// Main execution function for processing
void APP1_Execute(APP1_App1Main_t *this);

// TC Processing
void APP1_ExecuteTc(APP1_App1Main_t *this);

// Thread definition macro for APP1 execution
ABOS_DEFINE_TASK(APP1_ExecuteThread);

// Function called when a packet is received for this application
void APP1_DataHandler(void *handlingObject, uint8_t *inData,uint32_t inDataNb);

// Function that creates a ping response
void APP1_CreateTm17s2AndSend(APP1_App1Main_t *this,uint8_t *data,uint16_t dataNb,uint16_t destinationId);

/* public functions -----------------------------------------------------------*/
// Initializes the APP1 application
void APP1_Init(APP1_App1Main_t *this, SBRO_Router_t *router,
		ABOS_sem_handle_t *semaphoreStart, ABOS_sem_handle_t *semaphoreEnd)
{
	printf("APP1_Init\n");

	// Store semaphore handles
	this->semaphoreStart = semaphoreStart;
	this->semaphoreEnd = semaphoreEnd;

	// Initialize application status
	this->sentPacketsNo = 0;
	this->receivedPacketsNo = 0;
	this->rejectedPacketsNo = 0;
	this->isRunAgain = M_TRUE;
	this->messageType17s2Counter = 0;
	this->thisPidSequenceCount=0;
	// Initialize packet queue
	LFQ_Init(&this->packetQueue, this->packetQueueBuffer, APP1_QUEUE_NB);
	ABOS_MutexCreate(&this->packetQueueMutex);
	this->router = router;

	// Subscribe to receive packets for this application's APID
	SBRO_Subscribe(this->router, APP1_APID, this, *APP1_DataHandler);

	// Create and start execution thread
	ABOS_ThreadCreate(
			APP1_ExecuteThread,              // Thread function
			(int8_t *)"APP1_EXEC",           // Thread name
			APP1_THREAD_STACK_SIZE,          // Stack size
			(void *)this,                    // Thread argument
			APP1_THREAD_PRIORITY,            // Priority
			&this->threadHandleExecute       // Thread handle
	);
}

// Stops the application by exiting the execution loop
void APP1_Stop(APP1_App1Main_t *this)
{
	this->isRunAgain = M_FALSE;
}


/* local functions -----------------------------------------------------------*/
// Main execution function for APP1
// Processes all telecommands in the queue and sends back a response
void APP1_Execute(APP1_App1Main_t *this)
{
	//execute TCs
	APP1_ExecuteTc(this);

}

void APP1_ExecuteTc(APP1_App1Main_t *this)
{
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];  // Temporary buffer for one packet
	uint16_t packetSize;
	CCSDS_Packet_t *packet;
	uint8_t *packetData;
	uint16_t packetDataSize;
	uint8_t temp;
	uint16_t processedTcNo = 0;
	PUS_TcSecondaryHeader_t *tcHeader=NULL;
	bool_t isTherePacket;

	//printf("APP1_ExecuteTc \n");
	// Process packets in the queue (up to a max number)
	while ( (isTherePacket=LFQ_QueueGetWithMutex(&this->packetQueue, &this->packetQueueMutex, packetBuffer, &packetSize)) &&
			(processedTcNo < APP1_TC_MAX_NB))
	{
		printf("APP1_DataHandler received packet:\n");

		if (PUS_IsPacketSizeValid(packetBuffer,packetSize))
		{

			packet = (CCSDS_Packet_t *)packetBuffer;
			//TODO check that packet is valid
			//CCSDS_PrintPacket(packet);
			PUS_PrintTc(packetBuffer,packetSize);

			tcHeader=PUS_GetTcHeader(packetBuffer,packetSize);

			if (tcHeader!=NULL)
			{
				//ddebug PUS_PrintTcHeader(tcHeader);
				//check service/subservice
				if ((tcHeader->serviceType==17)&&(tcHeader->serviceSubType==1)) // ping request
				{
					//get data
					packetData=PUS_GetTcDataPointer(&packetDataSize,packetBuffer,packet->primaryHeader.dataLength);
					//switch data
					temp = packetData[1];
					packetData[1] = packetData[0];
					packetData[0] = temp;
					//printf("debug %d %d\n",packetData[0],packetData[1]);
					//create and send TM(17,2)
					APP1_CreateTm17s2AndSend(this,packetData,PUS_GET_TC_DATA_SIZE(packet),GROUND_APID);
				}
			}
		}


		processedTcNo++;
	}

}

// Called when a packet for APP1 is received by the router
void APP1_DataHandler(void *handlingObject, uint8_t *inData, uint32_t inDataNb)
{
	APP1_App1Main_t *this = (APP1_App1Main_t *)handlingObject;

	// Lock the queue to safely enqueue the incoming packet
	ABOS_MutexLock(&this->packetQueueMutex, ABOS_TASK_MAX_DELAY);

	// Add received packet to the processing queue
	if (LFQ_QueueAdd(&this->packetQueue, inData, inDataNb) == M_TRUE)
	{
		// Log if packet was rejected (queue full)
		printf("warning: APP1_DataHandler packet rejected\n");
		this->rejectedPacketsNo++;
	}
	//unlock the queue
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

// Execution thread for APP1
// Waits for the start semaphore, processes packets, then signals completion
ABOS_DEFINE_TASK(APP1_ExecuteThread)
{
	APP1_App1Main_t *this = (APP1_App1Main_t *)param;

	while (this->isRunAgain == M_TRUE)
	{
		// Wait until orchestrator gives go-ahead
		ABOS_SemaphoreWait(this->semaphoreStart, ABOS_TASK_MAX_DELAY);

		// Run one cycle of the application
		APP1_Execute(this);

		// Notify orchestrator that processing is complete
		ABOS_SemaphorePost(this->semaphoreEnd);
	}

	return ABOS_TASK_RETURN;
}

//function that creates a ping response
void APP1_CreateTm17s2AndSend(APP1_App1Main_t *this,uint8_t *data,uint16_t dataNb,uint16_t destinationId)
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
				APP1_APID,//apid,
				this->thisPidSequenceCount,
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
		this->thisPidSequenceCount++;
	}
}

/* end */
