/* ***************************************************************** */
/* File name:        display7seg_hal.c                               */
/* File description: This file has a couple of useful functions to   */
/*                   control the 7 Segments Display                  */
/* Author name:      Guilherme Paulo                                 */
/* Creation date:    31Mar2017                                       */
/* Revision date:    11Maz2017                                       */
/* ***************************************************************** */

/* ************************************************ */
/* Method name:        display7seg_initDisplay7seg  */
/* Method description: Initialize the 7 Segments    */
/*                       Display                    */
/* Input params:       n/a                          */
/* Outpu params:       n/a                          */
/* ************************************************ */
#include "Display7seg/display7seg_hal.h"
#include "ES670/es670_peripheral_board.h"
void display7seg_initDisplay7seg(){

	/* un-gate port clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);

	PORTC_PCR0 = PORT_PCR_MUX(SEG_A_ALT);
	PORTC_PCR1 = PORT_PCR_MUX(SEG_B_ALT);
	PORTC_PCR2 = PORT_PCR_MUX(SEG_C_ALT);
	PORTC_PCR3 = PORT_PCR_MUX(SEG_D_ALT);
	PORTC_PCR4= PORT_PCR_MUX(SEG_E_ALT);
	PORTC_PCR5 = PORT_PCR_MUX(SEG_F_ALT);
	PORTC_PCR6 = PORT_PCR_MUX(SEG_G_ALT);
	PORTC_PCR7 = PORT_PCR_MUX(SEG_DP_ALT);
	PORTC_PCR13 = PORT_PCR_MUX(DISP_1_ALT);
	PORTC_PCR12 = PORT_PCR_MUX(DISP_2_ALT);
	PORTC_PCR11 = PORT_PCR_MUX(DISP_3_ALT);
	PORTC_PCR10 = PORT_PCR_MUX(DISP_4_ALT);


	    GPIOC_PDDR |= GPIO_PDDR_PDD(SEG_A_DIR_OUTPUT|SEG_B_DIR_OUTPUT|SEG_C_DIR_OUTPUT|SEG_D_DIR_OUTPUT| \
	    		SEG_E_DIR_OUTPUT|SEG_F_DIR_OUTPUT|SEG_G_DIR_OUTPUT|SEG_DP_DIR_OUTPUT|DISP_1_DIR_OUTPUT | \
				DISP_2_DIR_OUTPUT | DISP_3_DIR_OUTPUT | DISP_4_DIR_OUTPUT );

}

/* ************************************************ */
/* Method name:        display7seg_setDisplay       */
/* Method description: Set one of the 7 Segments 	*/
/*                    Display with the number    	*/
/*                     in the display in cDisp      */
/* Input params:       cDisp    = which Disp {1..4} */
/*  				   cInfo    = which cInfo {0..9}*/
/* Outpu params:       n/a                          */
/* ************************************************ */

void display7seg_setDisplay(char cDisp, char cInfo) {

	switch (cDisp)
	{
		case 1:
			GPIOC_PSOR = GPIO_PSOR_PTSO (DISP_1_DIR_OUTPUT);
			break;
		case 2:
			GPIOC_PSOR = GPIO_PSOR_PTSO (DISP_2_DIR_OUTPUT);
			break;
		case 3:
			GPIOC_PSOR = GPIO_PSOR_PTSO (DISP_3_DIR_OUTPUT);
			break;
		case 4:
			GPIOC_PSOR = GPIO_PSOR_PTSO (DISP_4_DIR_OUTPUT);
			break;
	}


	switch (cInfo)
	{
	        case 0:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_E_DIR_OUTPUT | SEG_F_DIR_OUTPUT);
	            break;
	        case 1:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT );
	            break;
	        case 2:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_E_DIR_OUTPUT | SEG_G_DIR_OUTPUT );
	            break;
	        case 3:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_G_DIR_OUTPUT  );
	            break;
	        case 4:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT | SEG_F_DIR_OUTPUT |\
	            SEG_G_DIR_OUTPUT );
	            break;
	        case 5:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_F_DIR_OUTPUT | SEG_G_DIR_OUTPUT );
	            break;
	        case 6:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_E_DIR_OUTPUT | SEG_F_DIR_OUTPUT | SEG_G_DIR_OUTPUT );
	            break;
	        case 7:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT );
	            break;
	        case 8:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_E_DIR_OUTPUT | SEG_F_DIR_OUTPUT | SEG_G_DIR_OUTPUT );
	            break;
	        case 9:
	        	GPIOC_PSOR = GPIO_PSOR_PTSO ( SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
	            SEG_D_DIR_OUTPUT | SEG_F_DIR_OUTPUT | SEG_G_DIR_OUTPUT |\
	            SEG_DP_DIR_OUTPUT  );
	            break;
	 }

}

/* ************************************************ */
/* Method name:        ledswi_clearLed              */
/* Method description: Clear all the 7 Segments     */
/* Input params:       								*/
/* Outpu params:       n/a                          */
/* ************************************************ */

void display7seg_clearDisps(){

	GPIOC_PCOR = GPIO_PCOR_PTCO(  SEG_A_DIR_OUTPUT | SEG_B_DIR_OUTPUT | SEG_C_DIR_OUTPUT | \
			SEG_D_DIR_OUTPUT | SEG_E_DIR_OUTPUT | SEG_F_DIR_OUTPUT | SEG_G_DIR_OUTPUT | SEG_DP_DIR_OUTPUT |\
			DISP_1_DIR_OUTPUT | DISP_2_DIR_OUTPUT | DISP_3_DIR_OUTPUT | DISP_4_DIR_OUTPUT);
}
