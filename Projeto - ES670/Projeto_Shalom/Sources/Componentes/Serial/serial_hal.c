/* ***************************************************************** */
/* File name:        serial_hal.c	                                 */
/* File description: This file has a couple of useful functions to   */
/*                   use the UART serial communication.              */
/* Author name:      Uglaybe		                                 */
/* Creation date:    27apr2016                                       */
/* Modified by:    	 Bruno	                                         */
/* Revision date:    05may2016                                       */
/* ***************************************************************** */

#include "debugUart.h"
#include "Util/util.h"
#include "fsl_debug_console.h"
#include "Sistema/uC_definitions.h"
#include "serial_hal.h"
#include "fsl_device_registers.h"


#define LF 0x0A



/* ************************************************ */
/* Method name:        initUart		                */
/* Method description: Initizalize UART serial      */
/*					   communication			    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void serial_init (void)
{
	debugUart_init();
	return;
}



/* ************************************************ */
/* Method name:        sendBuffer	                */
/* Method description: send a string to the UART    */
/*					   serial communication		    */
/* Input params:       cCmdSent  = string to be sent*/
/*					   iCmdSize = size of the string*/
/*							to be sent.				*/
/* Output params:      n/a 							*/
/* ************************************************ */
void serial_sendBuffer (char* cCmdSent, int iCmdSize)
{
	int i;
	for(i = 0; i<iCmdSize; i++)
	{
		PUTCHAR(cCmdSent[i]);
	}
	return;
}


/* ************************************************ */
/* Method name:        receiveBuffer                */
/* Method description: get a string from the UART   */
/*					   serial communication. It	    */
/*					   assumes there are a LF 		*/
/*					   character at the end of the  */
/*					   string.						*/
/* Input params:       cCmd  = string received		*/
/* Output params:      int = string received size	*/
/* ************************************************ */
int serial_receiveBuffer (char cCmd[])
{
	char cChar;
	int iCmdSize = 0;

	while(cChar != LF)
	{
		/*Check if there are characters to be read*/
		if(UART0_BRD_S1_RDRF(UART0))
		{
			cChar = GETCHAR();
			cCmd[iCmdSize] = cChar;
			iCmdSize++;
		}
	}
	return iCmdSize;
}

