/* ***************************************************************** */
/* File name:        es670_peripheral_board.h                        */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_ES670_PERIPHERAL_BOARD_H_
#define SOURCES_ES670_PERIPHERAL_BOARD_H_

/* system includes */
#include <MKL25Z4.h>
#include <fsl_gpio_hal.h>

/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U


/*                 END OF General uC definitions         */


/*                 BUZZER Definitions                    */
#define BUZZER_PORT_BASE_PNT        PORTD                                   /* peripheral port base pointer */
#define BUZZER_GPIO_BASE_PNT        PTD                                     /* peripheral gpio base pointer */

#define BUZZER_PIN                  1U                                      /* buzzer pin */
#define BUZZER_DIR                  kGpioDigitalOutput
#define BUZZER_ALT                  0x01u
/*                 END OF BUZZER definitions             */


/*                 LED and SWITCH Definitions                    */
#define LS_PORT_BASE_PNT            PORTA                                   /* peripheral port base pointer */
#define LS_GPIO_BASE_PNT            PTA                                     /* peripheral gpio base pointer */

/* THIS PIN CONFLICTS WITH PTA1 USED AS UART0_RX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS1_PIN                     1U                                      /* led/switch #1 pin */
#define LS1_DIR_OUTPUT              (GPIO_OUTPUT << LS1_PIN)
#define LS1_DIR_INPUT               (GPIO_OUTPUT << LS1_PIN)
#define LS1_ALT                     0x01u                                   /* GPIO alternative */

/* THIS PIN CONFLICTS WITH PTA2 USED AS UART0_TX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS2_PIN                     2U                                      /* led/switch #2 pin */
#define LS2_DIR_OUTPUT              (GPIO_OUTPUT << LS2_PIN)
#define LS2_DIR_INPUT               (GPIO_OUTPUT << LS2_PIN)
#define LS2_ALT                     LS1_ALT

#define LS3_PIN                     4U                                      /* led/switch #3 pin */
#define LS3_DIR_OUTPUT              (GPIO_OUTPUT << LS3_PIN)
#define LS3_DIR_INPUT               (GPIO_OUTPUT << LS3_PIN)
#define LS3_ALT                     LS1_ALT

#define LS4_PIN                     5U                                      /* led/switch #4 pin */
#define LS4_DIR_OUTPUT              (GPIO_OUTPUT << LS4_PIN)
#define LS4_DIR_INPUT               (GPIO_OUTPUT << LS4_PIN)
#define LS4_ALT                     LS1_ALT

/*                 END OF LED and SWITCH definitions             */

/*                   7 Segments Display Definitions              */

#define SEG7_PORT_BASE_PNT            PORTC                                   /* peripheral port base pointer */
#define SEG7_GPIO_BASE_PNT            PTC                                     /* peripheral gpio base pointer */


#define SEG_A_PIN                   0U
#define SEG_A_ALT                   0x01u
#define SEG_A_DIR_OUTPUT            (GPIO_OUTPUT << SEG_A_PIN)

#define SEG_B_PIN                   1U
#define SEG_B_ALT                   SEG_A_ALT
#define SEG_B_DIR_OUTPUT            (GPIO_OUTPUT << SEG_B_PIN)

#define SEG_C_PIN                   2U
#define SEG_C_ALT                   SEG_A_ALT
#define SEG_C_DIR_OUTPUT            (GPIO_OUTPUT << SEG_C_PIN)

#define SEG_D_PIN                   3U
#define SEG_D_ALT                   SEG_A_ALT
#define SEG_D_DIR_OUTPUT            (GPIO_OUTPUT << SEG_D_PIN)

#define SEG_E_PIN                   4U
#define SEG_E_ALT                   SEG_A_ALT
#define SEG_E_DIR_OUTPUT            (GPIO_OUTPUT << SEG_E_PIN)

#define SEG_F_PIN                   5U
#define SEG_F_ALT                   SEG_A_ALT
#define SEG_F_DIR_OUTPUT            (GPIO_OUTPUT << SEG_F_PIN)

#define SEG_G_PIN                   6U
#define SEG_G_ALT                   SEG_A_ALT
#define SEG_G_DIR_OUTPUT            (GPIO_OUTPUT << SEG_G_PIN)

#define SEG_DP_PIN                  7U
#define SEG_DP_ALT                  SEG_A_ALT
#define SEG_DP_DIR_OUTPUT           (GPIO_OUTPUT << SEG_DP_PIN)

#define DISP_1_PIN                  13U
#define DISP_1_ALT                  SEG_A_ALT
#define DISP_1_DIR_OUTPUT           (GPIO_OUTPUT << DISP_1_PIN)

#define DISP_2_PIN                  12U
#define DISP_2_ALT                  SEG_A_ALT
#define DISP_2_DIR_OUTPUT           (GPIO_OUTPUT << DISP_2_PIN)

#define DISP_3_PIN                  11U
#define DISP_3_ALT                  SEG_A_ALT
#define DISP_3_DIR_OUTPUT           (GPIO_OUTPUT << DISP_3_PIN)

#define DISP_4_PIN                  10U
#define DISP_4_ALT                  SEG_A_ALT
#define DISP_4_DIR_OUTPUT           (GPIO_OUTPUT << DISP_4_PIN)


/*                END 7 Segments Display Definitions             */

/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8U                                      /* register selector */
#define LCD_RS_DIR                  1u
#define LCD_RS_ALT                  1u

#define LCD_ENABLE_PIN              9U                                      /* enable pin */
#define LCD_ENABLE_DIR              1u
#define LCD_ENABLE_ALT              1u

#define LCD_RS_HIGH                 1U
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  0U
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U

#define LCD_DATA_DIR                1u                      /* LCD data pins */
#define LCD_DATA_ALT                1u

#define LCD_DATA_DB0_PIN            0u
#define LCD_DATA_DB0_ALT			0x01u
#define LCD_DATA_DB0_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB0_PIN)

#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB1_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB1_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB1_PIN)

#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB2_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB2_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB2_PIN)

#define LCD_DATA_DB3_PIN            3U
#define LCD_DATA_DB3_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB3_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB3_PIN)

#define LCD_DATA_DB4_PIN            4U
#define LCD_DATA_DB4_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB4_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB4_PIN)

#define LCD_DATA_DB5_PIN            5U
#define LCD_DATA_DB5_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB5_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB5_PIN)

#define LCD_DATA_DB6_PIN            6U
#define LCD_DATA_DB6_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB6_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB6_PIN)

#define LCD_DATA_DB7_PIN            7U
#define LCD_DATA_DB7_ALT			LCD_DATA_DB0_ALT
#define LCD_DATA_DB7_DIR_OUTPUT		(LCD_DATA_DIR<<LCD_DATA_DB7_PIN)

/*                 END OF LCD definitions                 */

/*					Cooler Definitions									*/

#define	 CS_PIN						13U
#define  CS_DIR_OUTPUT				(GPIO_OUTPUT << CS_PIN)
#define  CS_ALT                     0x1u
#define  CS_SET_OUTPUT				(CS_ALT << CS_PIN)


/*					END Cooler Definitions							   */

/*					Tachometer Definitions							   */

#define FTM_CLKIN0					4U
#define TPM0CLKSEL					0x00u
#define SET_PS_1					0U // Divide by 1
#define COUNT_RES_EDG				2U // LPTM counter increments on rising edge of LPTPM_EXTCLK
#define TPMSRC_OSCERCLK				0b10


/*					END of Tachometer definitions					   */

/*				Timer Cooler Definition								   */

#define LPTPM_CNT_UP				0U
#define LPTPM_CLK_MOD1				0b01
#define LPTPM_SET_PS_1				0b000
#define LPTPM_PWM_MASK				0b0000000000101000



/*					END Timer Cooler								   */

/*					Adc Definitions									   */


#define ADC_ANALOG				    0U





#endif /* SOURCES_ES670_PERIPHERAL_BOARD_H_ */
