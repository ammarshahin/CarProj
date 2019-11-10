/*
 * softwareDelay.c
 *
 * Created: 10/21/2019 9:16:41 PM
 *  Author: Ammar Shahin 
 */ 

/************************************************************************/
/*                             Includes                                 */
/************************************************************************/
#include "MCU_Frequency.h"
#include "Typedefs.h"
#include "SwDelay.h"

/************************************************************************/
/*                       Defines and Macros                             */
/************************************************************************/
/* 9 is a factor that we find by try and error to simulate 
 *   how many cycles before counter is decremented.          */
#define CYCLE_MELLI_DELAY_FACTOR 9
#define CYCLE_MICRO_DELAY_FACTOR 13

#define SECONDS_TO_NANOSECONSD_FACTOR  1000000000
#define SECONDS_TO_MICROSECONSD_FACTOR 1000000
#define SECONDS_TO_MILLISECONSD_FACTOR 1000
#define DUTY_CYCLE_PERCENTAGE_FACTOR   100

/*===========================SW_Delay Functions===============================*/
/**
 * Description: Function to make a software Delay in the Melli seconds 
 * @param NoOfMilleSeconds the number of  Melli seconds to delay
 */
void SwDelay_ms(uint32 NoOfMilleSeconds)
{
	sint32 counter;
	counter = NoOfMilleSeconds * (F_CPU / SECONDS_TO_MILLISECONSD_FACTOR);
	while(counter > FALSE)
	{
			counter =  counter - CYCLE_MELLI_DELAY_FACTOR;
	}
}


/**
 * Description: Function to make a software Delay in the Micro Seconds. 
 * @param NoOfMicroeSeconds the number of Micro Seconds to delay
 */
void SwDelay_us(uint32 NoOfMicroeSeconds)
{
	sint32 counter;
	counter = NoOfMicroeSeconds * (F_CPU / SECONDS_TO_MICROSECONSD_FACTOR);
	while(counter > FALSE)
	{
			counter =  counter - CYCLE_MICRO_DELAY_FACTOR;
	}
}