/* ***************************************************************** */
/* File name:        display7seg_hal.h                               */
/* File description: Header file containing the function/methods     */
/*                   prototypes of display7seg_hal.c                 */
/* Author name:      Guilherme Paulo                                 */
/* Creation date:    31Mar2017                                       */
/* Revision date:    02Apr2017                                       */
/* ***************************************************************** */

#ifndef SOURCES_DISPLAY7SEG_HAL_H_
#define SOURCES_DISPLAY7SEG_HAL_H_


/* ************************************************ */
/* Method name:        display7seg_initDisplay7seg  */
/* Method description: Initialize the hardware 7    */
/*                     Segments Display    			*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void display7seg_initDisplay7seg();

/* ************************************************ */
/* Method name:        display7seg_setDisplay       */
/* Method description: Set one of the 7 Segments 	*/
/*                    Display with the number    	*/
/*                     in the display in cdisp      */
/* Input params:       cdisp, cInfo                 */
/* Output params:      n/a                          */
/* ************************************************ */

void display7seg_setDisplay(char cdisp, char cInfo);

/* ************************************************ */
/* Method name:        display7seg_clearDisps       */
/* Method description: Clear all the 7 Segments 	*/
/*                     display                      */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */

void display7seg_clearDisps();



#endif /* SOURCES_DISPLAY7SEG_HAL_H_ */
