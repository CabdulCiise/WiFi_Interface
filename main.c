/* DriverLib Includes */
#include "driverlib.h"

/* Project Includes */
#include "BME280/bme280_support.h"
#include "ClockSystem/ClockSystem.h"
#include "UART_Terminal/UART_Terminal.h"
#include "RTC/RTC.h"
#include "ILI9341/UserInterface.h"
#include "ESP8266/esp8266.h"
#include "Encoder/Encoder.h"

/* Function Prototypes */
void Init_System(void);
void LED_Init(void);

void main(void)
{
    Init_System();              // Initialize system

    /* System woken up by routine one second interrupt */
    while(1)
    {
        displayHeader();

        switch(screenIndex)                     // Determine which screen to display based on index
        {
            case 1:
                DisplayEnvironmentalData();     // Display BME data (Main Pt.1)
                break;
            case 2:
                DisplayForecastData();          // Display forecast data (Extra Credit Pt.1)
                break;
            case 3:
                DisplayStockData();             // Display exchange data (Extra Credit Pt.2)
                break;
        }

        if(twoMinuteFlag == 1)
            ESP8266_SendSensorData();           // Populate spreadsheet every 2 minutes

        MAP_PCM_gotoLPM3();                     // Go into low power mode until interrupt occurs
    }
}

/* Do all required startup initializations */
void Init_System(void)
{
    MAP_WDT_A_holdTimer();          // halting the Watchdog
    LED_Init();                     // drive LEDs low

    Setup_Clocks();                 // setting MCLK and SMCLK
    SysTick_Init();                 // systic timer setup

    BME280_Init();                  // setup BME sensor

    HAL_STARTUP();                  // setup LCD comm
    INIT_LCD();                     // initialize LCD

    EncoderInit();                  // setup encoder

    Terminal_Init();                // UART setup for terminal
    ESP8266_Init();                 // setup for ESP8266 module and internet access
    RTC_Init();                     // set current date/time via NIST server

    Timer32_Init();                 // one second interrupt
    MAP_Interrupt_enableMaster();   // set master interrupt handler
    MAP_PCM_gotoLPM3();             // enter low power mode
}

/* Turn all MSP432 LEDs off */
void LED_Init(void)
{
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);
}
