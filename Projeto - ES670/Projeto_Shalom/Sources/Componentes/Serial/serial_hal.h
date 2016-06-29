/* ***************************************************************** */
/* File name:        serial_hal.h                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of serial_hal.c                      */
/* Author name:      Uglaybe                                         */
/* Creation date:    28apr2016                                       */
/* Modified by:    	                                                 */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef SOURCES_SERIAL_SERIAL_HAL_H_
#define SOURCES_SERIAL_SERIAL_HAL_H_

#include "Util/util.h"


/* ************************************************ */
/* Method name:        serial_init	                */
/* Method description: Initizalize UART serial      */
/*					   communication			    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void serial_init (void);



/* ************************************************ */
/* Method name:        serial_sendBuffer	        */
/* Method description: send a string to the UART    */
/*					   serial communication		    */
/* Input params:       cCmdSent  = string to be sent*/
/*					   iCmdSize = size of the string*/
/*							to be sent.				*/
/* Output params:      n/a 							*/
/* ************************************************ */
void serial_sendBuffer (char* cCmdSent, int iCmdSize);



/* ************************************************ */
/* Method name:        serial_receiveBuffer         */
/* Method description: get a string from the UART   */
/*					   serial communication. It	    */
/*					   assumes there are a LF 		*/
/*					   character at the end of the  */
/*					   string.						*/
/* Input params:       cCmd  = string received		*/
/* Output params:      int = string received size	*/
/* ************************************************ */
int serial_receiveBuffer (char cCmd[]);


#endif /* SOURCES_SERIAL_SERIAL_HAL_H_ */
