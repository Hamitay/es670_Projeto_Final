/* ***************************************************************** */
/* File name:        button_hal.c	                                 */
/* File description: This file has a couple of useful functions to   */
/*                   use the button coupled on the control.	         */
/* Author name:      Uglaybe		                                 */
/* Creation date:    28jun2016                                       */
/* Modified by:    	 		                                         */
/* Revision date:    		                                         */
/* ***************************************************************** */

#include "Sistema/uC_definitions.h"
#include "button_hal.h"

#define BUTTON_PIN							5U



/* ************************************************ */
/* Method name:        button_init	                */
/* Method description: Initialize button	        */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void button_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);
    PORTA_PCR1 |= PORT_PCR_MUX(1U);
    GPIOA_PDDR &= ~GPIO_PDDR_PDD(1U << BUTTON_PIN);
}


/* ************************************************ */
/* Method name:        button_getButtonStatus       */
/* Method description: Returns button status        */
/* Input params:       n/a     						*/
/* Output params:      button_state = button status */
/* ************************************************ */
button_state button_getButtonStatus(void)
{
	return (GPIOA_PDIR & (1U << BUTTON_PIN)) >> BUTTON_PIN;
}


