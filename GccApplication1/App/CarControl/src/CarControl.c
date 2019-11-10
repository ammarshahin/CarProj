/*
 *  File : Car_Control.c
 *  Description : This file is used to control the car
 *  Created on: Nov 5, 2019
 *  Author: Ammar Shahin
 */


/************************************************************************/
/*                        Files Includes                                */
/************************************************************************/
#include "DC_Motor.h"
#include "Ultrasonic.h"
#include "CarDirection.h"
#include "CarControl.h"
#include <SwDelay.h>


/************************************************************************/
/*                         Macros and Defines                           */
/************************************************************************/
#define SLOW_SPEED 30
#define FAST_SPEED 100
#define NORMAL_SPEED 50

#define DELAY_TIME_MS 100

#define CAUTIOUS_DISTANCE 60
#define DENGEROUS_DISTANCE 30
/************************************************************************/
/*                        Functions Definitions                         */
/************************************************************************/

/**
 * Function : Car_Init
 * Description: This function is to initialize the car 
 *  it Don't take any thing and returns nothing
 */
void Car_Init(void)
{
	Ultrasonic_Init();
	DC_Motor_Init(DC_MOTOR_CHANNEL_0);
	DC_Motor_Init(DC_MOTOR_CHANNEL_1);
	DC_Motor_Start(DC_MOTOR_CHANNEL_0);
	DC_Motor_Start(DC_MOTOR_CHANNEL_1);
}


/**
 * Function : Car_Action
 * Description: This function is to Implement the car logic 
 *  it Don't take any thing and returns nothing
 */
void Car_Action(void)
{
	Ultrasonic_Trigger();	
	uint8 distance = Ultrasonic_CalculateDistance();
	
	if(distance > CAUTIOUS_DISTANCE) /* No obstacle Go Forward */
	{
		Move_Forward();
		DC_Motor_Set_Speed(FAST_SPEED);
	}
	else if ( (distance < CAUTIOUS_DISTANCE) && (distance > DENGEROUS_DISTANCE) )  /* Obstacle on the near range */
	{
		Move_RotateRight();
		DC_Motor_Set_Speed(NORMAL_SPEED);
		SwDelay_ms(DELAY_TIME_MS);
	}
	else if(distance < DENGEROUS_DISTANCE)  /* Obstacle is very near go back till an enough range to rotate */
	{
		DC_Motor_Set_Speed(SLOW_SPEED);
		Move_Backward();
		SwDelay_ms(DELAY_TIME_MS);
	}
}