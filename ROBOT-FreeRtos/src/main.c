#include "main.h"

int CONSIGNE_R = 1000;
int CONSIGNE_L = 1000;
char message_zigBee = 'B';
char aux = 'B';
int modeZigBee = 0;
#define TRUE 1
#define FALSE 0
int init = FALSE;
int selection = 0;
int pos = 0;

// Déclaration des objets synchronisants !! Ne pas oublier de les créer
xSemaphoreHandle xSemaphore = NULL;
xSemaphoreHandle xSemaphore_LCD = NULL;
xSemaphoreHandle xSemaphore_Motor = NULL;
xSemaphoreHandle xSemaphore_Servo = NULL;
xSemaphoreHandle xSemaphore_obstacle = NULL;

enum state_Controle {
	ZIGBEE, DEMONSTRATION, PIXY, IDLE
};

enum state_Controle currentControlState = IDLE;

xQueueHandle qh = NULL;
xQueueHandle qmotor = NULL;
xQueueHandle qSERVO = NULL;
xQueueHandle qobstacle = NULL;
xQueueHandle qLCD = NULL;

struct AMessage {
	char command;
	int data[2];
};

#define BLOCKED 'B'
#define LEFTTURN 'G'
#define RIGHTTURN 'D'
#define FOWARD 'F'
#define BACKWARD 'A'
#define DEFAULT 'N'
#define START 'R'
#define STOP 'S'
#define REPO 'I'
#define ZIG 'Z'
#define COLEUR 'P'
#define DEMO 'C'

int vitL[1000];
int vitR[1000];
char state = FOWARD;

static void task_Vitesse(void *pvParameters) {
	motorLeft_SetDuty(130);
	motorRight_SetDuty(130);

	int i = 0;
	for (;;) {
		//xSemaphoreTake(xSemaphore_Demo,portMAX_DELAY);
		if (i < 1000) {
			vitL[i] = quadEncoder_GetSpeedL();
			vitR[i] = quadEncoder_GetSpeedR();
			i++;
		} else {
			int k = 0;
		}
		vTaskDelay(5);
	}
}

static void task_PIXY(void *pvParameters) {
	for (;;) {
		int step = 1;
		uint16_t tablexy[2];
		uint16_t tablewh[2];

		int x = servoLow_Get();
		int y = servoHigh_Get();

		pixyCam_Get(&tablexy, &tablewh);

		if ((tablewh[0] > 10) || (tablewh[1] > 10)) {
			if (tablexy[0] >= 200) { // intervale de x et y = [0, 300]  droit -> gauche et up -> down
				x = x - step;
			} else if (tablexy[0] <= 80) {
				x = x + step;
			}

			if (tablexy[1] >= 200) {
				y = y + step;
			} else if (tablexy[1] <= 80) {
				y = y - step;
			}

			if (x <= 10 || x >= 130)
				x = 70;
			if (y <= 10 || y >= 130)
				y = 70;

			pos = x;
			servoLow_Set(x);
			//servoHigh_Set(y);

		}
		vTaskDelay(10);
	}
}

static void task_Controle(void *pvParameters) {
	struct AMessage ServoMessage;
	struct AMessage MotorMessage;
	struct AMessage obstacleMessage;
	struct AMessage LCDMessage;

	vTaskDelay(10);

	for (;;) {
		vTaskDelay(10);
		message_zigBee = (char) get_msg_uart();

		switch (message_zigBee) {
		case START:			//START
			currentControlState = DEMONSTRATION;
			break;
		case STOP:
			currentControlState = IDLE;
			break;

		case DEMO:
			currentControlState = DEMONSTRATION;
			break;
		case ZIG:
			currentControlState = ZIGBEE;
			break;
		case COLEUR:
			currentControlState = PIXY;
			break;

		default:
			break;
		}
		switch (currentControlState) {
		case DEMONSTRATION:
//			ServoMessage.data[0] = 50;
//			ServoMessage.data[1] = 50;
//			xQueueSend(qSERVO, (void * ) &ServoMessage, 0);
			CONSIGNE_L = 700;
			CONSIGNE_R = 700;
			break;

		case ZIGBEE:
			message_zigBee = (char) get_msg_uart();

			if (message_zigBee == FOWARD) {
				CONSIGNE_R = 1000;
				CONSIGNE_L = 1000;
			} else if (message_zigBee == BACKWARD) {
				CONSIGNE_R = -1000;
				CONSIGNE_L = -1000;
			} else if (message_zigBee == LEFTTURN) {
				CONSIGNE_R = 0;
				CONSIGNE_L = 1000;
			} else if (message_zigBee == RIGHTTURN) {
				CONSIGNE_R = 1000;
				CONSIGNE_L = 0;
			} else if (message_zigBee == BLOCKED || message_zigBee == ZIG) {
				CONSIGNE_R = 0;
				CONSIGNE_L = 0;
			}
			//Regarder comment envoyer la vitesse
			break;
		case PIXY:
			if (pos < 50) {
				CONSIGNE_L = pos * 15;
				CONSIGNE_R = 0;
			} else if (pos < 90 && pos > 70){
				CONSIGNE_L = pos * 6;
				CONSIGNE_R = pos * 6;
			}else {

				CONSIGNE_L = 0;
				CONSIGNE_R = pos * 6;
			}

			break;

		case IDLE:
			CONSIGNE_R = 0;
			CONSIGNE_L = 0;

			break;

		default:

			break;

		}
	}

}

static void task_obstacle(void *pvParameters) {
	int table[2]; // Déclaration d'un tableau de 2 entiers situés à l'adresse table
	struct AMessage ObstacleMessage;
	ObstacleMessage.command = 'F';
	ObstacleMessage.data[0] = 0;
	ObstacleMessage.data[1] = 0;
	int count = 0;
	for (;;) {
		uint16_t distanceLeft;
		uint16_t distanceRight;

		//xQueueReceive(qobstacle, &(ObstacleMessage)2000, portMAX_DELAY);

		char backState = DEFAULT, frontState = DEFAULT;

		captDistIR_Get(table); // table[1] = droit et table[0]  = gauche
		if (count == 0) {
			captDistUS_Measure(CAPT_US_LEFT_ADDRESS);
		}

		if (count == 14) {
			distanceLeft = captDistUS_Get(CAPT_US_LEFT_ADDRESS);
		}
		if (count == 28) {
			captDistUS_Measure(CAPT_US_RIGHT_ADDRESS);
		}
		if (count == 42) {
			distanceRight = captDistUS_Get(CAPT_US_RIGHT_ADDRESS);
		}

		if (distanceLeft < 10 || distanceRight < 10) {
			backState = BLOCKED;
		} else {
			backState = FOWARD;
		}

		// table[1] = droit et table[0]  = gauche
		if (table[0] > 1700 && table[1] > 1700) {
			frontState = BLOCKED;
		} else if (table[0] < 1700 && table[1] > 1700) {
			frontState = RIGHTTURN;
		} else if (table[0] > 1700 && table[1] < 1700) {
			frontState = LEFTTURN;
		} else {
			frontState = FOWARD;
		}

		if (frontState == FOWARD
				&& (backState == FOWARD || backState == BLOCKED)) {
			ObstacleMessage.data[0] = CONSIGNE_L;
			ObstacleMessage.data[1] = CONSIGNE_R;
			state = FOWARD;
		} else if (frontState == BLOCKED && backState == FOWARD) {
			ObstacleMessage.data[0] = -CONSIGNE_L;
			ObstacleMessage.data[1] = -CONSIGNE_R;
			state = BACKWARD;
		} else if (frontState == RIGHTTURN) {
			ObstacleMessage.data[0] = 0;
			ObstacleMessage.data[1] = CONSIGNE_R * 3;
			state = LEFTTURN;
		} else if (frontState == LEFTTURN) {
			ObstacleMessage.data[0] = CONSIGNE_L * 3;
			ObstacleMessage.data[1] = 0;
			state = RIGHTTURN;
		}
		if (count >= 42) {
			count = 0;
		}
		//term_printf("OBSTACLE\n\r");
		xQueueSend(qmotor, (void * ) &ObstacleMessage, portMAX_DELAY);
		count++;

	}

}

static void task_Motor(void *pvParameters) {
	motorLeft_SetDuty(100);
	struct AMessage MotorMessage;
	MotorMessage.command = 'S';
	MotorMessage.data[0] = 0;
	MotorMessage.data[1] = 0;
	//==================================
	// Caracteristiques Syst asservir
	//==================================
	float gainD = 720 / 30;
	float gainL = 750 / 30;
	int to_L = 215, to_R = 235; //Constant de temp de chaque moteur
	//===================================
	int Te = 5; //5ms            // Periode d'echantillonage
	//===================================
	int Cde_max = 100;             // Val max variation de commande
	int Cde_min = -Cde_max;
	//==================================
	// Caracteristiques Correcteur
	//==================================
	float ti_L = 0.1 * to_L, ti_R = 0.1 * to_R;
	;
	float Kp_L = 0.025, Kp_R = 0.025;
	float Ki_L = Te / ti_L, Ki_R = Te / ti_R;

	int consigneLeftSpeed = 0, consigneRightSpeed = 0;
	float glissement = 0.0;
	int mes_left, mes_right;
	int errorL, errorR, commandL = 0, commandR = 0;
	float up_L, up_R, ui_L, ui_R, uiAnt_L = 0, uiAnt_R = 0;
	float gainGlissement = 0.025;

	for (;;) {

		mes_left = quadEncoder_GetSpeedL();
		mes_right = quadEncoder_GetSpeedR();

		glissement = 0.0;
		if (consigneLeftSpeed == consigneRightSpeed) {
			glissement = (mes_left - mes_right) * gainGlissement;
		}

		errorL = consigneLeftSpeed - mes_left + (int) glissement;

		up_L = Kp_L * (float) errorL;
		uiAnt_L += up_L * Ki_L;

		errorR = consigneRightSpeed - mes_right - (int) glissement;
		up_R = Kp_R * (float) errorR;
		uiAnt_R += up_R * Ki_R;

		glissement = 0.0;

//		if ((uiAnt_L > 500.0) || (uiAnt_L < -500.0)) {
//			uiAnt_L = 500.0;
//		}
//		if ((uiAnt_R > 500.0) || (uiAnt_R < -500.0)) {
//			uiAnt_R = 500.0;
//		}

		commandL = (int) (up_L + uiAnt_L);
		commandR = (int) (up_R + uiAnt_R);

		if (xQueueReceive(qmotor, &(MotorMessage), portMAX_DELAY)) {
			if (currentControlState == DEMONSTRATION) {
				consigneLeftSpeed = MotorMessage.data[0];
				consigneRightSpeed = MotorMessage.data[1];
			} else {
				consigneLeftSpeed = CONSIGNE_L;
				consigneRightSpeed = CONSIGNE_R;
			}
		}
		//term_printf("commandL %d mes_left %d commandR %d mes_right %d \r\n",commandL,mes_left, commandR,mes_right);
		motorLeft_SetDuty(100 + commandL);
		motorRight_SetDuty(100 + commandR);
		//term_printf("%d %d \n\r", commandL, commandR);
		vTaskDelay(5);
	}
}

static void task_Servo(void *pvParameters) {

	struct AMessage servoMessage;
	servoMessage.command = 'F';
	int desiredLowServoPos = 0;
	int desiredHighServoPos = 0;
	servoMessage.data[0] = 0;
	servoMessage.data[1] = 0;
	for (;;) {

		if (xQueueReceive(qSERVO, &(servoMessage), portMAX_DELAY)) {
			desiredLowServoPos = servoMessage.data[0];
			desiredHighServoPos = servoMessage.data[1];
		}
		servoHigh_Set(desiredHighServoPos);
		vTaskDelay(20);
		servoLow_Set(desiredLowServoPos);
		vTaskDelay(20);
		//term_printf("SERVO\n\r");
	}
}

static void task_LCD(void *pvParameters) {
	struct AMessage lcdMessage;
	lcdMessage.command = 'F';
	lcdMessage.data[0] = 0;
	lcdMessage.data[1] = 0;
	screenLCD_SetBacklight(200);
	screenLCD_Clear();
	screenLCD_Write("PixyRobo", 16, 0, 0);
	screenLCD_Write("IDLE MODE", 16, 0, 1);
	for (;;) {
		xSemaphoreTake(xSemaphore_LCD, portMAX_DELAY);
		//term_printf("Message %c \n\r", message_zigBee);
		switch (currentControlState) {
		case DEMONSTRATION:			//START
			screenLCD_Write("DEMO MODE", 16, 0, 0);
			screenLCD_Write("PixyRobo", 16, 0, 1);
			break;
		case IDLE:
			screenLCD_Write("IDLE MODE", 16, 0, 0);
			screenLCD_Write("PixyRobo", 16, 0, 1);
			break;
		case ZIGBEE:
			screenLCD_Write("MANUAL MODE", 16, 0, 0);
			screenLCD_Write("   PixyRobo   ", 16, 0, 1);
			break;
		case PIXY:
			screenLCD_Write("PIXY MODE", 16, 0, 0);
			screenLCD_Write("   PixyRobo   ", 16, 0, 1);
			break;

		default:
			break;
		}
		xSemaphoreGive(xSemaphore_LCD);
		vTaskDelay(10);
	}

}

//=========================================================
//        >>>>>>>>>>>>        MAIN        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//=========================================================

int main(void) {
	HAL_Init();
	SystemClock_Config();

	uart2_Init();                        // CABLE
	uart6_Init();                        // ZIGBEE
	i2c1_Init();
	spi1Init();
	pixyCam_Init();                        // Caméra Pixy
	captDistIR_Init();                // Capteurs Infrarouge
	quadEncoder_Init();                // Encodeurs Incrémentaux
	motorCommand_Init();        // Commande des Hacheurs
	servoCommand_Init();        // Commande des Servomoteurs

	HAL_Delay(1000);

	motorLeft_SetDuty(100);
	motorRight_SetDuty(100);

	xTaskCreate(task_Controle, ( signed portCHAR * ) "task Controle",
			512 /* stack size */,NULL, tskIDLE_PRIORITY+6, NULL);
	xTaskCreate(task_Servo, ( signed portCHAR * ) "task Servo",
			512 /* stack size */,NULL, tskIDLE_PRIORITY+2, NULL);
	xTaskCreate(task_Motor, ( signed portCHAR * ) "task Motor",
			512 /* stack size */,NULL, tskIDLE_PRIORITY+5, NULL);
	xTaskCreate(task_obstacle, ( signed portCHAR * ) "task Obstacle",
			512 /* stack size */,NULL, tskIDLE_PRIORITY+6, NULL);
	xTaskCreate(task_LCD, ( signed portCHAR * ) "task LCD",
			512 /* stack size */,NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(task_PIXY, ( signed portCHAR * ) "task PIXY",
			512 /* stack size */,NULL, tskIDLE_PRIORITY+3, NULL);

	vSemaphoreCreateBinary(xSemaphore_Motor);
	vSemaphoreCreateBinary(xSemaphore_LCD);
	vSemaphoreCreateBinary(xSemaphore_obstacle);
	vSemaphoreCreateBinary(xSemaphore_Servo);

	xSemaphoreTake(xSemaphore_Servo, portMAX_DELAY);
	xSemaphoreTake(xSemaphore_Motor, portMAX_DELAY);
	xSemaphoreTake(xSemaphore_obstacle, portMAX_DELAY);
//  xSemaphoreGive(xSemaphore_LCD);

	qh = xQueueCreate(1, sizeof(struct AMessage));
	qmotor = xQueueCreate(1, sizeof(struct AMessage));
	qSERVO = xQueueCreate(1, sizeof(struct AMessage));
	qobstacle = xQueueCreate(1, sizeof(struct AMessage));
	qLCD = xQueueCreate(1, sizeof(struct AMessage));

	vTaskStartScheduler();

	return 0;

}

//=================================================================
// Called if stack overflow during execution
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed char *pcTaskName) {
//term_printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
	for (;;) {
	}
}
//=================================================================
//This function is called by FreeRTOS idle task
extern void vApplicationIdleHook(void) {
}
//=================================================================
// brief This function is called by FreeRTOS each tick
extern void vApplicationTickHook(void) {
//        HAL_IncTick();
}

