/*
 * Ultrasonic.c
 *
 * Created: 11/5/2019 2:20:05 PM
 *  Author: Ammar Shahin
 */ 
#include "Gpio.h"
#include "Sw_ICU.h"
#include "Ultrasonic_Cfg.h"
#include "Ultrasonic.h"
#include "SwDelay.h"

/************************************************************************/
/*				        Defines and Data Types                          */
/************************************************************************/
#define NANOSECONDS_FACTOR 1000000000.0
#define SOUNDSPEED_FACTOR  (34300/2)

/************************************************************************/
/*				          Functions Prototype                           */
/************************************************************************/

/**
 * Function : Ultrasonic_Init
 * Description : This function is used to initialize the UltraSonic module.
 * Return : the function Returns nothing
 */

void Ultrasonic_Init(void)
{
	SwICU_Init();
	Gpio_PinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,SET_OUT);
	Gpio_PinDirection(ULTRASONIC_ECHO_PORT,ULTRASONIC_ECHO_PIN,SET_IN);
}


/**
 * Function : Ultrasonic_Trigger
 * Description : This function is used to Trigger the UltraSonic module by sending a High
 *	    for at least a 10 micro seconds and then pull it low.
 * Return : the function Returns nothing
 */
void Ultrasonic_Trigger(void)
{
	Gpio_PinWrite(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,HIGH);
	SwDelay_us(10);
	Gpio_PinWrite(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOW);
}


/**
 * Function : Ultrasonic_CalculateDistance
 * Description : This function is used to Calculate the Distance by receiving the Ton from the ICU Unit
 *                           and then returning the Distance.
 * Return : the function Returns the Distance in centimeters.
 */
uint32 Ultrasonic_CalculateDistance(void)
{
	uint32 theDistance;
	uint64 raising_time_ns;
	SwICU_Read(&raising_time_ns);
	theDistance = ( ( raising_time_ns / NANOSECONDS_FACTOR ) * SOUNDSPEED_FACTOR );
	return theDistance;	
}