/* ***************************************************************** */
/* File name:        pid.h                                        */
/* File description: This file has a couple of useful functions to   */
/*                   set and use the pid from peripheral board       */
/* Author name:      PauloFavero e Guilherme Oliveira                */
/* Creation date:    30jun2017                                       */
/* Revision date:    30jun2017                                       */
/* ***************************************************************** */

#include "PID/PID.h"
//speed sensor
#include "Tachometer/tc_hal.h"

//PID parameters
static PID_DATA pid;

/* *************************************************** */
/* Method name: 	   pid_pidInit		 		       */
/* Method description: Initialize the pid	 		   */
/* Input params:	   n/a					   		   */
/* Output params:	   n/a 		              		   */
/* *************************************************** */
void pid_pidInit(void){
	pid.Pgain = 1;
	pid.Igain = 1;
	pid.Dgain = 0;
	pid.reference = 40;
	pid.actuator_value = 0;
	pid.sensor_value_previous=0;
	pid.error_sum = 0;
}

/* *********************************************************************** */
/* Method name: 	   pid_utUpdate		 		       					   */
/* Method description: Realize the control with pid parameters	 		   */
/* Input params:	   The velocity of cooler(Sensor Value) 			   */
/* 					   and the desired value(Reference Value)   		   */
/* Output params:	   n/a 		              		  					   */
/* *********************************************************************** */
void pid_utUpdate(int iSensor_value, int iReference_value){

	int Pterm, Iterm, Dterm;
	int iError, iDiff;

	//Proportional Gain
	iError = iReference_value - iSensor_value;
	Pterm = pid.Pgain * iError;

	//Integrative Gain
	pid.error_sum += iError; //acumulo do erro
	Iterm = pid.Igain * pid.error_sum;

	//Derivative Gain
	iDiff = pid.sensor_value_previous - iSensor_value;
	pid.sensor_value_previous = iSensor_value;
	Dterm = pid.Dgain * iDiff;

	pid.actuator_value = Pterm + Iterm + Dterm;

	if (pid.actuator_value > 100) //%PWM restriction
		pid.actuator_value = 100;
}

/* *********************************************************************** */
/* Method name: 	   pid_gainUpdate		 		       				   */
/* Method description: Realize the update of single pid parameters	  	   */
/* Input params:	   The desired value for P, I or D value 			   */
/* 					   Parameter Gain to set  		 					   */
/* Output params:	   n/a 		              		  					   */
/* *********************************************************************** */
void pid_gainUpdate(int iValue, int iK_choice){

	if (iK_choice == KP)
		pid.Pgain = iValue;

	if (iK_choice == KI)
		pid.Igain = iValue;

	if (iK_choice == KD)
		pid.Dgain = iValue;
}

/* *********************************************************************** */
/* Method name: 	   pid_sensorGetValue	 		       				   */
/* Method description: Get the value of cicles of rotation			  	   */
/* Input params:	   n/a												   */
/* 					   						  		 					   */
/* Output params:	   Cicles of Rotation      		  					   */
/* *********************************************************************** */
int pid_sensorGetValue(void){
	int iRps;
	iRps = tc_readTachometer();
	return iRps/7; //return rps
}

/* *********************************************************************** */
/* Method name: 	   pid_setReferenceValue 		       				   */
/* Method description: Sets the reference rotation 					  	   */
/* Input params:	   Reference value									   */
/* 					   						  		 					   */
/* Output params:	   n/a				     		  					   */
/* *********************************************************************** */
void pid_setReferenceValue(int iRef){
	pid.reference = iRef;
}

/* *********************************************************************** */
/* Method name: 	   pid_getPID			 		       				   */
/* Method description: Get the struct of PID controller				  	   */
/* Input params:	   n/a												   */
/* 					   						  		 					   */
/* Output params:	   PID Controller	     		  					   */
/* *********************************************************************** */
PID_DATA pid_getPID(void){
	return pid;
}


