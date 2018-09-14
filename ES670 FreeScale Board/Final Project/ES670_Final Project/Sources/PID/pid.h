/* ***************************************************************** */
/* File name:        heater.h                                        */
/* File description: Header file containing the function/methods     */
/*                   prototypes of pid.c                             */
/* Author name:      PauloFavero e Guilherme Oliveira                */
/* Creation date:    30jun2017                                       */
/* Revision date:    30jun2017                                       */
/* ***************************************************************** */


#ifndef SOURCES_PID_PID_H_
#define SOURCES_PID_PID_H_
#define KP	0
#define KI	1
#define KD	2

typedef struct PID_DATA{
	int Pgain, Dgain, Igain;
	int reference, actuator_value;
	double sensor_value_previous;
	double error_sum;
}PID_DATA;

/* *************************************************** */
/* Method name: 	   pid_pidInit		 		       */
/* Method description: Initialize the pid	 		   */
/* Input params:	   n/a					   		   */
/* Output params:	   n/a 		              		   */
/* *************************************************** */
void pid_pidInit(void);

/* *********************************************************************** */
/* Method name: 	   pid_utUpdate		 		       					   */
/* Method description: Realize the control with pid parameters	 		   */
/* Input params:	   The velocity of cooler(Sensor Value) 			   */
/* 					   and the desired value(Reference Value)   		   */
/* Output params:	   n/a 		              		  					   */
/* *********************************************************************** */
void pid_utUpdate(int iSensor_value, int iReference_value);

/* *********************************************************************** */
/* Method name: 	   pid_gainUpdate		 		       				   */
/* Method description: Realize the update of single pid parameters	  	   */
/* Input params:	   The desired value for P, I or D value 			   */
/* 					   Parameter Gain to set  		 					   */
/* Output params:	   n/a 		              		  					   */
/* *********************************************************************** */
void pid_gainUpdate(int iValue, int iK_choice);

/* *********************************************************************** */
/* Method name: 	   pid_sensorGetValue	 		       				   */
/* Method description: Get the value of cicles of rotation			  	   */
/* Input params:	   n/a												   */
/* 					   						  		 					   */
/* Output params:	   Cicles of Rotation      		  					   */
/* *********************************************************************** */
int pid_sensorGetValue(void);

/* *********************************************************************** */
/* Method name: 	   pid_setReferenceValue 		       				   */
/* Method description: Sets the reference rotation 					  	   */
/* Input params:	   Reference value									   */
/* 					   						  		 					   */
/* Output params:	   n/a				     		  					   */
/* *********************************************************************** */
void pid_setReferenceValue(int iRef);

/* *********************************************************************** */
/* Method name: 	   pid_getPID			 		       				   */
/* Method description: Get the struct of PID controller				  	   */
/* Input params:	   n/a												   */
/* 					   						  		 					   */
/* Output params:	   PID Controller	     		  					   */
/* *********************************************************************** */
PID_DATA pid_getPID(void);



#endif /* SOURCES_PID_PID_H_ */
