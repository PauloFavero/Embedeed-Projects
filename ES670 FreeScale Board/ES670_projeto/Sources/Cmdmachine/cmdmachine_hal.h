/* ***************************************************************** */
/* File name:        cmdmachine_hal.h                                */
/* File description: This file has a couple of useful functions to   */
/*                   implement with the state Machine                */
/* Author name:      Guilherme Paulo                                 */
/* Creation date:    28Apr2017                                       */
/* Revision date:    11May2017                                       */
/* ***************************************************************** */


#ifndef SOURCES_CMDMACHINE_HAL_H_
#define SOURCES_CMDMACHINE_HAL_H_

/* ***************************************************/
/* Method name:        cmdmachine_interpretCmd       */
/* Method description: This method read the serial,  */
/*					    interpret and activate one of*/
/*					   the peripheral.				 */
/* Input params:       cCmd = command string         */
/* Output params:       n/a                          */
/* ***************************************************/

void cCmdmachine_interpretcCmd(char *cCmd);


#endif /* SOURCES_CMDMACHINE_HAL_H_ */
