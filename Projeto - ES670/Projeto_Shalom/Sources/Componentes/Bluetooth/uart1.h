/* ***************************************************************** */
/* File name:        uart1.h	                                     */
/* File description: Header file containing the function/methods     */
/*                   prototypes of uart1.c	                         */
/* Author name:      Uglaybe                                         */
/* Creation date:    23jun2016                                       */
/* Modified by:    	                                                 */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef SOURCES_BLUETOOTH_uart1_HAL_H_
#define SOURCES_BLUETOOTH_uart1_HAL_H_

/* ************************************************ */
/* Method name:        uart1_init	                */
/* Method description: Initialize UART1 serial      */
/*					   communication			    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void uart1_init(void);

/* ************************************************ */
/* Method name:        uart1_sendBuffer             */
/* Method description: send a string to the UART1   */
/*					   serial communication		    */
/* Input params:       sBuffer  = string to be sent */
/*					   iSize = size of the string	*/
/*							to be sent.				*/
/* Output params:      n/a 							*/
/* ************************************************ */
void uart1_sendBuffer(char sBuffer[], int iSize);


/* ************************************************ */
/* Method name:        uart1_receiveBuffer          */
/* Method description: get a string from the UART1  */
/*					   serial communication. It	    */
/*					   assumes there are a stop 	*/
/*					   character at the end of the  */
/*					   string.						*/
/* Input params:       sBuffer  = string received	*/
/* Output params:      int = string received size	*/
/* ************************************************ */
int uart1_receiveBuffer(char sBuffer[]);


#endif /* SOURCES_BLUETOOTH_uart1_HAL_H_ */
