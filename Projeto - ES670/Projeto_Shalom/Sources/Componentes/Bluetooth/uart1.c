/* ***************************************************************** */
/* File name:        uart1.c		                                 */
/* File description: This file has a couple of useful functions to   */
/*                   use the UART1 serial communication.             */
/* Author name:      Uglaybe		                                 */
/* Creation date:    23jun2016                                       */
/* Modified by:    	 		                                         */
/* Revision date:    		                                         */
/* ***************************************************************** */

#include "Sistema/uC_definitions.h"
#include "Util/util.h"


#define UART1_ALT											3U
#define UART1_BAUDRATE										38400
#define BUS_CLOCK											20 *1000*1000 //20MHz
#define STOP_CHARACTER										0x0A  	 //LF




/* ************************************************ */
/* Method name:        uart1_init	                */
/* Method description: Initialize UART1 serial      */
/*					   communication			    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void uart1_init(void)
{
	uint16_t divisor;

	/*Habilita PORTE clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);
	/*Define alternativa dos pinos*/
	PORTE_PCR1 |= PORT_PCR_MUX(UART1_ALT);
	PORTE_PCR0 |= PORT_PCR_MUX(UART1_ALT);
	/*Habilita clock da UART1*/
	SIM_SCGC4 |= SIM_SCGC4_UART1(CGC_CLOCK_ENABLED);
	/*Assegura que RX e TX estão desabilitados para configuração*/
	UART1_C2 &= ~(UART_C2_TE_MASK	| UART_C2_RE_MASK);
	/*8bits sem paridade 1 stop bit (CONFIGURAÇÕES PADRÃO)*/
	UART1_C1 = 0;

	/*Cálculo do divisor do baud rate*/
    divisor = (uint16_t)((BUS_CLOCK)/(UART1_BAUDRATE * 16));
    UART1_BDH = (divisor >> 8) & UART_BDH_SBR_MASK;
    UART1_BDL = (divisor & UART_BDL_SBR_MASK);


    /*Habilita RX e TX*/
    UART1_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

}



/* ************************************************ */
/* Method name:        sendChar		                */
/* Method description: send a char to the UART 	    */
/*					   serial communication		    */
/* Input params:       cChar  = char to be sent		*/
/* Output params:      n/a 							*/
/* ************************************************ */
void sendChar(char cChar)
{
    /* Espera o último caracter enviado completar a transmissão */
    while(!(UART1_S1 & UART_S1_TDRE_MASK));
    UART1_D = cChar;
}



/* ************************************************ */
/* Method name:        getChar		                */
/* Method description: get a char from the UART     */
/*					   serial communication. 	    */
/* Output params:      char = char received 		*/
/* ************************************************ */
/*CUIDADO, ESSA FUNÇÃO TRAVA O CÓDIGO ATÉ RECEBER ALGUM CARACTER*/
char getChar (void)
{
	/*Espera até chegar um caracter para ser lido*/
    while (!(UART1_S1 & UART_S1_RDRF_MASK));
    return UART1_D;
}


/* ************************************************ */
/* Method name:        uart1_sendBuffer             */
/* Method description: send a string to the UART1   */
/*					   serial communication		    */
/* Input params:       sBuffer  = string to be sent */
/*					   iSize = size of the string	*/
/*							to be sent.				*/
/* Output params:      n/a 							*/
/* ************************************************ */
void uart1_sendBuffer(char sBuffer[], int iSize)
{
	int i;
	/*Envia cada um dos caracteres*/
	for(i=0; i<iSize; i++)
	{
		util_genDelay088us();
		sendChar(sBuffer[i]);
	}
}



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
int uart1_receiveBuffer(char sBuffer[])
{
	char cChar;
	int iSize = 0;

	/*Espera o caracter de parada ser enviado*/
	while(cChar != STOP_CHARACTER)
	{
		/*Checa se há caracteres para serem recebidos*/
		if(UART_BRD_S1_RDRF(UART1))
		{
			cChar = getChar();
			sBuffer[iSize] = cChar;
			iSize++;
		}
	}
	return iSize;
}
