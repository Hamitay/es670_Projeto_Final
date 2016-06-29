/* ***************************************************************** */
/* File name:        switch_hal.c	                                 */
/* File description: This file has a couple of useful functions to   */
/*                   use the switch coupled on the control.	         */
/* Author name:      Uglaybe		                                 */
/* Creation date:    25jun2016                                       */
/* Modified by:    	 		                                         */
/* Revision date:    		                                         */
/* ***************************************************************** */

#include "Sistema/uC_definitions.h"
#include "switch_hal.h"

#define SWITCH_PIN							4U



/* ************************************************ */
/* Method name:        switch_init	                */
/* Method description: Initialize switch	        */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void switch_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);
    PORTA_PCR4 |= PORT_PCR_MUX(1U);
    GPIOA_PDDR &= ~GPIO_PDDR_PDD(0x01u << SWITCH_PIN);
}


/* ************************************************ */
/* Method name:        switch_getSwitchStatus       */
/* Method description: Returns switch status        */
/* Input params:       n/a     						*/
/* Output params:      switch_state = switch status */
/* ************************************************ */
switch_state switch_getSwitchStatus(void)
{
	switch_state stReturn = REVERSO;
	if(FRENTE == ((GPIOA_PDIR & (0x01u << SWITCH_PIN)) >> SWITCH_PIN))
		stReturn = FRENTE;
	return stReturn;
}
