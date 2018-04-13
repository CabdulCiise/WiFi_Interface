
#include "msp.h"
#include "regs.h"

#ifndef HW_HW_H_
#define HW_HW_H_

/*  TEMPLATE
#define _PORT_NAME               1
#define _PORT_PIN_NUM            0
#define _ASSERT_VALUE            1
#define _BIT                     _BV(_PORT_PIN_NUM)
#define _P_IN                    CONCAT3(P,_PORT_NAME,IN)
#define _P_OUT                   CONCAT3(P,_PORT_NAME,OUT)
#define _P_DIR                   CONCAT3(P,_PORT_NAME,DIR)
#define _P_REN                   CONCAT3(P,_PORT_NAME,REN)
#define _P_SEL0                  CONCAT3(P,_PORT_NAME,SEL0)
#define _P_SEL1                  CONCAT3(P,_PORT_NAME,SEL1)
#define _P_SELC                  CONCAT3(P,_PORT_NAME,SELC)
#define _P_IES                   CONCAT3(P,_PORT_NAME,IES)
#define _P_IE                    CONCAT3(P,_PORT_NAME,IE)
#define _P_IFG                   CONCAT3(P,_PORT_NAME,IFG)
 */

// *****        GPIO CONNECTIONS     *****
#define LED_PORT_NAME               1
#define LED_PORT_PIN_NUM            0
#define LED_ASSERT_VALUE            1
#define LED_BIT                     _BV(LED_PORT_PIN_NUM)
#define LED_P_IN                    CONCAT3(P,LED_PORT_NAME,IN)
#define LED_P_OUT                   CONCAT3(P,LED_PORT_NAME,OUT)
#define LED_P_DIR                   CONCAT3(P,LED_PORT_NAME,DIR)
#define LED_P_REN                   CONCAT3(P,LED_PORT_NAME,REN)
#define LED_P_SEL0                  CONCAT3(P,LED_PORT_NAME,SEL0)
#define LED_P_SEL1                  CONCAT3(P,LED_PORT_NAME,SEL1)
#define LED_P_SELC                  CONCAT3(P,LED_PORT_NAME,SELC)
#define LED_P_IES                   CONCAT3(P,LED_PORT_NAME,IES)
#define LED_P_IE                    CONCAT3(P,LED_PORT_NAME,IE)
#define LED_P_IFG                   CONCAT3(P,LED_PORT_NAME,IFG)

#define LEDR_PORT_NAME               2
#define LEDR_PORT_PIN_NUM            0
#define LEDR_ASSERT_VALUE            1
#define LEDR_BIT                     _BV(LEDR_PORT_PIN_NUM)
#define LEDR_P_IN                    CONCAT3(P,LEDR_PORT_NAME,IN)
#define LEDR_P_OUT                   CONCAT3(P,LEDR_PORT_NAME,OUT)
#define LEDR_P_DIR                   CONCAT3(P,LEDR_PORT_NAME,DIR)
#define LEDR_P_REN                   CONCAT3(P,LEDR_PORT_NAME,REN)
#define LEDR_P_SEL0                  CONCAT3(P,LEDR_PORT_NAME,SEL0)
#define LEDR_P_SEL1                  CONCAT3(P,LEDR_PORT_NAME,SEL1)
#define LEDR_P_SELC                  CONCAT3(P,LEDR_PORT_NAME,SELC)
#define LEDR_P_IES                   CONCAT3(P,LEDR_PORT_NAME,IES)
#define LEDR_P_IE                    CONCAT3(P,LEDR_PORT_NAME,IE)
#define LEDR_P_IFG                   CONCAT3(P,LEDR_PORT_NAME,IFG)

#define LEDG_PORT_NAME               2
#define LEDG_PORT_PIN_NUM            1
#define LEDG_ASSERT_VALUE            1
#define LEDG_BIT                     _BV(LEDG_PORT_PIN_NUM)
#define LEDG_P_IN                    CONCAT3(P,LEDG_PORT_NAME,IN)
#define LEDG_P_OUT                   CONCAT3(P,LEDG_PORT_NAME,OUT)
#define LEDG_P_DIR                   CONCAT3(P,LEDG_PORT_NAME,DIR)
#define LEDG_P_REN                   CONCAT3(P,LEDG_PORT_NAME,REN)
#define LEDG_P_SEL0                  CONCAT3(P,LEDG_PORT_NAME,SEL0)
#define LEDG_P_SEL1                  CONCAT3(P,LEDG_PORT_NAME,SEL1)
#define LEDG_P_SELC                  CONCAT3(P,LEDG_PORT_NAME,SELC)
#define LEDG_P_IES                   CONCAT3(P,LEDG_PORT_NAME,IES)
#define LEDG_P_IE                    CONCAT3(P,LEDG_PORT_NAME,IE)
#define LEDG_P_IFG                   CONCAT3(P,LEDG_PORT_NAME,IFG)

#define LEDB_PORT_NAME               2
#define LEDB_PORT_PIN_NUM            2
#define LEDB_ASSERT_VALUE            1
#define LEDB_BIT                     _BV(LEDB_PORT_PIN_NUM)
#define LEDB_P_IN                    CONCAT3(P,LEDB_PORT_NAME,IN)
#define LEDB_P_OUT                   CONCAT3(P,LEDB_PORT_NAME,OUT)
#define LEDB_P_DIR                   CONCAT3(P,LEDB_PORT_NAME,DIR)
#define LEDB_P_REN                   CONCAT3(P,LEDB_PORT_NAME,REN)
#define LEDB_P_SEL0                  CONCAT3(P,LEDB_PORT_NAME,SEL0)
#define LEDB_P_SEL1                  CONCAT3(P,LEDB_PORT_NAME,SEL1)
#define LEDB_P_SELC                  CONCAT3(P,LEDB_PORT_NAME,SELC)
#define LEDB_P_IES                   CONCAT3(P,LEDB_PORT_NAME,IES)
#define LEDB_P_IE                    CONCAT3(P,LEDB_PORT_NAME,IE)
#define LEDB_P_IFG                   CONCAT3(P,LEDB_PORT_NAME,IFG)

#define PB1_PORT_NAME               1
#define PB1_PORT_PIN_NUM            1
#define PB1_ASSERT_VALUE            1
#define PB1_BIT                     _BV(PB1_PORT_PIN_NUM)
#define PB1_P_IN                    CONCAT3(P,PB1_PORT_NAME,IN)
#define PB1_P_OUT                   CONCAT3(P,PB1_PORT_NAME,OUT)
#define PB1_P_DIR                   CONCAT3(P,PB1_PORT_NAME,DIR)
#define PB1_P_REN                   CONCAT3(P,PB1_PORT_NAME,REN)
#define PB1_P_SEL0                  CONCAT3(P,PB1_PORT_NAME,SEL0)
#define PB1_P_SEL1                  CONCAT3(P,PB1_PORT_NAME,SEL1)
#define PB1_P_SELC                  CONCAT3(P,PB1_PORT_NAME,SELC)
#define PB1_P_IES                   CONCAT3(P,PB1_PORT_NAME,IES)
#define PB1_P_IE                    CONCAT3(P,PB1_PORT_NAME,IE)
#define PB1_P_IFG                   CONCAT3(P,PB1_PORT_NAME,IFG)

#define PB2_PORT_NAME               1
#define PB2_PORT_PIN_NUM            4
#define PB2_ASSERT_VALUE            1
#define PB2_BIT                     _BV(PB2_PORT_PIN_NUM)
#define PB2_P_IN                    CONCAT3(P,PB2_PORT_NAME,IN)
#define PB2_P_OUT                   CONCAT3(P,PB2_PORT_NAME,OUT)
#define PB2_P_DIR                   CONCAT3(P,PB2_PORT_NAME,DIR)
#define PB2_P_REN                   CONCAT3(P,PB2_PORT_NAME,REN)
#define PB2_P_SEL0                  CONCAT3(P,PB2_PORT_NAME,SEL0)
#define PB2_P_SEL1                  CONCAT3(P,PB2_PORT_NAME,SEL1)
#define PB2_P_SELC                  CONCAT3(P,PB2_PORT_NAME,SELC)
#define PB2_P_IES                   CONCAT3(P,PB2_PORT_NAME,IES)
#define PB2_P_IE                    CONCAT3(P,PB2_PORT_NAME,IE)
#define PB2_P_IFG                   CONCAT3(P,PB2_PORT_NAME,IFG)

#define ROTA_PORT_NAME               2
#define ROTA_PORT_PIN_NUM            5
#define ROTA_ASSERT_VALUE            1
#define ROTA_BIT                     _BV(ROTA_PORT_PIN_NUM)
#define ROTA_P_IN                    CONCAT3(P,ROTA_PORT_NAME,IN)
#define ROTA_P_OUT                   CONCAT3(P,ROTA_PORT_NAME,OUT)
#define ROTA_P_DIR                   CONCAT3(P,ROTA_PORT_NAME,DIR)
#define ROTA_P_REN                   CONCAT3(P,ROTA_PORT_NAME,REN)
#define ROTA_P_SEL0                  CONCAT3(P,ROTA_PORT_NAME,SEL0)
#define ROTA_P_SEL1                  CONCAT3(P,ROTA_PORT_NAME,SEL1)
#define ROTA_P_SELC                  CONCAT3(P,ROTA_PORT_NAME,SELC)
#define ROTA_P_IES                   CONCAT3(P,ROTA_PORT_NAME,IES)
#define ROTA_P_IE                    CONCAT3(P,ROTA_PORT_NAME,IE)
#define ROTA_P_IFG                   CONCAT3(P,ROTA_PORT_NAME,IFG)

#define ROTB_PORT_NAME               2
#define ROTB_PORT_PIN_NUM            6
#define ROTB_ASSERT_VALUE            1
#define ROTB_BIT                     _BV(ROTB_PORT_PIN_NUM)
#define ROTB_P_IN                    CONCAT3(P,ROTB_PORT_NAME,IN)
#define ROTB_P_OUT                   CONCAT3(P,ROTB_PORT_NAME,OUT)
#define ROTB_P_DIR                   CONCAT3(P,ROTB_PORT_NAME,DIR)
#define ROTB_P_REN                   CONCAT3(P,ROTB_PORT_NAME,REN)
#define ROTB_P_SEL0                  CONCAT3(P,ROTB_PORT_NAME,SEL0)
#define ROTB_P_SEL1                  CONCAT3(P,ROTB_PORT_NAME,SEL1)
#define ROTB_P_SELC                  CONCAT3(P,ROTB_PORT_NAME,SELC)
#define ROTB_P_IES                   CONCAT3(P,ROTB_PORT_NAME,IES)
#define ROTB_P_IE                    CONCAT3(P,ROTB_PORT_NAME,IE)
#define ROTB_P_IFG                   CONCAT3(P,ROTB_PORT_NAME,IFG)

#define ROTP_PORT_NAME               2
#define ROTP_PORT_PIN_NUM            4
#define ROTP_ASSERT_VALUE            1
#define ROTP_BIT                     _BV(ROTP_PORT_PIN_NUM)
#define ROTP_P_IN                    CONCAT3(P,ROTP_PORT_NAME,IN)
#define ROTP_P_OUT                   CONCAT3(P,ROTP_PORT_NAME,OUT)
#define ROTP_P_DIR                   CONCAT3(P,ROTP_PORT_NAME,DIR)
#define ROTP_P_REN                   CONCAT3(P,ROTP_PORT_NAME,REN)
#define ROTP_P_SEL0                  CONCAT3(P,ROTP_PORT_NAME,SEL0)
#define ROTP_P_SEL1                  CONCAT3(P,ROTP_PORT_NAME,SEL1)
#define ROTP_P_SELC                  CONCAT3(P,ROTP_PORT_NAME,SELC)
#define ROTP_P_IES                   CONCAT3(P,ROTP_PORT_NAME,IES)
#define ROTP_P_IE                    CONCAT3(P,ROTP_PORT_NAME,IE)
#define ROTP_P_IFG                   CONCAT3(P,ROTP_PORT_NAME,IFG)

#define LCD_DC_PORT_NAME            9
#define LCD_DC_PORT_PIN_NUM         2
#define LCD_DC_ASSERT_VALUE         1
#define LCD_DC_BIT                  _BV(LCD_DC_PORT_PIN_NUM)
#define LCD_DC_P_IN                 CONCAT3(P,LCD_DC_PORT_NAME,IN)
#define LCD_DC_P_OUT                CONCAT3(P,LCD_DC_PORT_NAME,OUT)
#define LCD_DC_P_DIR                CONCAT3(P,LCD_DC_PORT_NAME,DIR)
#define LCD_DC_P_REN                CONCAT3(P,LCD_DC_PORT_NAME,REN)
#define LCD_DC_P_SEL0               CONCAT3(P,LCD_DC_PORT_NAME,SEL0)
#define LCD_DC_P_SEL1               CONCAT3(P,LCD_DC_PORT_NAME,SEL1)
#define LCD_DC_P_SELC               CONCAT3(P,LCD_DC_PORT_NAME,SELC)
#define LCD_DC_P_IES                CONCAT3(P,LCD_DC_PORT_NAME,IES)
#define LCD_DC_P_IE                 CONCAT3(P,LCD_DC_PORT_NAME,IE)
#define LCD_DC_P_IFG                CONCAT3(P,LCD_DC_PORT_NAME,IFG)

#define LCD_RESET_PORT_NAME         9
#define LCD_RESET_PORT_PIN_NUM      3
#define LCD_RESET_ASSERT_VALUE      1
#define LCD_RESET_BIT               _BV(LCD_RESET_PORT_PIN_NUM)
#define LCD_RESET_P_IN              CONCAT3(P,LCD_RESET_PORT_NAME,IN)
#define LCD_RESET_P_OUT             CONCAT3(P,LCD_RESET_PORT_NAME,OUT)
#define LCD_RESET_P_DIR             CONCAT3(P,LCD_RESET_PORT_NAME,DIR)
#define LCD_RESET_P_REN             CONCAT3(P,LCD_RESET_PORT_NAME,REN)
#define LCD_RESET_P_SEL0            CONCAT3(P,LCD_RESET_PORT_NAME,SEL0)
#define LCD_RESET_P_SEL1            CONCAT3(P,LCD_RESET_PORT_NAME,SEL1)
#define LCD_RESET_P_SELC            CONCAT3(P,LCD_RESET_PORT_NAME,SELC)
#define LCD_RESET_P_IES             CONCAT3(P,LCD_RESET_PORT_NAME,IES)
#define LCD_RESET_P_IE              CONCAT3(P,LCD_RESET_PORT_NAME,IE)
#define LCD_RESET_P_IFG             CONCAT3(P,LCD_RESET_PORT_NAME,IFG)

#define LCD_CS_PORT_NAME               9
#define LCD_CS_PORT_PIN_NUM            4
#define LCD_CS_ASSERT_VALUE            1
#define LCD_CS_BIT                     _BV(LCD_CS_PORT_PIN_NUM)
#define LCD_CS_P_IN                    CONCAT3(P,LCD_CS_PORT_NAME,IN)
#define LCD_CS_P_OUT                   CONCAT3(P,LCD_CS_PORT_NAME,OUT)
#define LCD_CS_P_DIR                   CONCAT3(P,LCD_CS_PORT_NAME,DIR)
#define LCD_CS_P_REN                   CONCAT3(P,LCD_CS_PORT_NAME,REN)
#define LCD_CS_P_SEL0                  CONCAT3(P,LCD_CS_PORT_NAME,SEL0)
#define LCD_CS_P_SEL1                  CONCAT3(P,LCD_CS_PORT_NAME,SEL1)
#define LCD_CS_P_SELC                  CONCAT3(P,LCD_CS_PORT_NAME,SELC)
#define LCD_CS_P_IES                   CONCAT3(P,LCD_CS_PORT_NAME,IES)
#define LCD_CS_P_IE                    CONCAT3(P,LCD_CS_PORT_NAME,IE)
#define LCD_CS_P_IFG                   CONCAT3(P,LCD_CS_PORT_NAME,IFG)


// *****        SPI CONNECTIONS     *****
#define LCD_SOMI_PORT_NAME          9
#define LCD_SOMI_PORT_PIN_NUM       6
#define LCD_SOMI_ASSERT_VALUE       1
#define LCD_SOMI_BIT                _BV(LCD_SOMI_PORT_PIN_NUM)
#define LCD_SOMI_P_IN               CONCAT3(P,LCD_SOMI_PORT_NAME,IN)
#define LCD_SOMI_P_OUT              CONCAT3(P,LCD_SOMI_PORT_NAME,OUT)
#define LCD_SOMI_P_DIR              CONCAT3(P,LCD_SOMI_PORT_NAME,DIR)
#define LCD_SOMI_P_REN              CONCAT3(P,LCD_SOMI_PORT_NAME,REN)
#define LCD_SOMI_P_SEL0             CONCAT3(P,LCD_SOMI_PORT_NAME,SEL0)
#define LCD_SOMI_P_SEL1             CONCAT3(P,LCD_SOMI_PORT_NAME,SEL1)
#define LCD_SOMI_P_SELC             CONCAT3(P,LCD_SOMI_PORT_NAME,SELC)
#define LCD_SOMI_P_IES              CONCAT3(P,LCD_SOMI_PORT_NAME,IES)
#define LCD_SOMI_P_IE               CONCAT3(P,LCD_SOMI_PORT_NAME,IE)
#define LCD_SOMI_P_IFG              CONCAT3(P,LCD_SOMI_PORT_NAME,IFG)

#define LCD_SIMO_PORT_NAME          9
#define LCD_SIMO_PORT_PIN_NUM       7
#define LCD_SIMO_ASSERT_VALUE       1
#define LCD_SIMO_BIT                _BV(LCD_SIMO_PORT_PIN_NUM)
#define LCD_SIMO_P_IN               CONCAT3(P,LCD_SIMO_PORT_NAME,IN)
#define LCD_SIMO_P_OUT              CONCAT3(P,LCD_SIMO_PORT_NAME,OUT)
#define LCD_SIMO_P_DIR              CONCAT3(P,LCD_SIMO_PORT_NAME,DIR)
#define LCD_SIMO_P_REN              CONCAT3(P,LCD_SIMO_PORT_NAME,REN)
#define LCD_SIMO_P_SEL0             CONCAT3(P,LCD_SIMO_PORT_NAME,SEL0)
#define LCD_SIMO_P_SEL1             CONCAT3(P,LCD_SIMO_PORT_NAME,SEL1)
#define LCD_SIMO_P_SELC             CONCAT3(P,LCD_SIMO_PORT_NAME,SELC)
#define LCD_SIMO_P_IES              CONCAT3(P,LCD_SIMO_PORT_NAME,IES)
#define LCD_SIMO_P_IE               CONCAT3(P,LCD_SIMO_PORT_NAME,IE)
#define LCD_SIMO_P_IFG              CONCAT3(P,LCD_SIMO_PORT_NAME,IFG)

#define LCD_SCK_PORT_NAME           9
#define LCD_SCK_PORT_PIN_NUM        5
#define LCD_SCK_ASSERT_VALUE        1
#define LCD_SCK_BIT                 _BV(LCD_SCK_PORT_PIN_NUM)
#define LCD_SCK_P_IN                CONCAT3(P,LCD_SCK_PORT_NAME,IN)
#define LCD_SCK_P_OUT               CONCAT3(P,LCD_SCK_PORT_NAME,OUT)
#define LCD_SCK_P_DIR               CONCAT3(P,LCD_SCK_PORT_NAME,DIR)
#define LCD_SCK_P_REN               CONCAT3(P,LCD_SCK_PORT_NAME,REN)
#define LCD_SCK_P_SEL0              CONCAT3(P,LCD_SCK_PORT_NAME,SEL0)
#define LCD_SCK_P_SEL1              CONCAT3(P,LCD_SCK_PORT_NAME,SEL1)
#define LCD_SCK_P_SELC              CONCAT3(P,LCD_SCK_PORT_NAME,SELC)
#define LCD_SCK_P_IES               CONCAT3(P,LCD_SCK_PORT_NAME,IES)
#define LCD_SCK_P_IE                CONCAT3(P,LCD_SCK_PORT_NAME,IE)
#define LCD_SCK_P_IFG               CONCAT3(P,LCD_SCK_PORT_NAME,IFG)


#endif /* HW_HW_H_ */
