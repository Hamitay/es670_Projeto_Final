/* ***************************************************************** */
/* File name:        acelerometro.h                                  */
/* File description: Header file containing the function/methods     */
/*                   prototypes of i2c0.c            		         */
/* Author name:      Uglaybe                                         */
/* Creation date:    25jun2016                                       */
/* Modified by:    	                                                 */
/* Revision date:                                                    */
/* ***************************************************************** */
#ifndef SOURCES_COMPONENTES_ACELEROMETRO_I2C0_H_
#define SOURCES_COMPONENTES_ACELEROMETRO_I2C0_H_

/* ************************************************ */
/* Method name:        i2c0_init		            */
/* Method description: Initialize i2c0		        */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void i2c0_init(void);

/* ************************************************ */
/* Method name:        i2c0_writeRegister           */
/* Method description: Write in a i2c0 slave        */
/* Input params:       ucDeviceAddress = slave 		*/
/* 					   address 						*/
/* 				       ucRegisterAddress = slave	*/
/*					   register address				*/
/* 				       cData = data to be written   */
/* Output params:      n/a 							*/
/* ************************************************ */
void i2c0_writeRegister(unsigned char ucDeviceAddress, unsigned char ucRegisterAddress, char cData);

/* ************************************************ */
/* Method name:        i2c0_readRegister            */
/* Method description: Read something in a i2c0 	*/
/* 					   slave        				*/
/* Input params:       ucDeviceAddress = slave 		*/
/* 					   address 						*/
/* 				       ucRegisterAddress = slave	*/
/*					   register address				*/
/* Output params:      unsigned char = read data	*/
/* ************************************************ */
unsigned char i2c0_readRegister(unsigned char ucDeviceAddress, unsigned char ucRegisterAddress);

/* ************************************************ */
/* Method name:        i2c0_readMultiRegisters      */
/* Method description: Read multiples bytes in a    */
/*					   i2c0 slave			        */
/* Input params:       ucDeviceAddress = slave 		*/
/* 					   address 						*/
/* 				       ucRegisterAddress = slave	*/
/*					   register address				*/
/*					   iNumber = number of bytes    */
/* 				       ucValues = data read vector  */
/* Output params:      n/a 							*/
/* ************************************************ */
void i2c0_readMultiRegisters(unsigned char ucDeviceAddress, unsigned char ucRegisterAddress, int iNumber, unsigned char *ucValues);



#endif /* SOURCES_COMPONENTES_ACELEROMETRO_I2C0_H_ */
