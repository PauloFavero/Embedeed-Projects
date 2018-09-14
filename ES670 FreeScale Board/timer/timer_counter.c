#include "KL25Z/es670_peripheral_board.h"
#include "fsl_tpm_hal.h"

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM        */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 		              */
/* ************************************************** */
void timer_initTPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= ??; //Enable clock for TPM1

	TPM1_SC |= ??;   //up counting mode
	TPM1_SC |= ??;   //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |= ??;   //Prescale 1:1

	TPM1_C1SC |= ??;

	TPM1_CNT = ??;
	TPM1_MOD = ??; 
	TPM1_C1V = ??; //PWM 100%
//	TPM1_C1V = ??; //PWM 75% 
//	TPM1_C1V = ??; //PWM 50% 
//	TPM1_C1V = ??; //PWM 25% 
//	TPM1_C1V = ??; //PWM 0%  


}

/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerfan_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as PWM */
    PORTA_PCR13 |= ??;

}

