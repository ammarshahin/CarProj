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
	
	if(distance > 60) /* No obstacle Go Forward */
	{
		Move_Forward();
		DC_Motor_Set_Speed(95);
	}
	else if ( (distance < 60) && (distance > 30) )  /* Obstacle on the near range */
	{
		Move_RotateRight();
		DC_Motor_Set_Speed(50);
		SwDelay_ms(100);
	}
	else if(distance < 30)  /* Obstacle is very near go back till an enough range to rotate */
	{
		DC_Motor_Set_Speed(30);
		Move_Backward();
		SwDelay_ms(100);
	}
}