#include "msp.h"
#include "driverlib.h"

#include "hw.h"

// *****        PRIVATE FUNCTION PROTOTYPES     *****
void INIT_GPIO (void);
void INIT_SPI (void);


// *****        GLOBAL FUNCTIONS       *****
void HAL_STARTUP (void)
{
    // function to initialize ports and pins
    INIT_GPIO();
    INIT_SPI();
}

void assert_LED (void)
{
    #if(LED_ASSERT_VALUE)
        LED_P_OUT |= LED_BIT;
    #else
        LED_P_OUT &= ~LED_BIT;
    #endif
}

void deassert_LED (void)
{
    #if(!LED_ASSERT_VALUE)
        LED_P_OUT |= LED_BIT;
    #else
        LED_P_OUT &= ~LED_BIT;
    #endif
}

void assert_LEDR (void)
{
    #if(LEDR_ASSERT_VALUE)
        LEDR_P_OUT |= LEDR_BIT;
    #else
        LEDR_P_OUT &= ~LEDR_BIT;
    #endif
}

void deassert_LEDR (void)
{
    #if(!LEDR_ASSERT_VALUE)
        LEDR_P_OUT |= LEDR_BIT;
    #else
        LEDR_P_OUT &= ~LEDR_BIT;
    #endif
}

void assert_LEDG (void)
{
    #if(LEDG_ASSERT_VALUE)
        LEDG_P_OUT |= LEDG_BIT;
    #else
        LEDG_P_OUT &= ~LEDG_BIT;
    #endif
}

void deassert_LEDG (void)
{
    #if(!LEDG_ASSERT_VALUE)
        LEDG_P_OUT |= LEDG_BIT;
    #else
        LEDG_P_OUT &= ~LEDG_BIT;
    #endif
}

void assert_LEDB (void)
{
    #if(LEDB_ASSERT_VALUE)
        LEDB_P_OUT |= LEDB_BIT;
    #else
        LEDB_P_OUT &= ~LEDB_BIT;
    #endif
}

void deassert_LEDB (void)
{
    #if(!LEDB_ASSERT_VALUE)
        LEDB_P_OUT |= LEDB_BIT;
    #else
        LEDB_P_OUT &= ~LEDB_BIT;
    #endif
}

void assert_LCD_DC (void)
{
    #if(LCD_DC_ASSERT_VALUE)
        LCD_DC_P_OUT |= LCD_DC_BIT;
    #else
        LCD_DC_P_OUT &= ~LCD_DC_BIT;
    #endif
}

void deassert_LCD_DC (void)
{
    #if(!LCD_DC_ASSERT_VALUE)
        LCD_DC_P_OUT |= LCD_DC_BIT;
    #else
        LCD_DC_P_OUT &= ~LCD_DC_BIT;
    #endif
}

void assert_LCD_RESET (void)
{
    #if(LCD_RESET_ASSERT_VALUE)
        LCD_RESET_P_OUT |= LCD_RESET_BIT;
    #else
        LCD_RESET_P_OUT &= ~LCD_RESET_BIT;
    #endif
}

void deassert_LCD_RESET (void)
{
    #if(!LCD_RESET_ASSERT_VALUE)
        LCD_RESET_P_OUT |= LCD_RESET_BIT;
    #else
        LCD_RESET_P_OUT &= ~LCD_RESET_BIT;
    #endif
}

void assert_LCD_CS (void)
{
    #if(LCD_CS_ASSERT_VALUE)
        LCD_CS_P_OUT |= LCD_CS_BIT;
    #else
        LCD_CS_P_OUT &= ~LCD_CS_BIT;
    #endif
}

void deassert_LCD_CS (void)
{
    #if(!LCD_CS_ASSERT_VALUE)
        LCD_CS_P_OUT |= LCD_CS_BIT;
    #else
        LCD_CS_P_OUT &= ~LCD_CS_BIT;
    #endif
}


// *****        PRIVATE FUNCTIONS       *****
void INIT_GPIO (void)
{
    LED_P_DIR |= LED_BIT;
    LEDR_P_DIR |= LEDR_BIT;
    LEDG_P_DIR |= LEDG_BIT;
    LEDB_P_DIR |= LEDB_BIT;

    LCD_DC_P_DIR |= LCD_DC_BIT;
    LCD_RESET_P_DIR |= LCD_RESET_BIT;

    PB1_P_REN |= PB1_BIT;       // resistor enable
    PB1_P_OUT |= PB1_BIT;       // pull up resistor
    PB1_P_IES &= ~PB1_BIT;      // low-to-high edge
    PB1_P_IFG &= ~PB1_BIT;      // clear flag
    PB1_P_IE |= PB1_BIT;        // interrupt enabled

    PB2_P_REN |= PB2_BIT;       // resistor enable
    PB2_P_OUT |= PB2_BIT;       // pull up resistor
    PB2_P_IES &= ~PB2_BIT;      // low-to-high edge
    PB2_P_IFG &= ~PB2_BIT;      // clear flag
    PB2_P_IE |= PB2_BIT;        // interrupt enabled

    ROTA_P_REN |= ROTA_BIT;     // resistor enable
    ROTA_P_OUT |= ROTA_BIT;     // pull up resistor
    ROTA_P_IES |= ROTA_BIT;     // high-to-low edge
    ROTA_P_IFG &= ~ROTA_BIT;    // clear flag
    ROTA_P_IE |= ROTA_BIT;      // interrupt enable

    ROTB_P_REN |= ROTB_BIT;     // resistor enable
    ROTB_P_OUT |= ROTB_BIT;     // pull up resistor
    ROTB_P_IES |= ROTB_BIT;     // high-to-low edge
    ROTB_P_IFG &= ~ROTB_BIT;    // clear flag
    ROTB_P_IE |= ROTB_BIT;      // interrupt enable

    ROTP_P_REN |= ROTP_BIT;     // resistor enable
    ROTP_P_OUT |= ROTP_BIT;     // pull up resistor
    ROTP_P_IES |= ROTP_BIT;     // high-to-low edge
    ROTP_P_IFG &= ~ROTP_BIT;    // clear flag
    ROTP_P_IE |= ROTP_BIT;      // interrupt enable

    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableInterrupt(INT_PORT2);
}

void INIT_SPI (void)
{
    LCD_CS_P_SEL0 |= LCD_CS_BIT;
    LCD_SOMI_P_SEL0 |= LCD_SOMI_BIT;
    LCD_SIMO_P_SEL0 |= LCD_SIMO_BIT;
    LCD_SCK_P_SEL0 |= LCD_SCK_BIT;
}
