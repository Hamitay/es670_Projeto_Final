/* ***************************************************************** */
/* File name:        command_factory.h  	                         */
/* File description: Header file containing the functions/methods    */
/*                   that generate command words used by the         */
/*                   controller board to comunicate with the cart    */
/* Author name:      Henrique Amitay                                 */
/* Creation date:    25jun2016                                       */
/* Revision date:    25jun2016                                       */
/* ***************************************************************** */


/* ************************************************** */
/* Method name: 	   buildCommand                   */
/* Method description: Builds the command that will   */
/*                     be sent to the cart            */
/* Input params:	   fAcel: x axis of accelerometer */
/*                     fTouch: TSI data               */
/*                     iDirection: status of switch   */
/*                     cCommand: pointer to command   */
/*                     string                         */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void buildCommand(float fAcel, float fTouch, int iDirection, char cCommand[]);