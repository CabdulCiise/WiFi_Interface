/* Standard Includes */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* DriverLib Includes */
#include "driverlib.h"

/* Project Includes */
#include "ClockSystem/ClockSystem.h"
#include "ILI9341/UserInterface.h"
#include "BME280/bme280_support.h"
#include "esp8266_uart.h"
#include "esp8266.h"

#define NUM_FORECAST_ITEMS 11
#define NUM_STOCKS 5

void ESP8266_Init(void)
{
    // EN pin on ESP8266 pulled high
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

    // RST pin on ESP8266 pulled low to reset, pull high with 10K
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);

    EUSCIA2_Init();

    ESP8266_Reset();

    // setup Wi-Fi connection
    ESP8266_SetInternetAccess();
}

/* Configure ESP8266 into station mode, establish a connection to a Wi-Fi router */
void ESP8266_SetInternetAccess(void)
{
    // pull ESP from reset
    ESP8266_Start();
    SysTick_delay(250);

    // Set WiFi mode
    while(!ESP8266_RetryCommand("AT+CWMODE=1\r\n", 100));

    // Connect to personal hotspot
    while(!ESP8266_RetryCommand("AT+CWJAP=\"iPhone\",\"eskisehir01\"\r\n", 100));
}

void ESP8266_GetTimeDate(RTC_C_Calendar* time)
{
    char ESP8266String[150] = "";

    // Connect to NIST site via TCP connection
    strcpy(ESP8266String, "AT+CIPSTART=\"TCP\",\"time.nist.gov\",13\r\n");

    while(!ESP8266_RetryCommand(ESP8266String, 5000));

    while(strstr(RX_Buffer, "+IPD") == NULL)
    {
        _delay_cycles(1);
    }
    SysTick_delay(10);

    char* substr = strstr(RX_Buffer, "+IPD");
    int startIndex = substr - (char *)(&RX_Buffer) + 15;

    char str[50] = "";

    sprintf(str, "20%c%c", RX_Buffer[startIndex], RX_Buffer[startIndex+1]);
    time->year = atoi(str);

    sprintf(str, "%c%c", RX_Buffer[startIndex+3], RX_Buffer[startIndex+4]);
    time->month = atoi(str);

    sprintf(str, "%c%c", RX_Buffer[startIndex+6], RX_Buffer[startIndex+7]);
    time->dayOfmonth = atoi(str);

    sprintf(str, "%c%c", RX_Buffer[startIndex+9], RX_Buffer[startIndex+10]);

    // convert to EST time
    int hours = atoi(str) - 4;  // subtract time difference
    if(hours < 0)
    {
        hours += 24;
        time->dayOfmonth -= 1;  // set day back one
    }
    time->hours = hours;

    sprintf(str, "%c%c", RX_Buffer[startIndex+12], RX_Buffer[startIndex+13]);
    time->minutes = atoi(str);

    sprintf(str, "%c%c", RX_Buffer[startIndex+15], RX_Buffer[startIndex+16]);
    time->seconds = atoi(str);

    time->dayOfWeek = 1;    // don't care about this
}

void ESP8266_SendSensorData(void)
{
    char ESP8266String[150] = "";
    char PostSensorData[150] = "";

    float temp = BME280_GetTemperature();
    float humi = BME280_GetHumidity();
    float pres = BME280_GetPressure();

    // connect to Google pushingbox API
    strcpy(ESP8266String, "AT+CIPSTART=\"TCP\",\"api.pushingbox.com\",80\r\n");

    while(!ESP8266_RetryCommand(ESP8266String, 500));

    sprintf(PostSensorData,"GET /pushingbox?devid=v044C7149636F3E6&temperature=%.1f&humidity=%.1f&pressure=%.2f "
        "HTTP/1.1\r\nHost: api.pushingbox.com\r\nUser-Agent: ESP8266/1.0\r\nConnection: close\r\n\r\n", temp, humi, pres);
    int formLength = strlen(PostSensorData);

    // send api request for encrypting sensor data
    memset(ESP8266String, '\0', 150);
    sprintf(ESP8266String, "AT+CIPSEND=%d\r\n", formLength);
    ESP8266_RetryCommand(ESP8266String, 10);

    ESP8266_RetryCommand(PostSensorData, 10);
}

uint8_t ESP8266_SendCommand(char* command)
{
    uint8_t success = 0, i = 0;

    // send command to ESP8266
    for(i = 0; i < strlen(command); i++)
    {
        MAP_UART_transmitData(EUSCI_A2_BASE, command[i]);
    }

    SysTick_delay(100);

    // wait for response by looking for possible responses
    while(strstr(RX_Buffer, "OK") == NULL &&
          strstr(RX_Buffer, "ERROR") == NULL &&
          strstr(RX_Buffer, "FAIL") == NULL);

    // received success response
    if(strstr(RX_Buffer, "OK") != NULL || strstr(RX_Buffer, "ALREADY CONNECTED") != NULL)
    {
        success = 1;
    }

    // clear response buffer
    RX_Count = 0;
    memset(RX_Buffer, '\0', RX_BUFFER_SIZE);

    return success;
}

uint8_t ESP8266_RetryCommand(char* command, uint16_t delay_ms)
{
    uint8_t retry = 0;

    // retry sending the command if not succeeded
    do
    {
        // check for success
        if(ESP8266_SendCommand(command) == 1)
        {
            SysTick_delay(250);
            return 1;
        }

        SysTick_delay(delay_ms);
        retry++;
    } while(retry < 3);

    return 0;
}

void ESP8266_GetForecastData(void)
{
    char ESP8266String[150] = "";
    strcpy(ESP8266String, "AT+CIPSTART=\"TCP\",\"api.wunderground.com\",80\r\n");

    while(!ESP8266_RetryCommand(ESP8266String, 500));

    char PostSensorData[150] = "";
    sprintf(PostSensorData,"GET /api/24e8cb99501b03ce/conditions/q/MI/Grand_Rapids.json"
            " HTTP/1.1\r\nHost:api.wunderground.com\r\nConnection: close\r\n\r\n");
    int formLength = strlen(PostSensorData);

    // send api request for encrypting sensor data
    memset(ESP8266String, '\0', 150);
    sprintf(ESP8266String, "AT+CIPSEND=%d\r\n", formLength);
    ESP8266_RetryCommand(ESP8266String, 10);

    ESP8266_RetryCommand(PostSensorData, 10);
    while(strstr(RX_Buffer, "CLOSED") == NULL);

    ParseForecastData();
}

void ParseForecastData(void)
{
    int startIndex = 0, i = 0;
    char* substr;

    const char forecastFields[11][25] = {"\"weather\":", "\"temp_f\":", "\"relative_humidity\":", "\"wind_dir\":", "\"wind_mph\":", "\"pressure_in\":",
                                         "\"windchill_f\":", "\"feelslike_f\":", "\"visibility_mi\":", "\"precip_1hr_in\":", "\"precip_today_in\":"};

    // index offsets
    const int offsets[11] = {11, 9, 21, 12, 11, 15, 15, 15, 17, 17, 19};

    // setup recording array
    sprintf(forecastData[0],  "Weather: ");
    sprintf(forecastData[2],  "Temperature: "); // units Fahrenheit (F)
    sprintf(forecastData[4],  "Relative Humi: "); // units percentage (%)
    sprintf(forecastData[6],  "Wind Dir: "); // south north etc
    sprintf(forecastData[8],  "Wind Speed: "); // miles per hour (mph)
    sprintf(forecastData[10],  "Pressure: "); // units inches mercury inHg
    sprintf(forecastData[12],  "Wind Chill: "); // units Fahrenheit (F)
    sprintf(forecastData[14],  "Feels Like: "); // units Fahrenheit (F)
    sprintf(forecastData[16],  "Visibility: "); // units miles (mi)
    sprintf(forecastData[18],  "Precip 1hr: "); // units inches (in)
    sprintf(forecastData[20], "Precip Today: "); // units inches (in)

    for(i = 0; i < NUM_FORECAST_ITEMS; i++)
    {
        substr = strstr(RX_Buffer, forecastFields[i]);
        startIndex = substr - (char *)(&RX_Buffer) + offsets[i];

        sprintf(forecastData[2*i + 1], "    ");

        while(RX_Buffer[startIndex] != '"' && RX_Buffer[startIndex] != ',')
        {
            sprintf(forecastData[2*i + 1], "%s%c", forecastData[2*i + 1], RX_Buffer[startIndex++]);
        }
    }

    // append units
    sprintf(forecastData[3], "%s F", forecastData[3]);
    sprintf(forecastData[9], "%s mph", forecastData[9]);
    sprintf(forecastData[11], "%s inHg", forecastData[11]);
    sprintf(forecastData[13], "%s F", forecastData[13]);
    sprintf(forecastData[15], "%s F", forecastData[15]);
    sprintf(forecastData[17], "%s mi", forecastData[17]);
    sprintf(forecastData[19], "%s in", forecastData[19]);
    sprintf(forecastData[21], "%s in", forecastData[21]);

    // clear response buffer
    RX_Count = 0;
    memset(RX_Buffer, '\0', RX_BUFFER_SIZE);
}

void ESP8266_GetStockData(void)
{
    char ESP8266String[200] = "";
    strcpy(ESP8266String, "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

    while(!ESP8266_RetryCommand(ESP8266String, 500));

    char PostSensorData[200] = "";
    sprintf(PostSensorData,"GET /apps/thinghttp/send_request?api_key=U1WOPRJV707CXOXD "
        " HTTP/1.1\r\nHost: api.thingspeak.com\r\nConnection: close\r\n\r\n");
    int formLength = strlen(PostSensorData);

    // send api request for encrypting sensor data
    memset(ESP8266String, '\0', 200);
    sprintf(ESP8266String, "AT+CIPSEND=%d\r\n", formLength);
    ESP8266_RetryCommand(ESP8266String, 10);

    ESP8266_RetryCommand(PostSensorData, 10);
    while(strstr(RX_Buffer, "CLOSED") == NULL);

    ParseStockData();
}

void ParseStockData(void)
{
    const char stocks[5][5] = {"MSFT", "AAPL", "FB", "TWTR", "GNTX"};
    const char stockFields[4][20] = {"symbol", "price", "volume", "timestamp"};
    const int offsets[4] = {10, 9, 10, 13};
    uint8_t i = 0;

    // setup recording array
    for(i = 0; i < NUM_STOCKS; i++)
    {
        sprintf(stockData[i*4], "%s", stocks[i]);
        sprintf(stockData[i*4+1], "$");
        sprintf(stockData[i*4+2], "$");
        sprintf(stockData[i*4+3], "");
    }

    char* substr = strstr(RX_Buffer, "[{");
    int length = substr - (char*)(&RX_Buffer) + 3;

    char* data = (char*)(&RX_Buffer) + length;
    char* token = strtok(data, ",");
    token = strtok(NULL, ",");

    char line[50];
    uint8_t stockNum = 0;

    while(token != NULL)
    {
        for(i = 1; i < 4; i++)
        {
            memset(line, '\0', 50);
            sprintf(line, "%s", token);

            if(strstr(line, stockFields[i]) != NULL)
            {
                substr = strstr(line, stockFields[i]);
                int startIndex = substr - (char*)(&line) + offsets[i];

                while(line[startIndex] != '"')
                {
                    sprintf(stockData[stockNum*4 + i], "%s%c", stockData[stockNum*4 + i], line[startIndex++]);
                }

                if(i == 3)
                {
                    stockNum++;
                }
                token = strtok(NULL, ",");
            }
        }
        token = strtok(NULL, ",");
    }
}
