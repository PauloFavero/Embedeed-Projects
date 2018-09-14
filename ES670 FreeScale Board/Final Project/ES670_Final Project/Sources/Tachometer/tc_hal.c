/* File name:        tc_hal.c                                        */
/* File description: This file has a couple of useful functions to   */
/*                   timer and counter hardware abstraction layer    */
/*                                                                   */
/* Author name:      dloubach                                        */
/* Creation date:    23out2015                                       */
/* Revision date:    21may2017                                       */
/* ***************************************************************** */

#include "Tachometer/tc_hal.h"
#include "Lcd/lcd_hal.h"
#include "ES670/es670_peripheral_board.h"

/* system includes */
#include "fsl_lptmr_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"


/* LPTMR configurations */
lptmr_user_config_t lptmrConfig =
{
    .timerMode              = kLptmrTimerModeTimeCounter,
    .freeRunningEnable      = false,
    .prescalerEnable        = true,
    .prescalerClockSource   = kClockLptmrSrcLpoClk,
    .prescalerValue         = kLptmrPrescalerDivide2,
    .isInterruptEnabled     = true,
};

/* LPTMR driver state information */
lptmr_state_t lptmrState;


/* LPTMR IRQ handler that would cover the same name's APIs in startup code */
/* Do not edit this part */
void LPTMR0_IRQHandler(void)
{
    LPTMR_DRV_IRQHandler(0U);
}



/* dummy code for hardware debug purpose */
void tc_testDelaySetup(void)
{
    CLOCK_SYS_EnablePortClock(PORTE_IDX);
    PORT_HAL_SetMuxMode(PORTE, 0u, kPortMuxAsGpio);
    GPIO_HAL_SetPinDir(PTE, 0u, kGpioDigitalOutput);
    GPIO_HAL_ClearPinOutput(PTE, 0u);
}
/* dummy code for hardware debug purpose */
void tc_TestDelay(void)
{
    static char cTest = 0;

    if(!cTest)
        GPIO_HAL_ClearPinOutput(PTE, 0u);
    else
        GPIO_HAL_SetPinOutput(PTE, 0u);

    cTest ^= 1u;
}
/* dummy code for hardware debug purpose */
void tc_lptmrCallBack(void)
{
    tc_TestDelay();
}


/* ************************************************ */
/* Method name:        tc_installLptmr              */
/* Method description: Low power timer 0            */
/*                     initialization and start     */
/* Input params:       uiTimeInUs:                  */
/*                     time in micro seconds        */
/*                     tUserCallback:               */
/*                     function pointer to be called*/
/*                     when counter achieves        */
/*                     uiTimeInUs                   */
/* Output params:      n/a                          */
/* ************************************************ */
void tc_installLptmr0(uint32_t uiTimeInUs, lptmr_callback_t tUserCallback)
{
    /* Initialize LPTMR */
    LPTMR_DRV_Init(LPTMR0_IDX, &lptmrState, &lptmrConfig);

    /* Set timer period for TMR_PERIOD micro seconds */
    LPTMR_DRV_SetTimerPeriodUs(LPTMR0_IDX, uiTimeInUs);

    /* Install interrupt call back function for LPTMR */
    LPTMR_DRV_InstallCallback(LPTMR0_IDX, tUserCallback);

    /* Start LPTMR */
    LPTMR_DRV_Start(LPTMR0_IDX);
}
/* ************************************************ */
/* Method name:        tc_initTachometer            */
/* Method description: Inicialize and set           */
/* 					   the Tachometer               */
/*                   						        */
/* Input params:      n/a						    */
/* Output params:     n/a                           */
/* ************************************************ */
void tc_initTachometer(){

	//Ativa o clock do porta E onde se encontra o TPM
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

	//Ativa o clock da porta TPM0 (bit 24)
	SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED);

	//Seleciona a entrada do canal do tpm como clock externo gerado pelo tacometro (ALT4)
	PORTE_PCR29 |= PORT_PCR_MUX(FTM_CLKIN0);

	//Seleciona o canal do clock utilizado no TPM0 como CLKIN0
	SIM_SOPT4 |= SIM_SOPT4_TPM0CLKSEL(TPM0CLKSEL);

	//set o prescale
	TPM0_SC =TPM_SC_PS(SET_PS_1);

	//Selects LPTM conter clock modes.
		/*
		 * 00 clock disabled
		 * 01 LPTPM counter increments on every LPTPM conter clock
		 * 10 LPTPM counter increments on rising edge of LPTPM_EXTCLK synchornize to the LPTPM  counter clock
		 * 11 reserved
		 */
	TPM0_SC |= TPM_SC_CMOD(COUNT_RES_EDG);

	//Seleciona o clock fonte do TPM counter clock OSCERCLK
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(TPMSRC_OSCERCLK);

}

/* ************************************************ */
/* Method name:        tc_calculateRps              */
/* Method description: Calculate the                */
/* 					  velocity of cooler in RPS     */
/* Input params:      velocity of cooler            */
/* Output params:     n/a                           */
/* ************************************************ */
void tc_calculateRps(int iNum){

    int iTemp,iFactor=1;

    iTemp=iNum;
    while(iTemp > 0){
        iTemp=iTemp/10;
        iFactor = iFactor*10;
    }

    //"Each digits of given number are:
    while(iFactor > 1){
        iFactor = iFactor/10;
        lcd_writeData(48+iNum/iFactor);
        iNum = iNum % iFactor;
    }
}

/* ************************************************ */
/* Method name:        tc_readTachometer            */
/* Method description: Calculate pulses             */
/* 					   generated by cooler          */
/* Input params:      n/a                           */
/* Output params:     TPM0_CNT - Returns the Pulses */
/* ************************************************ */
int tc_readTachometer(void){

	return TPM0_CNT;
}
/* ************************************************ */
/* Method name:        tc_clearTacometer            */
/* Method description: Clear the register, which    */
/* 					   counts the pulses            */
/* Input params:      n/a                           */
/* Output params:     n/a							*/
/* ************************************************ */
void tc_clearTachometer(){


	TPM0_CNT = 0;


}

