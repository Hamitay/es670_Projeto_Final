/* ***************************************************************** */
/* File name:        acelerometro.c	                                 */
/* File description: This file has a couple of useful functions to   */
/*                   use the accelerometer sensor.	                 */
/* Author name:      Uglaybe		                                 */
/* Creation date:    25jun2016                                       */
/* Modified by:    	 	      	                                     */
/* Revision date:    		                                         */
/* ***************************************************************** */

#include "Sistema/uC_definitions.h"
#include "i2c0.h"
#include "acelerometro.h"
#include "MMA8451Q_definitions.h"

/* ************************************************ */
/* Method name:        acelerometro_init            */
/* Method description: Initialize accelerometer     */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void acelerometro_init(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED); //Habilita o clock da porta A
	PORTA_PCR14 |= PORT_PCR_MUX(1U); //Seleciona alternativa para o PTA14 como GPIO
	//PORTA_PCR14 |= (PORT_PCR_ISF_MASK | PORT_PCR_IRQC(0b1010)); //Habilita interrupção e configura interrupção na borda de descida

	//Enable PORTA interrupt on NVIC
	//NVIC_ICPR |= 1 << ((INT_PORTA - 16)%32);
	//NVIC_ISER |= 1 << ((INT_PORTA - 16)%32);

	i2c0_init();

	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, RESET_REGISTERS);
	
	unsigned char cVal = 0;

	do //Espera o acelerometro resetar 
	{
		cVal = i2c0_readRegister(MMA845x_I2C_ADDRESS, CTRL_REG2) & RESET_REGISTERS; 
	}while (cVal);

	i2c0_writeRegister(MMA845x_I2C_ADDRESS, XYZ_DATA_CFG_REG, SENSITIVITY_CONFIG); 
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, RESOLUTION_CONFIG);
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, CTRL_REG1_CONFIG);	
}

/* ************************************************ */
/* Method name:        acelerometro_calibrate       */
/* Method description: Calibrate accelerometer      */
/*					   sensor					    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void acelerometro_calibrate(void)
{
	char cVal= 0;
	unsigned char cSensorData[6];
	short Xdata, Ydata, Zdata;
	char Xoffset, Yoffset, Zoffset;

	while (!cVal) //Espera a primeira amostra de dados		 
	{
		cVal = i2c0_readRegister(MMA845x_I2C_ADDRESS, STATUS_REG) & IS_DATA_READY; 
	} 	
	  	
	i2c0_readMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, cSensorData); //Lê os registradores MSB e LSB da leitura do sensor de cada eixo  
	  						
	Xdata = ((short) (cSensorData[0]<<8 | cSensorData[1])) >> 2; //Coloca em Xdata o valor MSB e LSB da leitura para o eixo x
	Ydata = ((short) (cSensorData[2]<<8 | cSensorData[3])) >> 2; //Coloca em Ydata o valor MSB e LSB da leitura para o eixo y
	Zdata = ((short) (cSensorData[4]<<8 | cSensorData[5])) >> 2; //Coloca em Zdata o valor MSB e LSB da leitura para o eixo z
	  					
	Xoffset = ((-1)*Xdata) / 8;	//Calcula offset para o eixo x
	Yoffset = ((-1)*Ydata) / 8;	//Calcula offset para o eixo y
	Zoffset = (SENSITIVITY_8G - Zdata) / 8; //Calcula offset para o eixo z
	//OBS: A divisão por 8 serve como um shift para a direita de 3 bits para truncar o offset e caber no registrador de 8 bits do acelerometro
	  					
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, CTRL_REG1_STANDBY); //Entra no modo standby para permitir escrita nos registradores de offset	
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, OFF_X_REG, Xoffset); //Escreve o offset em x
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, OFF_Y_REG, Yoffset);	
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, OFF_Z_REG, Zoffset);	
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG3, LOW_INTERRUPTION); //Habilita interrupção em nível lógico baixo 
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, DATA_READY_INT); //Habilita interrupção quando o dado estiver pronto
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, INT1_PIN_INTERRUPTION); //Interrupção direcionada para o pino INT1 - PTA14 
	i2c0_writeRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, CTRL_REG1_CONFIG);
}

/* ************************************************ */
/* Method name:        acelerometro_getData         */
/* Method description: Get accelerometer read       */
/* Input params:       fXvalue = x axis read 		*/
/* 				       fYvalue = y axis read 		*/
/* 				       fZvalue = z axis read 		*/
/* Output params:      n/a 							*/
/* ************************************************ */
void acelerometro_getData (float* fXvalue, float *fYvalue, float *fZvalue)
{																
	short Xdata, Ydata, Zdata;
	unsigned char cSensorData[6];


	i2c0_readMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, cSensorData);		// Read data output registers 0x01-0x06
    
	Xdata = ((short) (cSensorData[0]<<8 | cSensorData[1])) >> 2; //Coloca em Xdata o valor MSB e LSB da leitura para o eixo x
	Ydata = ((short) (cSensorData[2]<<8 | cSensorData[3])) >> 2; //Coloca em Ydata o valor MSB e LSB da leitura para o eixo y
	Zdata = ((short) (cSensorData[4]<<8 | cSensorData[5])) >> 2; //Coloca em Zdata o valor MSB e LSB da leitura para o eixo z
	
	*fXvalue = ((float) Xdata) / SENSITIVITY_8G; //Calcula o valor da leitura do acelerometro para x
	*fYvalue = ((float) Ydata) / SENSITIVITY_8G; //Calcula o valor da leitura do acelerometro para y
	*fZvalue = ((float) Zdata) / SENSITIVITY_8G; //Calcula o valor da leitura do acelerometro para z

}

