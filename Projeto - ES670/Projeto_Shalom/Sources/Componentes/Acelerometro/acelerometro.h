/* ***************************************************************** */
/* File name:        acelerometro.h                                  */
/* File description: Header file containing the function/methods     */
/*                   prototypes of acelerometro.c                    */
/* Author name:      Uglaybe                                         */
/* Creation date:    25jun2016                                       */
/* Modified by:    	                                                 */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef SOURCES_COMPONENTES_ACELEROMETRO_ACELEROMETRO_H_
#define SOURCES_COMPONENTES_ACELEROMETRO_ACELEROMETRO_H_

#include "Util/util.h"



/* ************************************************ */
/* Method name:        acelerometro_init            */
/* Method description: Initialize accelerometer     */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void acelerometro_init(void);


/* ************************************************ */
/* Method name:        acelerometro_calibrate       */
/* Method description: Calibrate accelerometer      */
/*					   sensor					    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void acelerometro_calibrate(void);


/* ************************************************ */
/* Method name:        acelerometro_getData         */
/* Method description: Get accelerometer read       */
/* Input params:       fXvalue = x axis read 		*/
/* 				       fYvalue = y axis read 		*/
/* 				       fZvalue = z axis read 		*/
/* Output params:      n/a 							*/
/* ************************************************ */
void acelerometro_getData (float* fXvalue, float *fYvalue, float *fZvalue);


#endif /* SOURCES_COMPONENTES_ACELEROMETRO_ACELEROMETRO_H_ */
