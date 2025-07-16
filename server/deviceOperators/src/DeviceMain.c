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
#include <DEV_DeviceMain.h>

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
void DEV_Execute(DEV_DeviceMain_t *this);

// Function to handle the TCs
void DEV_HandleTcs(DEV_DeviceMain_t *this);

// Thread definition macro for DEV execution
ABOS_DEFINE_TASK(DEV_ExecuteThread);

// Function called when a packet is received for this application
void DEV_DataHandler(void *handlingObject, uint8_t *inData,uint32_t inDataNb);

/* public functions -----------------------------------------------------------*/
// Initializes the DEV application
void DEV_Init(DEV_DeviceMain_t *this, SBRO_Router_t *router,
		ABOS_sem_handle_t *semaphoreStart, ABOS_sem_handle_t *semaphoreEnd)
{
	printf("DEV_Init\n");

	// Store semaphore handles
	this->semaphoreStart = semaphoreStart;
	this->semaphoreEnd = semaphoreEnd;

	// Initialize application status
	this->sentPacketsNo = 0;
	this->receivedPacketsNo = 0;
	this->rejectedPacketsNo = 0;
	this->isRunAgain = M_TRUE;

	// Initialize packet queue
	LFQ_Init(&this->packetQueue, this->packetQueueBuffer, DEV_QUEUE_NB);
	ABOS_MutexCreate(&this->packetQueueMutex);
	this->router = router;

	//initialize sub-classes
	DPDU_Init(&this->pdu,&this->sentPacketsNo,router);

	// Subscribe to receive packets for this application's APID
	SBRO_Subscribe(this->router, DEV_APID, this, *DEV_DataHandler);

	// Create and start execution thread
	ABOS_ThreadCreate(
			DEV_ExecuteThread,              // Thread function
			(int8_t *)"DEV_EXEC",           // Thread name
			DEV_THREAD_STACK_SIZE,          // Stack size
			(void *)this,                    // Thread argument
			DEV_THREAD_PRIORITY,            // Priority
			&this->threadHandleExecute       // Thread handle
	);
}

// Stops the application by exiting the execution loop
void DEV_Stop(DEV_DeviceMain_t *this)
{
	this->isRunAgain = M_FALSE;
}


/* local functions -----------------------------------------------------------*/
void DEV_HandleTcs(DEV_DeviceMain_t *this)
{
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];  // Temporary buffer for one packet
	uint16_t packetSize;
	CCSDS_Packet_t *packet;
	PUS_TcSecondaryHeader_t *tcSecondaryHeader;
	//TODO remove uint8_t *packetData;
	uint16_t processedTcNo = 0;


	//printf("DEV_Execute\n");

	// Process packets in the queue (up to a max number)
	while ((LFQ_QueueGetWithMutex(&this->packetQueue, &this->packetQueueMutex, packetBuffer, &packetSize))  &&
			(processedTcNo < DEV_TC_MAX_NB))
	{
		printf("DEV_DataHandler received packet:\n");

		packet = (CCSDS_Packet_t *)packetBuffer;
		CCSDS_PrintPacket(packet);

		//if pus packet
		if (PUS_IsPacketSizeValid(packetBuffer, packetSize))
		{
			//if TC
			if (PUS_IsPusPusTc(packetBuffer, packetSize))
			{
				tcSecondaryHeader=PUS_GetTcHeader(packetBuffer, packetSize);
				//if for PDU
				if (tcSecondaryHeader->serviceType==DPDU_PUS_SERVICE_ID)
				{
					DPDU_HandleTc(&this->pdu,packetBuffer, packetSize);
				}
			}
		}


		processedTcNo++;
	}
}

// Main execution function for DEV
// Processes all telecommands in the queue and sends back a response
void DEV_Execute(DEV_DeviceMain_t *this)
{
	DEV_HandleTcs(this);

	DPDU_Execute(&this->pdu);
}

// Called when a packet for DEV is received by the router
void DEV_DataHandler(void *handlingObject, uint8_t *inData, uint32_t inDataNb)
{
	DEV_DeviceMain_t *this = (DEV_DeviceMain_t *)handlingObject;

	// Lock the queue to safely enqueue the incoming packet
	ABOS_MutexLock(&this->packetQueueMutex, ABOS_TASK_MAX_DELAY);

	// Add received packet to the processing queue
	if (LFQ_QueueAdd(&this->packetQueue, inData, inDataNb) == M_TRUE)
	{
		// Log if packet was rejected (queue full)
		printf("warning: DEV_DataHandler packet rejected\n");
		this->rejectedPacketsNo++;
	}
	//unlock the queue
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

// Execution thread for DEV
// Waits for the start semaphore, processes packets, then signals completion
ABOS_DEFINE_TASK(DEV_ExecuteThread)
{
	DEV_DeviceMain_t *this = (DEV_DeviceMain_t *)param;

	while (this->isRunAgain == M_TRUE)
	{
		// Wait until orchestrator gives go-ahead
		ABOS_SemaphoreWait(this->semaphoreStart, ABOS_TASK_MAX_DELAY);

		// Run one cycle of the application
		DEV_Execute(this);

		// Notify orchestrator that processing is complete
		ABOS_SemaphorePost(this->semaphoreEnd);
	}

	return ABOS_TASK_RETURN;
}



/* end */
