/* ***************************************************************** */
/* File name:        uC_definitions 			                     */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Modified by:    	 Uglaybe                                         */
/* Revision date:    18may2016                                       */
/* ***************************************************************** */


#ifndef SOURCES_ES670_PERIPHERAL_BOARD_H_
#define SOURCES_ES670_PERIPHERAL_BOARD_H_

#include "fsl_device_registers.h"
#include "MKL25Z4.h"
#include "MKL25Z4_extension.h"


/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U

/* GPIO Alternative*/
#define GPIO_ALT					0x01U

/* GPIO OPERATOR   */
#define GPIO_OPERATOR				0x01U


/*                 END OF General uC definitions         */




/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8U                                      /* register selector */
#define LCD_RS_DIR                  (GPIO_OUTPUT << 8U)
#define LCD_RS_ALT                  kPortMuxAsGpio

#define LCD_ENABLE_PIN              9U                                      /* enable pin */
#define LCD_ENABLE_DIR              (GPIO_OUTPUT << 9U)
#define LCD_ENABLE_ALT              kPortMuxAsGpio

#define LCD_RS_HIGH                 1U
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  0U
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U

#define LCD_DATA_DIR                kGpioDigitalOutput                      /* LCD data pins */
#define LCD_DATA_ALT                kPortMuxAsGpio

#define LCD_DATA_DB0_PIN            0U
#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB3_PIN            3U
#define LCD_DATA_DB4_PIN            4U
#define LCD_DATA_DB5_PIN            5U
#define LCD_DATA_DB6_PIN            6U
#define LCD_DATA_DB7_PIN            7U

#define LCD_DATA_DB0_ALT            kPortMuxAsGpio
#define LCD_DATA_DB1_ALT            kPortMuxAsGpio
#define LCD_DATA_DB2_ALT            kPortMuxAsGpio
#define LCD_DATA_DB3_ALT            kPortMuxAsGpio
#define LCD_DATA_DB4_ALT            kPortMuxAsGpio
#define LCD_DATA_DB5_ALT            kPortMuxAsGpio
#define LCD_DATA_DB6_ALT            kPortMuxAsGpio
#define LCD_DATA_DB7_ALT            kPortMuxAsGpio

#define LCD_DATA_DB0_DIR			(GPIO_OUTPUT << 0U)
#define LCD_DATA_DB1_DIR			(GPIO_OUTPUT << 1U)
#define LCD_DATA_DB2_DIR			(GPIO_OUTPUT << 2U)
#define LCD_DATA_DB3_DIR			(GPIO_OUTPUT << 3U)
#define LCD_DATA_DB4_DIR			(GPIO_OUTPUT << 4U)
#define LCD_DATA_DB5_DIR			(GPIO_OUTPUT << 5U)
#define LCD_DATA_DB6_DIR			(GPIO_OUTPUT << 6U)
#define LCD_DATA_DB7_DIR			(GPIO_OUTPUT << 7U)
/*                 END OF LCD definitions                 */


/*                 TPM0 definitions                 */
/*	Using TPM0 as tachometer pulse counter to measure fan speed*/
#define COUNTER_CLK_SOURCE_OSCERCLK					2U
#define COUNTER_EXTERNAL_CLK_SOURCE 				0U
#define EXTERNAL_CLK_COUNTING						2U
#define PRESCALER_COUNTER							0U
#define TACHOMETER_ALT								4U
#define CLKOUT_SELECT_OSCERCLK						6U
/*                 END OF TPM0 definitions                 */


#endif /* SOURCES_ES670_PERIPHERAL_BOARD_H_ */
