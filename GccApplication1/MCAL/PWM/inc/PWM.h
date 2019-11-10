/*
 * PWM.h
 * Description : This file is used to control the PWM in the MCU
 * Created: 11/10/2019 3:27:00 PM
 *  Author: Ammar Shahin
 */ 

#ifndef PWM_H_
#define PWM_H_


/************************************************************************/
/*                        Functions Prototypes                          */
/************************************************************************/
/**
 * Function :  PWM_PhaseCorrect
 * Description: PWM_PhaseCorrect is a function to initiate a PWM on a GPIO pin OC1 
 * @param dutyCycle the duty cycle of the PWM in percentage
 * @param freq the frequency of the PWM in Hz
 */
void PWM_Init( uint8 ch_no);

/**
 * Function :  PWM_PhaseCorrect
 * Description: PWM_PhaseCorrect is a function to initiate a PWM on a GPIO pin OC1 
 * @param dutyCycle the duty cycle of the PWM in percentage
 * @param freq the frequency of the PWM in Hz
 */
void PWM_PhaseCorrect( uint8 dutycycle , uint16 freq);

#endif /* PWM_H_ */