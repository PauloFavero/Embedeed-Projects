/* ***************************************************************** */
/* File name:        es670.c                                         */
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
/* Revision date:    09mai2017                                       */
/* ***************************************************************** */

/* our includes */
#include "KL25Z/es670_peripheral_board.h"
#include "Buzzer/buzzer_hal.h"
#include "LedSwi/ledswi_hal.h"
#include "Display7seg/display7seg_hal.h"
#include "LedRgb/ledrgb_hal.h"
#include "Lcd/lcd_hal.h"
#include "Util/mcg_hal.h"
#include "Util/tc_hal.h"
#include "Util/debugUart.h"
#include "Util/util.h"
#include "Util/timer_counter.h"

/* system includes */
#include "fsl_debug_console.h"

/* defines *
#define CYCLIC_EXECUTIVE_PERIOD         1000 * 1000 /* 1000000 micro seconds */


/* globals */
volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_cyclicExecuteIsr(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}



/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
    /* board initializations */
    main_boardInit();

    /* configure cyclic executive interruption */
    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

    /* cooperative cyclic executive main loop */
    while(1U)
    {
        /* task/function code goes here */

        /* WAIT FOR CYCLIC EXECUTIVE PERIOD */
        while(!uiFlagNextPeriod);
        uiFlagNextPeriod = 0;
    }

    /* Never leave main */
    return 0;
}
