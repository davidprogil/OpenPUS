
/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <ABOS_Osal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* application includes--------------------------------------------------------*/
#include <CORE_Maestro.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
#define MAIN_INFINITE_CYCLE_PERIOD_MS (1000)


/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
CMAS_Maestro_t maestro;
ABOS_Osal_t osal;
uint16_t sequenceCount=0;
/* local prototypes -----------------------------------------------------------*/
/* none */


/* public functions -----------------------------------------------------------*/
int main(int argc, char *argv[])
{
	printf("SERVER\n");

	//road map:
	// x PUS data model
	// x client creates ping
	// x - print PUS TC
	// x print PUS TM
	// x server responds
	// x - payloadApp
	// 	x - simulate pdu
	//  x - handle on/off requests
	//  x - handle status requests
	//  x - client prints status requests
	// x - fix TODOs
	// x - document
	// - publish
	// - service 1
	//		- tm 1,1 - suc acceptance verification report
	//		- tm 1,2 - failed acceptance verification report
	//		- tm 1,7 - suc completition of execution verification report
	//		- tm 1,8 - failed completion of execution verification report
	// - packet encoders
	// - packet decoders
	// - application tutorial
	// - publish
	// - packets data model
	// - issue code generation
	// - service 17
	// - publish
	// - service 3
	// - publish
	// - service 5
	// - publish
	// - sample payload
	// - publish
	// - documentation

	//hardware initialization
	//not applicable in standard linux pc

	//checks
	printf("size of CCSDS_PrimaryHeader_t: %ld\n",sizeof(CCSDS_PrimaryHeader_t));

	//library initializations
	//NA

	//abstraction initialization
	ABOS_Init(&osal);

	//Maestro Initialization and wait
	CMAS_Init(&maestro);
	ABOS_Sleep(100);

	//maestro start
	CMAS_Start(&maestro);

	//other starts
	//NA

	//Infinite Cycle
	while (maestro.isRunAgain==M_TRUE)
	{
		//wait
		ABOS_Sleep(MAIN_INFINITE_CYCLE_PERIOD_MS);
	}
	//wait for all tasks to stop hopefully
	ABOS_Sleep(1000);
	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





