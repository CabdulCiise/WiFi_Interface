/* Standard Includes */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Driver Library */
#include "driverlib.h"

/* Project Includes */
#include "UserInterface.h"
#include "ESP8266/esp8266.h"

#define NUM_FORECAST_ITEMS 11

void DisplayEnvironmentalData(void)
{
    /* Header Info */
    char Title1[] = "Weather";
    char Title2[] = "Data";
    char buffer[50];

    displayHeader(Title1, Title2);

    sprintf(buffer, "%.1f%cF", BME280_GetTemperature() , 248);          // Format the temperature
    ILI_Write_String(buffer, 66, 90, TEXTCOLOR, MAIN_BG, 3);            // Display the temperature

    sprintf(buffer, "%.1f%%", BME280_GetHumidity());                    // Format the humidity
    ILI_Write_String(buffer, 74, 160, TEXTCOLOR, MAIN_BG, 3);           // Display the humidity

    sprintf(buffer, "%.2f inHg", BME280_GetPressure());                 // Format the pressure
    ILI_Write_String(buffer, 34, 230, TEXTCOLOR, MAIN_BG, 3);           // Display the pressure
}


void DisplayForecastData(void)
{
    /* Header Info */
    char Title1[] = "Weather";
    char Title2[] = "Forecast";
    displayHeader(Title1, Title2);

    int scrollLine = 90, heightDelta = 20, index = 0, i = 0, updateLines = 1, scrollCount = 0;
    int dispX = 10, dispY = scrollLine + 5;
    ILI_draw_fast_H_line(20, scrollLine, 200, BLACK);

    char buffer[50];
    sprintf(buffer, "Grand Rapids, MI"); // Format the city location
    ILI_Write_String(buffer, 25, scrollLine - 18, TEXTCOLOR, MAIN_BG, 2);  // Display the city location

    char* Field = "";
    char* Result = "";
    char displayLine[NUM_FORECAST_ITEMS][20];
    if(updateLines == 1)
    {
        ESP8266_GetForecastData();

        Field = strtok(forecastFields, " ");
        while(Field != NULL)
        {
            sprintf(displayLine[index], "%s:", Field);
            int size = strlen(Field);
            for(i = 0; i < 10-size; i++)
            {
                sprintf(displayLine[index], "%s ", displayLine[index]);
            }

            Field = strtok(NULL, " ");
            index++;
        }

        index = 0;
        Result = strtok(forecastResults, " ");
        while(Result != NULL)
        {
            sprintf(displayLine[index], "%s%s", displayLine[index], Result);
            Result = strtok(NULL, " ");

            index++;
        }

        index = 0;
        updateLines = 0;
    }

    for(index = 0; index < NUM_FORECAST_ITEMS; index++)
    {
        ILI_Write_Scroll_String(displayLine[index], dispX, dispY + (index * heightDelta) + (scrollCount * 3), TEXTCOLOR, MAIN_BG, 2, scrollLine);
    }

    scrollCount++;
    if(scrollCount == 60)
    {
        updateLines = 1;
        scrollCount = 0;
    }
}


void displayHeader(const char *screenTitle1, const char *screenTitle2)
{
    int headerLine = 45;
    static int screenStarted, toggle = 0;
    char buffer[50];

    if(screenStarted == 0)
    {
        // Section off date/time from weather info
        ILI_fill_rectangle(0, headerLine, 240, 320-headerLine, MAIN_BG);
        ILI_fill_rectangle(0, 0, 240, headerLine, HEADER_BG);
        ILI_draw_fast_H_line(0, headerLine, 300, BLACK);
        screenStarted = 1;
    }

    time = MAP_RTC_C_getCalendarTime();

    // Format the time being displayed
    if(time.hours > 12)
    {
        time.hours -= 12;
        if(toggle == 1)      // blink_time is used to blink the ':'    should toggle every second
        {
            sprintf(buffer, "%02d:%02d PM", time.hours, time.minutes);
        }
        else
        {
            sprintf(buffer, "%02d %02d PM", time.hours, time.minutes);
        }
    }
    else
    {
        if(toggle == 1)      // blink_time is used to blink the ':'    should toggle every second
        {
            sprintf(buffer, "%02d:%02d AM", time.hours, time.minutes);
        }
        else
        {
            sprintf(buffer, "%02d %02d AM", time.hours, time.minutes);
        }
    }

    ILI_Write_String(buffer, 137, 7, TEXTCOLOR, HEADER_BG, 2);                        // Display the time

    sprintf(buffer, "%02d/%02d", time.month , time.dayOfmonth);                         // Format the date
    ILI_Write_String(buffer, 172, 24, TEXTCOLOR, HEADER_BG, 2);                       // Display the date
    ILI_Write_String(screenTitle1, 8, 7, TEXTCOLOR, HEADER_BG, 2);                   // Display the screen title
    ILI_Write_String(screenTitle2, 8, 24, TEXTCOLOR, HEADER_BG, 2);                   // Display the screen title

    toggle = (++toggle) % 2;
}
