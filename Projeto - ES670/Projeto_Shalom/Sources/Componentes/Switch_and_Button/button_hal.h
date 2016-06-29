/* ***************************************************************** */
/* File name:        button_hal.h                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of button_hal.c                      */
/* Author name:      Uglaybe                                         */
/* Creation date:    28jun2016                                       */
/* Modified by:    	                                                 */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef SOURCES_COMPONENTES_SWITCH_AND_BUTTON_BUTTON_HAL_H_
#define SOURCES_COMPONENTES_SWITCH_AND_BUTTON_BUTTON_HAL_H_

typedef enum {OFF, ON}button_state;

/* ************************************************ */
/* Method name:        button_init	                */
/* Method description: Initialize button	        */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void button_init(void);


/* ************************************************ */
/* Method name:        button_getButtonStatus       */
/* Method description: Returns button status        */
/* Input params:       n/a     						*/
/* Output params:      button_state = button status */
/* ************************************************ */
button_state button_getButtonStatus(void);



#endif /* SOURCES_COMPONENTES_SWITCH_AND_BUTTON_BUTTON_HAL_H_ */
