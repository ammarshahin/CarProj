/*
 * PWM.c
 * Description : This file is used to control the PWM in the MCU
 * Created: 11/10/2019 3:27:00 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "MCU_Frequency.h"
#include "Typedefs.h"
#include "Timers.h"

/************************************************************************/
/*                        Functions Definitions                         */
/************************************************************************/
/**
 * Function :  PWM_PhaseCorrect
 * Description: PWM_PhaseCorrect is a function to initiate a PWM on a GPIO pin OC1 
 * @param dutyCycle the duty cycle of the PWM in percentage
 * @param freq the frequency of the PWM in Hz
 */

void PWM_Init( uint8 ch_no){
	switch(ch_no)
	{
		case TIMER0:
		Timers_Init(&timer0_cfg_s);
		break;
		case TIMER1:
		Timers_Init(&timer1_cfg_s);
		break;
		case TIMER2:
		Timers_Init(&timer2_cfg_s);
		break;
	}
}

/**
 * Function :  PWM_PhaseCorrect
 * Description: PWM_PhaseCorrect is a function to initiate a PWM on a GPIO pin OC1 
 * @param dutyCycle the duty cycle of the PWM in percentage
 * @param freq the frequency of the PWM in Hz
 */

void PWM_PhaseCorrect( uint8 dutycycle , uint16 freq){
	uint16 TOP_Value;
	uint16 Compare_Value;
	TOP_Value = F_CPU / ( 2 * freq * Gv_PrescallerTimer1_AbsoluteValue);
	Compare_Value = (TOP_Value*dutycycle)/DUTY_CYCLE_PERCENTAGE_FACTOR;
	ICR1L  = (uint8)(TOP_Value);
	ICR1H  = (uint8)(TOP_Value>>8);
	OCR1AL = (uint8)(Compare_Value);
	OCR1AH = (uint8)(Compare_Value>>8);
}