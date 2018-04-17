/* Standard Includes */
#include <stdio.h>

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
void GetData(void);
void LED_Init(void);

void main(void)
{
    Init_System();              // Initialize system

    /* System woken up by routine one second interrupt */
    while(1)
    {
        while(screenTransition == 1)
        {
            ILI_fill_rectangle(0, 46, 240, 300, MAIN_BG);       // Clear content before changing screens
            screenTransition = 0;                               // Clear flag
        }

        while(updateHeader == 1)
        {
            displayHeader();                    // Update header (every 1 second or when screen transition)
            updateHeader = 0;                   // Clear flag
        }

        switch(screenIndex)                     // Determine which screen to display based on index
        {
            case 1:
                DisplayEnvironmentalData();     // Display BME data (Main Pt.1)
                if(BME280_GetHumidity() >= 50)
                    ESP8266_SendNotice();
                break;
            case 2:
                if(tenSecondFlag == 1)
                {
                    uint8_t success = 0;
                    while(!success)
                    {
                        success = ESP8266_GetForecastData();
                    }
                }
                DisplayForecastData();          // Display forecast data (Extra Credit Pt.1)
                break;
            case 3:
                if(tenSecondFlag == 1)
                {
                    uint8_t success = 0;
                    while(!success)
                    {
                        success = ESP8266_GetStockData();
                    }
                }
                if(pageDrawn == 0)
                {
                    DisplayStockData();             // Display exchange data (Extra Credit Pt.2)
                }
                break;
        }

        if(twoMinuteFlag == 1)
        {
            ESP8266_SendSensorData();           // Populate spreadsheet every 2 minutes
        }
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

    Terminal_Init();                // UART setup for terminal
    ESP8266_Init();                 // setup for ESP8266 module and internet access

    HAL_STARTUP();                  // setup LCD comm
    INIT_LCD();                     // initialize LCD

    RTC_Init();                     // set current date/time via NIST server
    GetData();                      // get initial stock and forecast data

    EncoderInit();                  // setup encoder

    Timer32_Init();                 // one second interrupt
    MAP_Interrupt_enableMaster();   // set master interrupt handler
}

/* Get initial data */
void GetData(void)
{
    ESP8266_GetForecastData() ? printf("1\n") : printf("0\n");

    ESP8266_GetStockData() ? printf("1\n") : printf("0\n");
}

/* Turn all MSP432 LEDs off */
void LED_Init(void)
{
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);
}
