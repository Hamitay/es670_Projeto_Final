/* ***************************************************************** */
/* File name:        switch_hal.h                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of switch_hal.c                      */
/* Author name:      Uglaybe                                         */
/* Creation date:    25jun2016                                       */
/* Modified by:    	                                                 */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef SOURCES_COMPONENTES_SWITCH_AND_BUTTON_SWITCH_HAL_H_
#define SOURCES_COMPONENTES_SWITCH_AND_BUTTON_SWITCH_HAL_H_


typedef enum {REVERSO, FRENTE}switch_state;



/* ************************************************ */
/* Method name:        switch_init	                */
/* Method description: Initialize switch	        */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void switch_init(void);


/* ************************************************ */
/* Method name:        switch_getSwitchStatus       */
/* Method description: Returns switch status        */
/* Input params:       n/a     						*/
/* Output params:      switch_state = switch status */
/* ************************************************ */
switch_state switch_getSwitchStatus(void);


#endif /* SOURCES_COMPONENTES_SWITCH_AND_BUTTON_SWITCH_HAL_H_ */
