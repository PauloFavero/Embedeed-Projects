
/* *****************************************************************   */
/* File name:        timer_counter.c                                   */
/* File description: This file has a couple of useful functions to     */
/*                   control the cooler with PWM from peripheral board */
/* Author name:      PauloFavero                                       */
/* Creation date:    17jmay2017                                        */
/* Revision date:    17may2017                                         */
/* *****************************************************************   */

#include "TimerCooler/timer_counter.h"
#include "ES670/es670_peripheral_board.h"
#include "fsl_tpm_hal.h"




/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 			      		   	  */
/* Outpu params:	   n/a 		              		  */
/* ************************************************** */
void timer_initTPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1

	TPM1_SC |= TPM_SC_CPWMS(LPTPM_CNT_UP);   //up counting mode
	TPM1_SC |= TPM_SC_CMOD(LPTPM_CLK_MOD1);   //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |= TPM_SC_PS(LPTPM_SET_PS_1);   //Prescale 1:1

	TPM1_C1SC |= LPTPM_PWM_MASK;

	// Zera o valor do contador
	TPM1_CNT = 0;

	TPM1_MOD = 100;

}

/* ***************************************************  */
/* Method name: 	   timer_setCooler       		    */
/* Method description: Set the velocity in cooler fan   */
/* Input params:	   Velocity desired     			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/
void timer_setCooler(int iVelocity)
{
	TPM1_C1V = iVelocity;
}


/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerFanInit(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as PWM */
    PORTA_PCR13 |= PORT_PCR_MUX(0b011);

}
//void timer_setDutyCycle(int iDuty){
//	//Seta o m�dulo m�ximo do pwm
//		TPM1_MOD = iDuty;
//}
