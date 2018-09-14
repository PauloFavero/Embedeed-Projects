/* ***************************************************************** */
/* File name:        serial_hal.c                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control the Serial Communication                */
/* Author name:      Guilherme Paulo                                 */
/* Creation date:    28Apr2017                                       */
/* Revision date:    05May2017                                       */
/* ***************************************************************** */


#include "serial_hal.h"
#include "DebugUart/debugUart.h"
#include "fsl_debug_console.h"
#include "ES670/es670_peripheral_board.h"


/* ********************************************************/
/* Method name:        sendBuffer                         */
/* Method description:  This method sends a string through*/
/* 						the serial port	                  */
/* Input params:       *cmd = vector to be written        */
/* Output params:       n/a                               */
/* ********************************************************/

void serial_sendBuffer(char *cmd){


	for (int i = 0; i< BUFF_SIZE; i++)
	{
		if (0x0A != cmd[i] )
		{
			PUTCHAR(cmd[i]);
		} else
		{
			PUTCHAR(cmd[i]);
			break;
		}

	}

}

/* ********************************************************* */
/* Method name:        receiveBuffer                         */
/* Method description: This method receives a string through */
/* 						the serial port	                     */
/* Input params:       *cBuf = vector to be receive data     */
/* Output params:       n/a                                  */
/* ********************************************************* */

void serial_receiveBuffer(char *cBuf) {
	int i = 0;

	while (i<=3) {
	cBuf[i] = GETCHAR();
	i++;
	}

}
