/* ***************************************************************** */
/* File name:        timer_counter.h                                 */
/* File description: Header file containing the function/methods     */
/*                   prototypes of timer_counter                     */
/* Author name:      PauloFavero                                     */
/* Creation date:    17may2017                                      */
/* Revision date:    17june2017                                       */
/* ***************************************************************** */

#ifndef SOURCES_TIMERCOOLER_TIMER_COUNTER_H_
#define SOURCES_TIMERCOOLER_TIMER_COUNTER_H_


/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 			      		   	  */
/* Outpu params:	   n/a 		              		  */
/* ************************************************** */
void timer_initTPM1AsPWM(void);


/* ***************************************************  */
/* Method name: 	   timer_setCooler       		    */
/* Method description: Set the velocity in cooler fan   */
/* Input params:	   Velocity desired     			*/
/* Outpu params:	   n/a 		              			*/
/* ***************************************************	*/
void timer_setCooler(int iVelocity);

/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerFanInit(void);


#endif /* SOURCES_TIMERCOOLER_TIMER_COUNTER_H_ */
