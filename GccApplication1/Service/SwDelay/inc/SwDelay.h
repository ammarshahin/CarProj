/*
 * SwDelay.h
 *
 * Created: 10/21/2019 9:17:54 PM
 *  Author: Ammar Shahin
 */ 


#ifndef SOFTWAREDELAY_H_
#define SOFTWAREDELAY_H_


/*===========================SW_Delay Functions===============================*/
/**
 * Description: Function to make a software Delay in the Melli seconds 
 * @param n_ms the number of ms to delay
 */
void SwDelay_ms(uint32 NoOfMilleSeconds);

/**
 * Description: Function to make a software Delay in the Micro Seconds. 
 * @param NoOfMicroeSeconds the number of Microe Seconds to delay
 */
void SwDelay_us(uint32 NoOfMicroeSeconds);

#endif /* SOFTWAREDELAY_H_ */