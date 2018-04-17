/* DriverLib Includes */
#include "driverlib.h"

/* Project Includes */
#include "ESP8266/esp8266.h"
#include "ClockSystem/ClockSystem.h"
#include "RTC.h"

void RTC_Init(void)
{
    uint8_t success = 0;
    RTC_C_Calendar time;

    /* Get time date from NIST server and set on-board RTC */
    while(!success)
    {
        success = ESP8266_GetTimeDate(&time);
        success ? SysTick_delay(10) : SysTick_delay(5000);
    }

    /* Initializing RTC with current time as described in time in
     * definitions section */
    MAP_RTC_C_initCalendar(&time, RTC_C_FORMAT_BINARY);

    /* Start RTC Clock */
    MAP_RTC_C_startClock();
}

