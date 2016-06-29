/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Util/util.h"
#include "Sistema/uC_definitions.h"
#include "Sistema/mcg_hal.h"
#include "fsl_debug_console.h"
#include "Componentes/Serial/serial_hal.h"
#include "Componentes/LCD/lcd_hal.h"
#include "Componentes/Timers/tc_hal.h"
#include "Componentes/Acelerometro/acelerometro.h"
#include "Componentes/Bluetooth/uart1.h"
#include "Componentes/Switch_and_Button/switch_hal.h"
#include "Componentes/Switch_and_Button/button_hal.h"
#include "Factory/command_factory.h"
#include "Componentes/TSI/tsi_hal.h"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         		700*1000 /* 500ms*/

/* globals */
volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void cyclicExecuteISR(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}



/* ************************************************ */
/* Method name:        controlInit			        */
/* Method description: initialize control setting   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void controlInit(void)
{
  int i;

  lcd_sendCommand(CMD_CLEAR);
  lcd_setCursor(0,0);
  lcd_writeString("Bem-vindo a");
  lcd_setCursor(1,0);
  lcd_writeString("Shalom RC");

  for(i = 0; i<200; i++)
  {
    util_genDelay10ms();
  }

  lcd_sendCommand(CMD_CLEAR);
  lcd_setCursor(0,0);
  lcd_writeString("Calibre o");
  lcd_setCursor(1,0);
  lcd_writeString("controle");

  while(!button_getButtonStatus());


  lcd_sendCommand(CMD_CLEAR);
  lcd_setCursor(0,0);
  lcd_writeString("Calibrando...");

  acelerometro_calibrate();

  for(i = 0; i<50; i++)
  {
    util_genDelay10ms();
  }

  lcd_sendCommand(CMD_CLEAR);
  lcd_setCursor(0,0);
  lcd_writeString("VAMOS CORRER!!");
}




/* ************************************************ */
/* Method name:        boardInit			        */
/* Method description: initialize peripherals	    */
/*                     components and control 		*/
/* 					   settings		                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void boardInit(void)
{
	mcg_clockInit();
	uart1_init();
	serial_init();
	acelerometro_init();
	tsi_init();
	switch_init();
	lcd_initLcd();

	/* configure cyclic executive interruption */
	tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, cyclicExecuteISR);

	acelerometro_calibrate();
	//controlInit();
}


/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
	float fXAcc,fYAcc,fZAcc;
	float fTouch;

  switch_state SwitchStatus = REVERSO;

  char sCommandString[12];
  int iCmdSize = 11;

  /* board initializations */
  boardInit();

	/* cooperative cyclic executive main loop */
  while(1)
  {
 	acelerometro_getData(&fXAcc, &fYAcc, &fZAcc);
    fTouch = tsi_scan();
    SwitchStatus = switch_getSwitchStatus();

    buildCommand(fXAcc, fTouch, SwitchStatus, sCommandString);

    uart1_sendBuffer(sCommandString, iCmdSize);

 	while(!uiFlagNextPeriod);
    uiFlagNextPeriod = 0;
  }

  /* Never leave main */
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
