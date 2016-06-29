/* ***************************************************************** */
/* File name:        tsi_hal.c  	                                 */
/* File description: Header File containing the methods to configure */
/*					 and use the TSI of the KL25Z board              */
/*                                                                   */
/*                                                                   */
/* Author name:      Henrique Amitay                                 */
/* Creation date:    08jun2016                                       */
/* Revision date:    08jun2016                                       */
/* ***************************************************************** */

#include "tsi_hal.h"

#define MAX_TOUCH_VALUE				2400
#define MIN_TOUCH_VALUE				650

/* ************************************************ */
/* Method name:        tsi_init         	        */
/* Method description: Configure the TSI            */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void tsi_init(void){

	/*Ungate clock*/
	SIM_SCGC5 |= SIM_SCGC5_TSI(1u);

	TSI0_GENCS |= (0b0000 << 24u);
	TSI0_GENCS |= (0b100 << 21u);
	TSI0_GENCS |= (0b00 << 19u);
	TSI0_GENCS |= (0b111 << 16u);
	TSI0_GENCS |= (0b100 << 13u);
	TSI0_GENCS |= (0b10001 << 8u);
	TSI0_GENCS |= (0b1 << 7u);
	TSI0_GENCS |= (0b0 << 6u);

	// TSI0_GENCS |= (TSI_GENCS_MODE(0));          //Set to TSI Cap Sense (non-noise detection)
	// |TSI_GENCS_REFCHRG(4)        			   //Reference osc charge/discharge current is 8uA
	// |TSI_GENCS_DVOLT(0)          			   //Osc voltage rails set to 1.03V, Vp=1.33V, Vm=0.30V
	// |TSI_GENCS_EXTCHRG(7)        			   //External electrode osc charge/discharge current is 64uA
	// |TSI_GENCS_PS(4)            			  	   //Electrode osc prescaler is div/16
	// |TSI_GENCS_NSCN(11)         			  	   //Number of scans for each external electrode is 18 times/electrode

	TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;	//ENTENDER

}

/* ************************************************ */
/* Method name:        tsi_scan         	        */
/* Method description: Starts scanning the TSI and  */
/*                     returns the scanned value    */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
float tsi_scan(void){

	float ftouch;
	int itouch;

	TSI0_DATA |= TSI_DATA_TSICH(10);          // Select the TSI Channel 10 to be scanned
	TSI0_DATA |= TSI_DATA_SWTS_MASK;          // Start a software trigger to scan selected electrode(s)

	while (!(TSI0_GENCS&TSI_GENCS_EOSF_MASK));// Wait for electrode scan to complete
	itouch=(TSI0_DATA&TSI_DATA_TSICNT_MASK);   // Read data from TSI0_Data register
	TSI0_GENCS |= TSI_GENCS_EOSF_MASK;


	ftouch = (float)((float)itouch - MIN_TOUCH_VALUE)/(MAX_TOUCH_VALUE - MIN_TOUCH_VALUE);

	return ftouch;

}

