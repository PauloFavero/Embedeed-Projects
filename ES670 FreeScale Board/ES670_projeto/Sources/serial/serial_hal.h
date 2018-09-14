/* ***************************************************************** */
/* File name:        serial_hal.h                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control the Serial Communication                */
/* Author name:      Guilherme Paulo                                 */
/* Creation date:    28Apr2017                                       */
/* Revision date:    05May2017                                       */
/* ***************************************************************** */

#ifndef SOURCES_SERIAL_HAL_H_
#define SOURCES_SERIAL_HAL_H_
#define BUFF_SIZE 256

/* ********************************************************/
/* Method name:        sendBuffer                         */
/* Method description:  This method sends a string through*/
/* 						the serial port	                  */
/* Input params:       *cmd = vector to be written        */
/* Output params:       n/a                               */
/* ********************************************************/
void serial_sendBuffer(char *cmd);

/* ********************************************************* */
/* Method name:        receiveBuffer                         */
/* Method description: This method receives a string through */
/* 						the serial port	                     */
/* Input params:       *cBuf = vector to be receive data     */
/* Output params:       n/a                                  */
/* ********************************************************* */
void serial_receiveBuffer(char *cBuf);


#endif /* SOURCES_SERIAL_HAL_H_ */
