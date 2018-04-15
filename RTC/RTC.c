/* DriverLib Includes */
#include "driverlib.h"

/* Project Includes */
#include "ESP8266/esp8266.h"
#include "RTC.h"

void RTC_Init(void)
{
    RTC_C_Calendar time;

    /* Get time date from NIST server and set on-board RTC */
    //ESP8266_GetTimeDate(&time);

    time.minutes = 30;
    time.hours = 14;
    time.dayOfmonth = 14;
    time.month = 4;
    time.seconds = 0;
    time.dayOfWeek = 7;
    time.year = 2018;

    /* Initializing RTC with current time as described in time in
     * definitions section */
    MAP_RTC_C_initCalendar(&time, RTC_C_FORMAT_BINARY);

    /* Start RTC Clock */
    MAP_RTC_C_startClock();
}

