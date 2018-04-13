/* Standard Includes */
#include <stdio.h>

/* Driver Library */
#include "driverlib.h"

/* Project Includes */
#include "UserInterface.h"

void DisplayData(void)
{
    static int toggle = 0;
    char buffer[50];

    RTC_C_Calendar time = MAP_RTC_C_getCalendarTime();

    sprintf(buffer, "%02d/%02d/%04d", time.month, time.dayOfmonth, time.year);
    ILI_Write_String(buffer, 15, 6, BLACK, BACKGROUND, 3);

    if(time.hours > 12)
    {
        time.hours -= 12;
        sprintf(buffer, "%02d:%02d PM", time.hours, time.minutes);
    }
    else
    {
        sprintf(buffer, "%02d:%02d AM", time.hours, time.minutes);
    }
    ILI_Write_String(buffer, 60, 40, BLACK, BACKGROUND, 3);

    if(toggle == 1)
    {
        ILI_Write_String(" ", 95, 40, BLACK, BACKGROUND, 3);
    }
    toggle = (++toggle) % 2;

    sprintf(buffer, "%.1fF", BME280_GetTemperature());
    ILI_Write_String(buffer, 38, 100, BLACK, BACKGROUND, 3);

    sprintf(buffer, "%.1f%%", BME280_GetHumidity());
    ILI_Write_String(buffer, 48, 160, BLACK, BACKGROUND, 3);

    sprintf(buffer, "%.2f inHg", BME280_GetPressure());
    ILI_Write_String(buffer, 58, 220, BLACK, BACKGROUND, 3);
}
