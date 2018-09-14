/* ***************************************************************** */
/* File name:        adc.h                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of adc.c                      */
/* Author name:      PauloFavero                                     */
/* Creation date:    17jun2017                                      */
/* Revision date:    17jun2017                                       */
/* ***************************************************************** */

#ifndef SOURCES_ADC_ADC_H_
#define SOURCES_ADC_ADC_H_

#define ADC_CONVERTION_DONE				01
#define ADC_CONVERTION_PROCESSING		00


/* ***************************************************  */
/* Method name: 	   adc_initAdc     		   		    */
/* Method description: Initialize the adc      		    */
/* Input params:	   n/a					   			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/

void adc_initAdc();

/* ***************************************************  */
/* Method name: 	   adc_isAdcDone  		   		    */
/* Method description: Verify if conversion is done     */
/* Input params:	   n/a					   			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/

int adc_isAdcDone();

/* ***************************************************  */
/* Method name: 	   adc_startConvertion()  		    */
/* Method description: Initialize the conversion        */
/* Input params:	   n/a					   			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/

void adc_startConvertion();

/* ***************************************************  */
/* Method name: 	   adc_getValue  		   		    */
/* Method description: Returns the conversion value     */
/* Input params:	   n/a					   			*/
/* Outpu params:	   Conversion value        			*/
/* ***************************************************	*/
int adc_getValue();


#endif /* SOURCES_ADC_ADC_H_ */
