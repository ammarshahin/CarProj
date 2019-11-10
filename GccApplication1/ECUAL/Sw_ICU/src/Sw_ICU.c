/*
 * SwICU.c
 *
 * Created: 11/5/2019 2:44:26 PM
 *  Author: Ammar Shahin
 */ 


/************************************************************************/
/*				           Files Includes                               */
/************************************************************************/
#include "Typedefs.h"
#include "Timers.h"
#include "Gpio.h"
#include "Interrupts.h"

/************************************************************************/
/*				          Defines and macros                            */
/************************************************************************/
#define REGISTER_BIT_MAXVALUE 256
#define F_CPU_PRESCALLER_FACTOR 1000000000

/************************************************************************/
/*				         Static Global Variables                        */
/************************************************************************/
static volatile uint8  Falling_Risin_Flag = 0;
static volatile uint8  numOfOverflows = 0;
static volatile uint64 raising_time_ns = 0;

/************************************************************************/
/*				         Functions Definitions                         */
/************************************************************************/
/*
 * Description: This function initializes the ICU module 
 * Parameter: void
 * Return : The status of the function [OK or NOT_OK]
 */
uint8 SwICU_Init(void)
{
	Interrupts_ExtInt_Init(INT0,ANY_CHANGE);
	//Timers_timer2_Init(T2_NORMAL_MODE,T2_OC0_DIS,T2_PRESCALER_1,0,0,T2_INTERRUPT_NORMAL);
	Timers_Init(&timer2_cfg_s);
	Interrupts_On();
	return OK;
}

/*
 * Description: This function Reads all Timer 0 counts (Including overflow ) 
 * Parameter: 
				Output :  Reading_value >> used to return the value of the value Ton 
 * Return : The status of the function [OK or NOT_OK]
 */
uint8 SwICU_Read(uint64* Reading_value)
{
	*Reading_value = raising_time_ns;
	return OK;
}

/*
 * Description: This function enables the ICU functionality 
 * Parameter: void
 * Return : The status of the function [OK or NOT_OK]
 */
uint8 SwICU_Enable(void)
{
	Interrupts_On();
	return OK;
}

/*
 * Description: This function disables the ICU functionality
 * Parameter: void 
 * Return : The status of the function [OK or NOT_OK]
 */
uint8 SwICU_Disable(void)
{
	Timers_timer2_Stop();
	return OK;
}

/*
 * Description: This is an ISR that executes when an External interrupt occurs.
 * Parameter: void 
 * Return : void
 */
ISR_T(INT0_vect)
{
	if(Falling_Risin_Flag == 0)
	{
		Timers_timer2_Set(0);
		Timers_timer2_Start();
		numOfOverflows = 0;
		Falling_Risin_Flag = 1;
	}
	else if(Falling_Risin_Flag == 1)
	{
		raising_time_ns =  ( ( (numOfOverflows * REGISTER_BIT_MAXVALUE) + Timers_timer2_Read()) * ( F_CPU_PRESCALLER_FACTOR /F_CPU ) );
		Timers_timer1_Stop();
		numOfOverflows = 0;
		Timers_timer2_Set(0);
		Falling_Risin_Flag = 0;
	}
}

/*
 * Description: This is an ISR that executes when the timer 2 overflows.
 * Parameter: void 
 * Return : void
 */
ISR_T(TIMER2_OVF_vect)
{
	numOfOverflows++;
}