/* ***************************************************************** */
/* File name:        cCmdmachine_hal.h                                */
/* File description: This file has a couple of useful functions to   */
/*                   implement with the state Machine                */
/* Author name:      Guilherme Paulo                                 */
/* Creation date:    28Apr2017                                       */
/* Revision date:    05May2017                                       */
/* ***************************************************************** */

#include "LedSwi/ledswi_hal.h"
#include "Serial/serial_hal.h"
#include "Debuguart/debugUart.h"
#include "Buzzer/buzzer_hal.h"
#include "Util/util.h"
#include "TimerCooler/timer_counter.h"
#include "ES670/es670_peripheral_board.h"
#include "fsl_debug_console.h"
#include "Lcd/lcd_hal.h"
#include "Tachometer/tc_hal.h"
#include "Heater/heater.h"
#include "PID/pid.h"
#include "cmdmachine_hal.h"


/* ***************************************************/
/* Method name:         interpretcCmd                 */
/* Method description:  This Method implement the    */
/* 						state machine        		 */
/* Input params:       ccCmd = command string         */
/* Output params:       n/a                          */
/* ***************************************************/

void cCmdmachine_interpretcCmd(char *ccCmd) {

	int iTime = 0;
	int iFirstDigit=0;
	int iSecondDigit=0;
	int iThirdDigit=0;
	int iVelocity=0;
	int iTempFirstDigit=0;
	int iTempSecondDigit=0;
	int iTempThirdDigit=0;
	int iTemperature=0;
	int iKP,iKI,iKD,iRef=0;



	switch (ccCmd[0]) {
	/* Inicio LED */	
	case 'L':
		switch (ccCmd[1]) {
		case 'C':
			if (ccCmd[2] != '1' && ccCmd[2] != '2' && ccCmd[2] != '3' && ccCmd[2] != '4') {
				serial_sendBuffer("ERROR\r\n");
			} else {
				ledswi_clearLed(ccCmd[2] - '0');
				serial_sendBuffer("ACK\r\n"); // ACK
			}
			break;

		case 'S':
			if (ccCmd[2] != '1' && ccCmd[2] != '2' && ccCmd[2] != '3' && ccCmd[2] != '4') {
				serial_sendBuffer("ERROR\r\n");
			} else {
				ledswi_setLed(ccCmd[2] - '0');
				serial_sendBuffer("ACK\r\n"); // ACK
			}
			break;
		default:
			serial_sendBuffer("ERROR\r\n");
		}

		break;
		/*  Fim LED */

		/* Inicio Switch */
		case 'S':
			if (ccCmd[1] != '1' && ccCmd[1] != '2' && ccCmd[1] != '3' && ccCmd[1] != '4') {
				serial_sendBuffer("ERROR\r\n");
			} else {
				serial_sendBuffer("ACK\r\n");
				ledswi_initLedSwitch(0, 4);
				if (SWITCH_ON == ledswi_getSwitchStatus(ccCmd[1] - '0')) {
					serial_sendBuffer("O\r\n");
				} else {
					serial_sendBuffer("C\r\n");
				}
			}
			ledswi_initLedSwitch(4, 0);
			break;
			/* Fim Switch */

			/* Inicio Buzzer */
		case 'B':
			if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
				iTime += (ccCmd[1] - '0') * 100;
				if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
					iTime += (ccCmd[2] - '0') * 10;
					if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
						serial_sendBuffer("ACK\r\n");
						iTime += (ccCmd[3] - '0');
					} else
						serial_sendBuffer("ERROR\r\n");
				} else
					serial_sendBuffer("ERROR\r\n");
			} else
				serial_sendBuffer("ERROR\r\n");
			break;
			/* Fim Buzzer */

			/* INIT COOLER */

		case 'V':
			if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
				iFirstDigit = (ccCmd[1] - '0')*100;
				if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
					iSecondDigit = (ccCmd[2] - '0') * 10;
					if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
						iThirdDigit = (ccCmd[3] - '0');
						iVelocity=iFirstDigit + iSecondDigit +iThirdDigit;
						timer_setCooler(iVelocity);
						serial_sendBuffer("ACK\r\n");
					}else
						serial_sendBuffer("ERROR\r\n");
				}

				else
					serial_sendBuffer("ERROR\r\n");
			} else
				serial_sendBuffer("ERROR\r\n");

			break;
			/* FIM COOLER*/

			/* INIT HEATER*/
		case 'H':

			if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
				iTempFirstDigit = (ccCmd[1] - '0')*100;
				if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
					iTempSecondDigit = (ccCmd[2] - '0') * 10;
					if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
						iTempThirdDigit = (ccCmd[3] - '0');
						iTemperature=iTempFirstDigit + iTempSecondDigit +iTempThirdDigit;
						heater_setHeater(iTemperature);
						serial_sendBuffer("ACK\r\n");
					}else
						serial_sendBuffer("ERROR\r\n");
				}

				else
					serial_sendBuffer("ERROR\r\n");
			} else
				serial_sendBuffer("ERROR\r\n");

			break;
			/* FIM HEATER*/

			/* INICIO PID P*/
		case 'P':
			if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
				iFirstDigit = (ccCmd[1] - '0')*100;
				if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
					iSecondDigit = (ccCmd[2] - '0') * 10;
					if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
						iThirdDigit = (ccCmd[3] - '0');
						iKP=iFirstDigit + iSecondDigit +iThirdDigit;
						pid_gainUpdate(iKP, KP);
						serial_sendBuffer("ACK\r\n");
					}else
						serial_sendBuffer("ERROR\r\n");
				}

				else
					serial_sendBuffer("ERROR\r\n");
			} else
				serial_sendBuffer("ERROR\r\n");

			break;
			/* FIM PID P*/

			/* INICIO PID I*/
		case 'I':
			if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
				iFirstDigit = (ccCmd[1] - '0')*100;
				if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
					iSecondDigit = (ccCmd[2] - '0') * 10;
					if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
						iThirdDigit = (ccCmd[3] - '0');
						iKI=iFirstDigit + iSecondDigit +iThirdDigit;
						pid_gainUpdate(iKI, KI);
						serial_sendBuffer("ACK\r\n");
					}else
						serial_sendBuffer("ERROR\r\n");
				}

				else
					serial_sendBuffer("ERROR\r\n");
			} else
				serial_sendBuffer("ERROR\r\n");

			break;
			/* FIM PID I*/

			/* INICIO PID D*/
		case 'D':
			if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
				iFirstDigit = (ccCmd[1] - '0')*100;
				if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
					iSecondDigit = (ccCmd[2] - '0') * 10;
					if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
						iThirdDigit = (ccCmd[3] - '0');
						iKD=iFirstDigit + iSecondDigit +iThirdDigit;
						pid_gainUpdate(iKD, KD);
						serial_sendBuffer("ACK\r\n");
					}else
						serial_sendBuffer("ERROR\r\n");
				}

				else
					serial_sendBuffer("ERROR\r\n");
			} else
				serial_sendBuffer("ERROR\r\n");

			break;
			/* FIM PID D*/
			/* INICIO PID D*/
				case 'R':
					if (((ccCmd[1] - '0') >= 0) && ((ccCmd[1] - '0') <= 9)) {
						iFirstDigit = (ccCmd[1] - '0')*100;
						if (((ccCmd[2] - '0') >= 0) && ((ccCmd[2] - '0') <= 9)) {
							iSecondDigit = (ccCmd[2] - '0') * 10;
							if (((ccCmd[3] - '0') >= 0) && ((ccCmd[3] - '0') <= 9)) {
								iThirdDigit = (ccCmd[3] - '0');
								iRef=iFirstDigit + iSecondDigit +iThirdDigit;
								pid_setReferenceValue(iRef);
								serial_sendBuffer("ACK\r\n");
							}else
								serial_sendBuffer("ERROR\r\n");
						}

						else
							serial_sendBuffer("ERROR\r\n");
					} else
						serial_sendBuffer("ERROR\r\n");

					break;
					/* FIM PID D*/

		default:
			serial_sendBuffer("DEFAULT\r\n");
	}
}

