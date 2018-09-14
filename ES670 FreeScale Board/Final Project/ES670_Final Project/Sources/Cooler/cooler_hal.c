/* ***************************************************************** */
/* File name:        cooler_hal.c                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control the cooler from peripheral board        */
/* Author name:      PauloFavero                                     */
/* Creation date:    17jmay2017                                      */
/* Revision date:    17may2017                                       */
/* ***************************************************************** */

#include "Cooler/cooler_hal.h"
#include "ES670/es670_peripheral_board.h"


/* ********************************************************************** */
/* Method name:        cooler_initCooler                                 */
/* Method description: Initialize the cooler as GPIO in maximum rotation  */
/* Input params:       n/a                          					  */
/* Output params:      n/a                          					  */
/* ********************************************************************** */
void cooler_initCooler(void){


		//Ativa o clock da PTA cooler
		SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

		//portas do cooler
		PORTA_PCR13 |= PORT_PCR_MUX(CS_ALT);
		GPIOA_PDDR |= GPIO_PDDR_PDD(CS_DIR_OUTPUT);
		GPIOA_PSOR |= GPIO_PSOR_PTSO(CS_SET_OUTPUT);

}
