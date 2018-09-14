/* ***************************************************************** */
/* File name:        adc.c                                           */
/* File description: This file has a couple of useful functions to   */
/*                   set and use the adc from peripheral board       */
/* Author name:      PauloFavero                                     */
/* Creation date:    17jun2017                                       */
/* Revision date:    17jun2017                                       */
/* ***************************************************************** */
#include "ES670/es670_peripheral_board.h"

/* ***************************************************  */
/* Method name: 	   adc_initAdc     		   		    */
/* Method description: Initialize the adc      		    */
/* Input params:	   n/a					   			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/
void adc_initAdc(){

	//Ativa o clock da PTE cooler
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);

	PORTE_PCR20 |= PORT_PCR_MUX(ADC_ANALOG);
	PORTE_PCR21 |= PORT_PCR_MUX(ADC_ANALOG);


	ADC0_CFG1 |= ADC_CFG1_MODE(00);




}
/* ***************************************************  */
/* Method name: 	   adc_isAdcDone  		   		    */
/* Method description: Verify if conversion is done     */
/* Input params:	   n/a					   			*/
/* Outpu params:	   flag for conversion status 		*/
/* ***************************************************	*/
int adc_isAdcDone(){

	int iAdcStatus = ADC0_SC1A >> 7;

	if(iAdcStatus) // watch complete convertion flag
		{
			return 1; // if the conversion is complete, return 1
		}
		else
			return 0;

}
/* ***************************************************  */
/* Method name: 	   adc_startConvertion()  		    */
/* Method description: Initialize the conversion        */
/* Input params:	   n/a					   			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/
void adc_startConvertion(){

	ADC0_SC1A = ADC_SC1_DIFF(0U)|ADC_SC1_ADCH(0b00100);


}

/* ***************************************************  */
/* Method name: 	   adc_getValue  		   		    */
/* Method description: Returns the conversion value     */
/* Input params:	   n/a					   			*/
/* Outpu params:	   Conversion value        			*/
/* ***************************************************	*/
int adc_getValue(){

	int iResult = ADC0_RA;

	return iResult;

}




