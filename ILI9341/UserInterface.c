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
#include "Encoder/Encoder.h"

#define NUM_FORECAST_ITEMS 11
#define NUM_STOCKS 5

/* Global Variables */
uint8_t pageDrawn = 0;
char forecastData[22][30];
char stockData[20][32];

char screenTitle1[10] = "Weather  ", screenTitle2[10] = "Data";
uint8_t LCD_Initialized = 0;

void displayHeader()
{
    int headerLine = 45;
    static int screenStarted;
    char buffer[50], buffer2[50], AMPM[2];

    if(screenStarted == 0)
    {
        // Section off date/time from weather info
        ILI_fill_rectangle(0, headerLine, 240, 320-headerLine, MAIN_BG);
        ILI_fill_rectangle(0, 0, 240, headerLine, HEADER_BG);
        ILI_draw_fast_H_line(0, headerLine, 300, BLACK);
        screenStarted = 1;
    }

    RTC_C_Calendar time = MAP_RTC_C_getCalendarTime();

    // Format the time being displayed
    if(time.hours > 12)
    {
        time.hours -= 12;
        sprintf(AMPM, "PM");
    }
    else
        sprintf(AMPM, "AM");

    sprintf(buffer, "%02d", time.hours);
    sprintf(buffer2, "%02d %s", time.minutes, AMPM);
    ILI_Write_String(buffer, 137, 7, TEXTCOLOR, HEADER_BG, 2);              // Display the time
    ILI_Write_String(buffer2, 173, 7, TEXTCOLOR, HEADER_BG, 2);             // Display the time

    sprintf(buffer, "%02d/%02d", time.month , time.dayOfmonth);             // Format the date
    ILI_Write_String(buffer, 172, 24, TEXTCOLOR, HEADER_BG, 2);             // Display the date
    ILI_Write_String(screenTitle1, 8, 7, TEXTCOLOR, HEADER_BG, 2);          // Display the screen title
    ILI_Write_String(screenTitle2, 8, 24, TEXTCOLOR, HEADER_BG, 2);         // Display the screen title
}

void DisplayEnvironmentalData(void)
{
    /* Header Info */
    sprintf(screenTitle1, "Weather  ");
    sprintf(screenTitle2, "Data    ");

    if(screenTransition == 1)
    {
        MAP_Interrupt_disableInterrupt(INT_T32_INT1);
        displayHeader();
        ILI_fill_rectangle(0, 46, 240, 300, MAIN_BG);       // Clear content before changing screens
        screenTransition = 0;                               // Clear flag
        MAP_Interrupt_enableInterrupt(INT_T32_INT1);
    }

    char buffer[50];

    sprintf(buffer, "%.1f%cF", BME280_GetTemperature() , 248);          // Format the temperature
    ILI_Write_String(buffer, 66, 90, TEXTCOLOR, MAIN_BG, 3);            // Display the temperature

    sprintf(buffer, "%.1f%%", BME280_GetHumidity());                    // Format the humidity
    ILI_Write_String(buffer, 74, 160, TEXTCOLOR, MAIN_BG, 3);           // Display the humidity

    sprintf(buffer, "%.2f inHg", BME280_GetPressure());                 // Format the pressure
    ILI_Write_String(buffer, 34, 230, TEXTCOLOR, MAIN_BG, 3);           // Display the pressure
}

void DisplayForecastData(void)
{
    // Header Info
    sprintf(screenTitle1, "Weather  ");
    sprintf(screenTitle2, "Forecast");

    if(screenTransition == 1)
    {
        MAP_Interrupt_disableInterrupt(INT_T32_INT1);
        displayHeader();
        ILI_fill_rectangle(0, 46, 240, 300, MAIN_BG);       // Clear content before changing screens
        screenTransition = 0;                               // Clear flag
        MAP_Interrupt_enableInterrupt(INT_T32_INT1);
    }

    static int scrollCount = 0;
    int scrollLine = 90, heightDelta = 20, index = 0, i = 0, updateCity = 1;
    int dispX = 8, dispY = scrollLine + 5;

    char buffer[50];
    if(updateCity == 1)
    {
        sprintf(buffer, "Grand Rapids, MI"); // Format the city location
        ILI_Write_String(buffer, 25, scrollLine - 18, TEXTCOLOR, MAIN_BG, 2);  // Display the city location
        ILI_draw_fast_H_line(20, scrollLine, 200, BLACK);
        updateCity = 0;
    }

    for(index = 0; index < 2*NUM_FORECAST_ITEMS; index++)
    {
        dispY = (scrollLine) + (((index * heightDelta) + (scrollCount * 2)) % 438);

        if((dispY < 320) && (dispY > scrollLine+1))
        {
            if(dispY > scrollLine+3)
            {
                ILI_draw_fast_H_line(0, dispY-2, 240, MAIN_BG);
                ILI_draw_fast_H_line(0, dispY-1, 240, MAIN_BG);
            }
            ILI_Write_Scroll_String(forecastData[index], dispX, dispY, TEXTCOLOR, MAIN_BG, 2, scrollLine);
        }
    }

    scrollCount++;

    if(scrollCount >= 219){
        ESP8266_GetForecastData();
        scrollCount = 0;
    }
}

void DisplayStockData(void)
{
    // Header Info
    sprintf(screenTitle1, "Stock     ");
    sprintf(screenTitle2, "Data    ");

    if(screenTransition == 1)
    {
        MAP_Interrupt_disableInterrupt(INT_T32_INT1);
        displayHeader();
        ILI_fill_rectangle(0, 46, 240, 300, MAIN_BG);       // Clear content before changing screens
        screenTransition = 0;                               // Clear flag
        MAP_Interrupt_enableInterrupt(INT_T32_INT1);
    }

    static int stockDisplayed = 0;
    char buffer1[50], buffer2[50];

    sprintf(buffer1, "Symbol:");                                          // Symbol label
    ILI_Write_String(buffer1, 10, 60, TEXTCOLOR, MAIN_BG, 2);
    ILI_draw_fast_H_line(7, 76, 84, BLACK);                               // Underline label
    sprintf(buffer2, " %s", stockData[4*stockDisplayed]);
    ILI_Write_String(buffer2, 10, 85, TEXTCOLOR, MAIN_BG, 3);             // Display the stock symbol
    sprintf(buffer1, ""); sprintf(buffer2, "");

    sprintf(buffer1, "Price:");                                           // Price label
    ILI_Write_String(buffer1, 10, 130, TEXTCOLOR, MAIN_BG, 2);
    ILI_draw_fast_H_line(7, 146, 74, BLACK);                              // Underline label
    sprintf(buffer2, " %s", stockData[4*stockDisplayed + 1]);
    ILI_Write_String(buffer2, 10, 155, TEXTCOLOR, MAIN_BG, 3);            // Display the price symbol
    sprintf(buffer1, ""); sprintf(buffer2, "");


    sprintf(buffer1, "Volume:");                                          // Volume label
    ILI_Write_String(buffer1, 10, 200, TEXTCOLOR, MAIN_BG, 2);
    ILI_draw_fast_H_line(7, 216, 84, BLACK);                              // Underline label
    sprintf(buffer2, " %s", stockData[4*stockDisplayed + 2]);
    ILI_Write_String(buffer2, 10, 225, TEXTCOLOR, MAIN_BG, 3);            // Display the volume symbol
    sprintf(buffer1, ""); sprintf(buffer2, "");

    sprintf(buffer1, "Timestamp:");                                       // Timestamp label
    ILI_Write_String(buffer1, 10, 270, TEXTCOLOR, MAIN_BG, 2);
    ILI_draw_fast_H_line(7, 286, 120, BLACK);                             // Underline label
    sprintf(buffer2, "%s", stockData[4*stockDisplayed + 3]);
    ILI_Write_String(buffer2, 6, 295, TEXTCOLOR, MAIN_BG, 2);            // Display the timestamp symbol
    sprintf(buffer1, ""); sprintf(buffer2, "");

    stockDisplayed = (stockDisplayed + 1) % 5;

    pageDrawn = 1;
}
