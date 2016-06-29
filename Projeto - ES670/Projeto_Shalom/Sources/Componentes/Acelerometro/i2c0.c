/* ***************************************************************** */
/* File name:        i2c0.c			                                 */
/* File description: This file has a couple of useful functions to   */
/*                   use the I2C0 with the accelerometer sensor.     */
/* Author name:      Uglaybe		                                 */
/* Creation date:    25jun2016                                       */
/* Modified by:    	 	      	                                     */
/* Revision date:    		                                         */
/* ***************************************************************** */

#include "Sistema/uC_definitions.h"
#include "i2c0.h"

#define I2C0_FREQUENCY_CONFIG									0x14



/* ************************************************ */
/* Method name:        Pause			            */
/* Method description: Wait for n number core clock */
/*					   cycles.						*/
/* Input params:       number = number of cycles    */
/* Output params:      n/a 							*/
/* ************************************************ */
void Pause(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		__asm("NOP");
	};
}


/* ************************************************ */
/* Method name:        disableAck		            */
/* Method description: Disable acknowledge sending  */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void disableAck(void)
{
	I2C0_C1 |= I2C_C1_TXAK_MASK; //Não envia acknowledge após o próximo byte recebido
}


/* ************************************************ */
/* Method name:        enableAck		            */
/* Method description: Enable acknowledge sending   */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void enableAck(void)
{
	I2C0_C1 &= ~I2C_C1_TXAK_MASK; //Habilita o envio de acknowledge após receber bytes
}        

/* ************************************************ */
/* Method name:        sendRepeatedStart            */
/* Method description: Send a repeated start signal */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void sendRepeatedStart(void)
{
	I2C0_C1 |= I2C_C1_RSTA_MASK; //Envia um repeated start
}    

/* ************************************************ */
/* Method name:        enterReceiveMode             */
/* Method description: Start to record i2c0 bus data*/
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void enterReceiveMode(void)
{
	I2C0_C1 &= ~I2C_C1_TX_MASK; //Seleciona direção do pino i2c como entrada
}

/* ************************************************ */
/* Method name:        writeByte		            */
/* Method description: Send a byte to i2c0 bus      */
/* Input params:       cData = byte to be sent		*/
/* Output params:      n/a 							*/
/* ************************************************ */
void writeByte(char cData)
{
	I2C0_D = cData; //Escreve o byte no registrador para ser enviado
}

/* ************************************************ */
/* Method name:        readByte			            */
/* Method description: get i2c0 received byte       */
/* Input params:       n/a     						*/
/* Output params:      char = received byte			*/
/* ************************************************ */
char readByte(void)
{
	return I2C0_D;
}   

/* ************************************************ */
/* Method name:        startTransmission            */
/* Method description: Start a i2c0 transmission    */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void startTransmission(void)
{
	I2C0_C1 |= I2C_C1_TX_MASK; //Seleciona direção do pino i2c como saída
	I2C0_C1 |= I2C_C1_MST_MASK; //Envia um start bit para o barramento i2c
}
                               
/* ************************************************ */
/* Method name:        sendStopBit		            */
/* Method description: Stop a i2c0 transmission     */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void sendStopBit(void)
{
	I2C0_C1 &= ~I2C_C1_MST_MASK; //Envia um stop bit para o barramento i2c
	I2C0_C1 &= ~I2C_C1_TX_MASK; //Seleciona direçãod o pino i2c como entrada
}
                               
/* ************************************************ */
/* Method name:        waitAck			            */
/* Method description: Wait for slave acknowledge   */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void waitAck(void)
{
	while((I2C0_S & I2C_S_IICIF_MASK)==0); //Espera acknowledge do dispositivo.
	I2C0_S |= I2C_S_IICIF_MASK; //Libera o registrador de status para receber outro acknowledge
}              
                               
/* ************************************************ */
/* Method name:        i2c0_init		            */
/* Method description: Initialize i2c0		        */
/* Input params:       n/a     						*/
/* Output params:      n/a 							*/
/* ************************************************ */
void i2c0_init(void)
{
	SIM_SCGC4 |= SIM_SCGC4_I2C0(CGC_CLOCK_ENABLED); //Habilita clock no módulo I2C0 
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED); //Habilita clock na porta E 
	PORTE_PCR24 = PORT_PCR_MUX(5U); //Seleciona alternativa do PTE24 como I2C0 SCL 
	PORTE_PCR25 = PORT_PCR_MUX(5U); // Seleciona alternativa do PTE25 como I2C0 SDA 
	I2C0_F  = I2C0_FREQUENCY_CONFIG; //SCL frequency = 250kHz - SDA hold time = 0.85us, SCL start hold time = 1.7us, SCL stop hold time = 2.05us
	I2C0_C1 = I2C_C1_IICEN_MASK; // Enable do módulo I2C0 
}


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
void i2c0_writeRegister(unsigned char ucDeviceAddress, unsigned char ucRegisterAddress, char cData)
{
	startTransmission();	          
	writeByte(ucDeviceAddress << 1); //Envia endereço do dispositivo e coloca o bit de W/R = 0, escrita.
	waitAck();

	writeByte(ucRegisterAddress); //Envia endereço do registrador que queremos escrever
	waitAck();

	writeByte(cData);
	waitAck();

	sendStopBit();

    Pause(50);

}

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
unsigned char i2c0_readRegister(unsigned char ucDeviceAddress, unsigned char ucRegisterAddress)
{
	unsigned char readValue;
	  
	startTransmission();	          
	writeByte(ucDeviceAddress << 1); //Envia endereço do dispositivo e coloca o bit de W/R = 0, escrita.
	waitAck();										

	writeByte(ucRegisterAddress); //Envia endereço do registrador que queremos ler
	waitAck();

	sendRepeatedStart();
	
	writeByte( (ucDeviceAddress << 1) | 0x01); //Envia endereço do dispositivo e coloca o bit de W/R = 1, leitura. 
	waitAck();	

	enterReceiveMode();
	disableAck();

	readValue = readByte();												
	waitAck();

	sendStopBit();  
	readValue = readByte();
	
	Pause(50);
	
	return readValue;
}

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
void i2c0_readMultiRegisters(unsigned char ucDeviceAddress, unsigned char ucRegisterAddress, int iNumber, unsigned char *ucValues)
{
	char i;
	
	startTransmission();	          
	writeByte(ucDeviceAddress << 1); //Envia endereço do dispositivo e coloca o bit de W/R = 0, escrita.
	waitAck();										

	writeByte(ucRegisterAddress); //Envia endereço do registrador que queremos ler
	waitAck();

	sendRepeatedStart();
		
	writeByte( (ucDeviceAddress << 1) | 0x01); //Envia endereço do dispositivo e coloca o bit de W/R = 1, leitura.
	waitAck();	

	enterReceiveMode();
	enableAck();
	
// ---------------------------
	i = readByte();
	waitAck();
	
	for(i=0; i<iNumber-2; i++)
	{
	    *ucValues = readByte();
	    ucValues++;
	    waitAck();
	}
	
	disableAck();
	*ucValues = readByte();
	ucValues++;
	waitAck();
	sendStopBit();
	*ucValues = readByte();

	Pause(50);
}



