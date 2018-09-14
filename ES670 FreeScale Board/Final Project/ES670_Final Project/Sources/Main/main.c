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

/* ***************************************************************** */
/* File name:        main.c                                          */
/* File description: File dedicated to the ES670 prototype projects  */
/*                   involving the FRDM-KL25Z board together with is */
/*                   daughter board containing more peripherals      */
/*                                                                   */
/*                   Processor MKL25Z128VLK4 characteristics         */
/*                   48 MHz ARM Cortex-M0+ core                      */
/*                   128 KB program flash memory                     */
/*                   16 KB SRAM                                      */
/*                   Voltage range: 1.71 to 3.6 V                    */
/*                                                                   */
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    21may2017                                       */
/* ***************************************************************** */

/* our includes */
#include "ES670/es670_peripheral_board.h"
#include "Buzzer/buzzer_hal.h"
#include "LedSwi/ledswi_hal.h"
#include "Display7seg/display7seg_hal.h"
#include "Lcd/lcd_hal.h"
#include "Mcg/mcg_hal.h"
#include "Tachometer/tc_hal.h"
#include "DebugUart/debugUart.h"
#include "Util/util.h"
#include "Cooler/cooler_hal.h"
#include "TimerCooler/timer_counter.h"
#include "Heater/heater.h"
#include "Adc/Adc.h"
#include "PID/pid.h"
#include "Cmdmachine/cmdmachine_hal.h"

/* system includes */
#include "fsl_debug_console.h"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         300 * 1000 /* 1000000 micro seconds */

/* globals */
volatile unsigned int uiFlagNextPeriod = 0; /* cyclic executive flag */

const unsigned char tabela_temp[256] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,					//15
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,					//31
		1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6,					//47
		7, 7, 8, 8, 8, 8, 9, 9, 10, 10, 10, 10, 11, 11, 12, 12,			//63
		12, 12, 13, 13, 14, 14, 15, 15, 15, 15, 16, 16, 16, 17, 17, 17,	//79
		17, 18, 18, 19, 19, 19, 19, 20, 20, 21, 21, 21, 21, 22, 22, 23,	//95
		23, 24, 24, 24, 24, 25, 25, 26, 26, 26, 26, 27, 27, 28, 28, 28,	//111
		28, 29, 29, 30, 30, 30, 30, 31, 31, 32, 32, 32, 32, 33, 33, 34,	//127
		34, 35, 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 39, 39, 39,	//143
		39, 40, 40, 41, 41, 41, 41, 42, 42, 43, 43, 44, 44, 44, 44, 45,	//159
		45, 46, 46, 46, 46, 47, 47, 48, 48, 48, 48, 49, 49, 50, 50, 50,	//175
		50, 51, 51, 52, 52, 53, 53, 53, 53, 54, 54, 55, 55, 55, 55, 56,	//191
		56, 57, 57, 57, 57, 58, 58, 59, 59, 59, 59, 60, 60, 61, 61, 62,	//207
		62, 62, 62, 63, 63, 64, 64, 64, 64, 65, 65, 66, 66, 66, 66, 67,	//223
		67, 68, 68, 68, 68, 69, 69, 70, 70, 71, 71, 71, 71, 72, 72, 72,	//239
		73, 73, 73, 73, 74, 74, 75, 75, 75, 75, 76, 76, 77, 77, 77, 77	//255
};


/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_cyclicExecuteIsr(void) {
	/* set the cyclic executive flag */
	uiFlagNextPeriod = 1;
}

/* ************************************************ */
/* Method name:        main_boardInit               */
/* Method description: Initialize the board         */
/*                     peripheral units             */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_boardInit(void) {

	mcg_clockInit();
	debugUart_init();
	timer_coolerFanInit();
	ledswi_initLedSwitch(2, 2);
	buzzer_init();
	display7seg_initDisplay7seg();
	lcd_initLcd();
	tc_initTachometer();
	timer_initTPM1AsPWM();
	adc_initAdc();
	//cooler_initCooler();
	heater_initHeater();
	pid_pidInit();


}

/* **************************************************** */
/* Method name:        showScreen                   	*/
/* Method description: Shows in the lcd the pid         */
/* 					   parameters  and velocity cooler	*/
/* Input params:       n/a							 	*/
/* Output params:      n/a                          	*/
/* ************************************************ 	*/
void main_showScreen(void){

	PID_DATA pid_data = pid_getPID();

	lcd_sendCommand(CMD_CLEAR);

	//shows the proportional(PID) gain into the LCD display
	lcd_setCursor(0,0);
	lcd_writeString("P ");
	tc_calculateRps(pid_data.Pgain);



	//shows the integrative(PID) gain into the LCD display
	lcd_setCursor(0,5);
	lcd_writeString("I ");
	tc_calculateRps(pid_data.Igain);



	//shows the derivative(PID) gain into the LCD display
	lcd_setCursor(0,10);
	lcd_writeString("D ");
	tc_calculateRps(pid_data.Dgain);



	//shows the speed reference
	lcd_setCursor(1,0);
	lcd_writeString("ref= ");
	tc_calculateRps(pid_data.reference);

	lcd_setCursor(1,7);
	//shows the actual speed of the cooler
	lcd_writeString("vel= ");
	tc_calculateRps(tc_readTachometer()/(7*0.3));




}

/* ************************************************ */
/* Method name:        writeVelocity                */
/* Method description: Write the velocity and       */
/* 						duty cicle on lcd           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_writeTemperature(void){

	int iTemperature;

	lcd_sendCommand(CMD_CLEAR);
	lcd_setCursor(0, 0);
	lcd_writeString("Temp = ");
	iTemperature = adc_getValue();
	tc_calculateRps(tabela_temp[iTemperature]);
	lcd_setCursor(1, 0);
	lcd_writeString("Indice = ");
	tc_calculateRps(iTemperature);

}


/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void) {
	/* board initializations */
	main_boardInit();

	PID_DATA pid_data;
	int iSensor_value, iActuator_value, iReference_value;

	int count = 0;

	char *cCommand[4];
	/* configure cyclic executive interruption */
	tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

	/* cooperative cyclic executive main loop */
	while (1U) {
		//get PID controller parameters
		pid_data = pid_getPID();
		iReference_value = pid_data.reference;

		//get speed value [rps]
		iSensor_value = pid_sensorGetValue()/0.3  ;

		pid_utUpdate(iSensor_value, iReference_value);
		pid_data = pid_getPID();

		iActuator_value = pid_data.actuator_value;

		//timer_setDutyCycle(actuator_value);
		timer_setCooler(iActuator_value);

		main_showScreen();
		tc_clearTachometer();

		/* task/function code goes here */
		if(UART0_BRD_S1_RDRF(UART0)){
			serial_receiveBuffer(cCommand);
			cCmdmachine_interpretcCmd(cCommand);

		}

		/* WAIT FOR CYCLIC EXECUTIVE PERIOD */
		while (!uiFlagNextPeriod);
		uiFlagNextPeriod = 0;

	}

	/* Never leave main */
	return 0;
}

