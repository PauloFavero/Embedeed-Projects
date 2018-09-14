/* ***************************************************************** */
/* File name:        heater.c                                        */
/* File description: This file has a couple of useful functions to   */
/*                   set and use the heater from peripheral board    */
/* Author name:      PauloFavero                                     */
/* Creation date:    17jun2017                                       */
/* Revision date:    17jun2017                                       */
/* ***************************************************************** */

#include "ES670/es670_peripheral_board.h"

/* *************************************************** */
/* Method name: 	   heater_initHeater  		       */
/* Method description: Initialize the heater 		   */
/* Input params:	   Temperature desired     		   */
/* Outpu params:	   n/a 		              		   */
/* *************************************************** */
	void heater_initHeater(){

		SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

		heater_initTPM1AsPWM();


	}

	/* ******************************************************* */
	/* Method name: 	   heater_initTPM1AsPWM   		       */
	/* Method description: Initialize the heater with PWM sinal*/
	/* Input params:	   Temperature desired     			   */
	/* Outpu params:	   n/a 		              			   */
	/* ******************************************************* */
	void heater_initTPM1AsPWM(void)
	{
		/* un-gate port clock*/
		SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1

		PORTA_PCR12 |= PORT_PCR_MUX(0X03);

		TPM1_SC |= TPM_SC_CPWMS(LPTPM_CNT_UP);   //up counting mode
		TPM1_SC |= TPM_SC_CMOD(LPTPM_CLK_MOD1);   //LPTPM Counter increments on every LPTPM counter clock
		TPM1_SC |= TPM_SC_PS(LPTPM_SET_PS_1);   //Prescale 1:1

		TPM1_C0SC |= LPTPM_PWM_MASK;

		// Zera o valor do contador
		TPM1_CNT = 0;
		//Seta o m�dulo m�ximo do pwm
		TPM1_MOD = 100;
	}

	/* ***************************************************  */
	/* Method name: 	   heater_setHeater      		    */
	/* Method description: Set the temperature in the heater*/
	/* Input params:	   Temperature desired     			*/
	/* Outpu params:	   n/a 		              			*/
	/* ***************************************************	*/
	void heater_setHeater(int iTemperature)
	{
		TPM1_C0V = iTemperature;
	}
