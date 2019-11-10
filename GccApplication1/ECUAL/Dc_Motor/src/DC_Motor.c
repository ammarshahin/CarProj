/*
 * DC_Motor.c
 * Description : This file is used to control the motor channels.
 * Created: 11/5/2019 1:06:51 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*				              Files Includes                            */
/************************************************************************/
#include "Typedefs.h"
#include "Gpio.h"
#include "Timers.h"
#include "PWM.h"
#include "DC_Motor_cfg.h"
#include "DC_Motor.h"


/************************************************************************/
/*				          Data Types and Defines                        */
/************************************************************************/
#define MOTOR_FREQUENCY_IN_HZ 20
#define DEFAULT_SPEED    50

/**
 * Function : DC_Motor_Init
 * Description : This function is used to initialize the DC motor channels
 * @pram  Channel  : is the channel that the user want to initialize [DC_MOTOR_CHANNEL_0 or DC_MOTOR_CHANNEL_1]
 * Return : the function Returns nothing
 */
void DC_Motor_Init(uint8 Channel)
{
	//Timers_timer1_Init(T1_PWM_PhaseCorrect_ICR1_MODE,T1_OC1A_CLEAR,T1_PRESCALER_1024,0,0,0,0,T1_POLLING);
	//Timers_Init(&timer1_cfg_s);
	PWM_Init(TIMER1);
	switch(Channel)
	{
		case DC_MOTOR_CHANNEL_0 : 
					/* Initiate the Motor pin Direction */
					Gpio_PinDirection(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_1,SET_OUT);
					Gpio_PinDirection(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_2,SET_OUT);
	
					/* Initiate the Motor pin  */
					Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_1,LOW);
					Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_2,LOW);
		break;
		case DC_MOTOR_CHANNEL_1 : 
					/* Initiate the Motor pin Direction */
					Gpio_PinDirection(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_1,SET_OUT);
					Gpio_PinDirection(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_2,SET_OUT);
		
					/* Initiate the Motor pin  */
					Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_1,LOW);
					Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_2,LOW);
		break;
		default:
		break;
	}
}

/**
 * Function : DC_Motor_Set_Speed
 * Description : This function is used to set the speed of the motor
 * @pram  Speed : Set the speed of the motor to this much
 * Return : the function Returns uint8 to describe the status of the speed setting (OK Or Not_OK)
 */
uint8 DC_Motor_Set_Speed(uint8 Speed)
{
	if(Speed <= 100)
	{
		PWM_PhaseCorrect(Speed,MOTOR_FREQUENCY_IN_HZ);
		return OK;
	}
	else
	{
		return NOT_OK;
	}
}

/**
 * Function : DC_Motor_Set_Direction
 * Description : This function is used to set the Direction of the motor Channel.
 * @pram  Channel : Set the Channel of the motor.
 * @pram  Direction : Set the Direction of the motor Channel.
 * Return : the function Returns uint8 to describe the status of the Direction setting (OK Or Not_OK).
 */
uint8 DC_Motor_Set_Direction(uint8 Channel , uint8 Direction)
{
	switch(Channel)
	{
		case DC_MOTOR_CHANNEL_0 :
			switch(Direction)
			{
				case DC_MOTOR_FORWARD :
						/* Set the Motor pin */
						Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_1,HIGH);
						Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_2,LOW);
				break;
				case DC_MOTOR_BACK : 
						/* Set the Motor pin */
						Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_1,LOW);
						Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_2,HIGH);
				break;
				default:
				break;
			}
		break;
		case DC_MOTOR_CHANNEL_1 :
			switch(Direction)
			{
				case DC_MOTOR_FORWARD :
					/* Set the Motor pin */
					Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_1,HIGH);
					Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_2,LOW);
				break;
				case DC_MOTOR_BACK :
					/* Set the Motor pin */
					Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_1,LOW);
					Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_2,HIGH);
				break;
				default:
				break;
		}
		break;
	}
	return OK;
}

/**
 * Function : DC_Motor_Stop
 * Description : This function is used to Stop the motor Channel.
 * @pram  Channel : Set the Channel of the motor.
 * Return : the function Returns Nothing.
 */
void DC_Motor_Stop(uint8 Channel)
{
	switch(Channel)
	{
		case DC_MOTOR_CHANNEL_0 : 
		Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_1,LOW);
		Gpio_PinWrite(DC_MOTOR_CHANNEL_0_PORT,DC_MOTOR_CHANNEL_0_PIN_2,LOW);
		break;
		case DC_MOTOR_CHANNEL_1 : 
		Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_1,LOW);
		Gpio_PinWrite(DC_MOTOR_CHANNEL_1_PORT,DC_MOTOR_CHANNEL_1_PIN_2,LOW);
		break;
		default:
		break;	
	}		
}

/**
 * Function : DC_Motor_Start
 * Description : This function is used to Start the motor Channel.
 * @pram  Channel : Set the Channel of the motor.
 * Return : the function Returns Nothing.
 */
void DC_Motor_Start(uint8 Channel)
{
	DC_Motor_Set_Speed(DEFAULT_SPEED);
	Timers_timer1_Start();
	DC_Motor_Set_Direction(Channel,DC_MOTOR_FORWARD); // Move Forward as A default Direction
}