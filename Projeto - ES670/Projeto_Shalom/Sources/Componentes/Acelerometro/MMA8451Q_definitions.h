/*
 * MMA8451Q_definitions.h
 *
 *  Created on: 24/06/2016
 *      Author: Uglaybe Piell
 */

#ifndef SOURCES_COMPONENTES_ACELEROMETRO_MMA8451Q_DEFINITIONS_H_
#define SOURCES_COMPONENTES_ACELEROMETRO_MMA8451Q_DEFINITIONS_H_

#define MMA845x_I2C_ADDRESS   0x1D

//Registradores do MMA8451Q

#define STATUS_REG            0x00		

#define OUT_X_MSB_REG         0x01		
#define OUT_X_LSB_REG         0x02		
#define OUT_Y_MSB_REG         0x03		
#define OUT_Y_LSB_REG         0x04		
#define OUT_Z_MSB_REG         0x05		
#define OUT_Z_LSB_REG         0x06		

#define F_SETUP_REG           0x09    	 
#define TRIG_CFG_REG          0x0A    	
#define SYSMOD_REG            0x0B    	
#define INT_SOURCE_REG        0x0C    	
#define WHO_AM_I_REG          0x0D    	
#define XYZ_DATA_CFG_REG      0x0E    	
#define HP_FILTER_CUTOFF_REG  0x0F    	

#define PL_STATUS_REG         0x10    	
#define PL_CFG_REG            0x11    	
#define PL_COUNT_REG          0x12    	
#define PL_BF_ZCOMP_REG       0x13    	
#define P_L_THS_REG           0x14    	

#define FF_MT_CFG_REG         0x15    	
#define FF_MT_SRC_REG         0x16    	
#define FT_MT_THS_REG         0x17    	
#define FF_MT_COUNT_REG       0x18    	

#define TRANSIENT_CFG_REG     0x1D    	
#define TRANSIENT_SRC_REG     0x1E    	
#define TRANSIENT_THS_REG     0x1F    
#define TRANSIENT_COUNT_REG   0x20    	

#define PULSE_CFG_REG         0x21    	
#define PULSE_SRC_REG         0x22    	
#define PULSE_THSX_REG        0x23    	
#define PULSE_THSY_REG        0x24
#define PULSE_THSZ_REG        0x25
#define PULSE_TMLT_REG        0x26    	
#define PULSE_LTCY_REG        0x27    	 
#define PULSE_WIND_REG        0x28    	

#define ASLP_COUNT_REG        0x29    	

#define CTRL_REG1             0x2A    	
#define CTRL_REG2             0x2B    	
#define CTRL_REG3             0x2C    	
#define CTRL_REG4             0x2D    	
#define CTRL_REG5             0x2E    	

#define OFF_X_REG             0x2F    	
#define OFF_Y_REG             0x30
#define OFF_Z_REG             0x31

/* ------------------Comandos e configurações--------------------- */
//Reseta Registradores
#define RESET_REGISTERS	  	  0x40
//Sensibilidade
#define SENSITIVITY_8G		  2048/2
//Configuração de Sensibilidade
#define SENSITIVITY_CONFIG	  0x00 //4G
//Configuração do modo de resolução e consumo de energia
#define RESOLUTION_CONFIG	  0x02 //Alta resolução
//Configuração da taxa de amostragem, filtragem e habilita o acelerômetro
#define CTRL_REG1_CONFIG	  0x35 //ODR = 6.25Hz, Reduced noise, Active mode	
//Lê o bit do registrador de status
#define	IS_DATA_READY		  0x08
//Entra no modo Standby
#define CTRL_REG1_STANDBY	  0x00
//Habilita interrupção em nível lógico baixo
#define LOW_INTERRUPTION	  0x00
//Habilita interrupção quando o dado estiver pronto
#define DATA_READY_INT		  0x01
//Interrupção direcionada para o pino INT1 - PTA14
#define INT1_PIN_INTERRUPTION 0x01

#endif /* SOURCES_COMPONENTES_ACELEROMETRO_MMA8451Q_DEFINITIONS_H_ */
