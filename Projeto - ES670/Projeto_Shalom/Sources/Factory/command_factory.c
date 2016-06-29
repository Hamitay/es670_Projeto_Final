/* ***************************************************************** */
/* File name:        command_factory.c  	                         */
/* File description: Source file containing the functions/methods    */
/*                   that generate command words used by the         */
/*                   controller board to comunicate with the cart    */
/* Author name:      Henrique Amitay                                 */
/* Creation date:    25jun2016                                       */
/* Revision date:    25jun2016                                       */
/* ***************************************************************** */

#include "command_factory.h"

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

void buildCommand(float fAcel, float fTouch, int iDirection, char *cCommand)
{
	/* Command to be built */
	/* $snnn#nnn#n$ = 12*/
	char cWord[12];

	/*Acceleration Angle Treatment*/

	cWord[0] = '$';

	/* Changes the interval of fAcel from [-1,+1] to [-180,+180], we also multiply by 100 to consider floating point*/
	float faux = fAcel*100*180; 
	faux = faux/100;

	/*We truncate the number*/
	int iaux = (int)faux;

	/*Checks which signal the angle is, and gets number absolute value*/
	if(iaux < 0){
		cWord[1] = '-';
		iaux = (-1)*iaux;
	}
	else
		cWord[1] = '+';


	/*Converts the number to string then writes it to the command*/
	cWord[2] = (48+iaux/100);
	iaux = iaux%100;
	cWord[3] = (48+iaux/10);
	iaux = iaux%10;
	cWord[4] = (48+iaux);

	/*Divide the information*/
	cWord[5] = '#';

	/*Touch Treatment*/
	faux = fTouch*100;
	iaux = (int)faux;

	/*Converts the number to string then writes it to the command*/
	cWord[6] = (48+iaux/100);
	iaux = iaux%100;
	cWord[7] = (48+iaux/10);
	iaux = iaux%10;
	cWord[8] = (48+iaux);

	/*Divide the information*/
	cWord[9] = '#';

	/*Checks the direction*/
	cWord[10] = 48+iDirection;
	cWord[11] = '$';

	int i;
	for(i=0;i<11;i++)
	cCommand[i] = cWord[i];



	return;

}
