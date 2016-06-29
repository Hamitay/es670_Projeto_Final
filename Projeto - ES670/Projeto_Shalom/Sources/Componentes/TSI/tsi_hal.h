/* ***************************************************************** */
/* File name:        tsi_hal.h  	                                 */
/* File description: Header File containing the methods to configure */
/*					 and use the TSI of the KL25Z board              */
/*                                                                   */
/*                                                                   */
/* Author name:      Henrique Amitay                                 */
/* Creation date:    08jun2016                                       */
/* Revision date:    08jun2016                                       */
/* ***************************************************************** */

#include "MKL25Z4.h"

#ifndef SOURCES_TSI_TSI_HAL_H_
#define SOURCES_TSI_TSI_HAL_H_

/* ************************************************ */
/* Method name:        tsi_init         	        */
/* Method description: Configure the TSI            */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void tsi_init(void);

/* ************************************************ */
/* Method name:        tsi_scan         	        */
/* Method description: Starts scanning the TSI and  */
/*                     returns the scanned value    */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
float tsi_scan(void);

#endif /* SOURCES_TSI_TSI_HAL_H_ */
