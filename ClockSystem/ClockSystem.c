/* Driver Library */
#include "driverlib.h"

/* Project Includes */
#include "ClockSystem.h"
#include "ILI9341/UserInterface.h"

/* Global Variables */
int twoMinuteFlag = 0;
int twoSecondFlag = 0;
int tenSecondFlag = 0;
int updateHeader = 0;

/* Setup clock sources: MCLK => 48 MHz, SMCLK => 12 MHz*/
void Setup_Clocks(void)
{
    /* Configuring pins for peripheral/crystal usage */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
        GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN3 | GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting the external clock frequency */
    MAP_CS_setExternalClockSourceFrequency(32000, 48000000);

    /* Starting HFXT in non-bypass mode without a timeout.
     * Change VCORE to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_CS_startHFXT(false);
    MAP_CS_startLFXT(false);

    /* Initializing MCLK (48MHz) to HFXT */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Initializing SMCLK (12MHz) to HFXT */
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);

    uint32_t MCLK = MAP_CS_getMCLK();       // used for Systic Timer
    uint32_t SMCLK = MAP_CS_getSMCLK();     // used for BME280 I2C communication
}

/* Setting Systic Timer for static delaying */
void SysTick_Init(void)
{
    //set up the clock
    SysTick -> CTRL = 0;
    SysTick -> LOAD = 0x00FFFFFF;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
}

/* Static delaying (ms) using Systic Timer */
void SysTick_delay(uint32_t delay_ms)
{
    //delay for the amount of time in milliseconds
    if(delay_ms > 349)
    {
        // Recursive delay
        SysTick_delay(delay_ms-349);
        delay_ms = 349;
    }
    SysTick -> LOAD = ((delay_ms*48000)-1);
    SysTick -> VAL = 0;
    while((SysTick -> CTRL & 0x00010000) == 0);
}

void Timer32_Init(void)
{
    uint64_t period_ticks = 48000000;  // 48000000 ticks for 1s

    MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    MAP_Timer32_setCount(TIMER32_0_BASE, period_ticks);
    MAP_Timer32_registerInterrupt(INT_T32_INT1, T32_INT1_IRQHandler);
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);
    MAP_Timer32_startTimer(TIMER32_0_BASE, false);
}

void T32_INT1_IRQHandler(void)
{
    // One second interrupt
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);

    // Set flags
    updateHeader = 1;
    twoMinuteFlag = (++twoMinuteFlag) % 120;
    twoSecondFlag = (++twoSecondFlag) % 2;
    tenSecondFlag = (++tenSecondFlag) % 10;

    if(LCD_Initialized = 1)
    {
        if(twoSecondFlag == 1)
        {
            pageDrawn = 0;
            ILI_DrawChar(161, 7, ':',  TEXTCOLOR, HEADER_BG, 2);
        }
        else
            ILI_DrawChar(161, 7, ' ',  TEXTCOLOR, HEADER_BG, 2);
    }
}
