/* ***************************************************************** */
/* File name:        heater.h                                        */
/* File description: Header file containing the function/methods     */
/*                   prototypes of heater.c                          */
/* Author name:      PauloFavero                                     */
/* Creation date:    17jun2017                                       */
/* Revision date:    17jun2017                                       */
/* ***************************************************************** */

#ifndef SOURCES_HEATER_HEATER_H_
#define SOURCES_HEATER_HEATER_H_


/* *************************************************** */
/* Method name: 	   heater_initHeater  		       */
/* Method description: Initialize the heater 		   */
/* Input params:	   n/a                   		   */
/* Outpu params:	   n/a 		              		   */
/* *************************************************** */
void heater_initHeater();

/* ******************************************************* */
/* Method name: 	   heater_initTPM1AsPWM   		       */
/* Method description: Initialize the heater with PWM sinal*/
/* Input params:	   n/a								   */
/* Outpu params:	   n/a 		              			   */
/* ******************************************************* */
void heater_initTPM1AsPWM();

/* ***************************************************  */
/* Method name: 	   heater_setHeater      		    */
/* Method description: Set the temperature in the heater*/
/* Input params:	   Temperature desired     			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/
void heater_setHeater(int iTemperature);


#endif /* SOURCES_HEATER_HEATER_H_ */
