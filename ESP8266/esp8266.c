/* Standard Includes */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* DriverLib Includes */
#include "driverlib.h"

/* Project Includes */
#include "ClockSystem/ClockSystem.h"
#include "BME280/bme280_support.h"
#include "esp8266.h"

#define RX_BUFFER_SIZE (1024*4)

uint16_t RX_Count = 0;
char RX_Buffer[RX_BUFFER_SIZE] = "";
char forecastResults[512] = "";
char forecastFields[512] = "";

const eUSCI_UART_Config uartConfigA2 =
{
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,    // SMCLK Clock Source at 12000000 (divided down from MCLK)
     6,                                 // BRDIV (clock pre-scaler) = INT((12000000/115200=104.167/16)
     8,                                 // UCxBRF INT([(104.167/16)-INT(104.167/16)]x16))=(6.51-6)x16=8.16)
     0x11,                              // UCxBRS = 0x11 (fractional part of N from table on p.721 of tech ref)
     EUSCI_A_UART_NO_PARITY,            // No Parity
     EUSCI_A_UART_LSB_FIRST,            // LSB First
     EUSCI_A_UART_ONE_STOP_BIT,         // One stop bit
     EUSCI_A_UART_MODE,                 // UART mode
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Over sampling
};

/* Initializes UART on module A2. This is to be used with the ESP8266.
 * Creates and enables interrupt to handle UART TX/RX. */
void EUSCIA2_Init(void)
{
    // Selecting P3.2(RX) and P3.3(TX) in UART mode. ESP8266 UART
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 |
       GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfigA2);      // Configuring UART Module
    MAP_UART_enableModule(EUSCI_A2_BASE);                 // Enable UART module

    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_UART_registerInterrupt(EUSCI_A2_BASE, EUSCIA2_ISR);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
}

/* EUSCI A2 UART ISR - gets data from ESP8266 on UART2, sends to terminal emulator on UART0 */
void EUSCIA2_ISR(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
    {
        uint8_t U2RXData = MAP_UART_receiveData(EUSCI_A2_BASE);
        RX_Buffer[RX_Count++] = U2RXData;
        MAP_UART_transmitData(EUSCI_A0_BASE, U2RXData); // send byte out UART0 port
    }
}

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

void ESP8266_Reset(void)
{
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    SysTick_delay(3000);
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
}

/* Configure ESP8266 into station mode, establish a connection to a Wi-Fi router */
void ESP8266_SetInternetAccess(void)
{
    // Set WiFi mode
    ESP8266_RetryCommand("AT+CWMODE=1\r\n", 10, 1);

    // Connect to personal hotspot
    ESP8266_RetryCommand("AT+CWJAP=\"iPhone\",\"eskisehir01\"\r\n", 10, 1);
}

void ESP8266_GetTimeDate(RTC_C_Calendar* time)
{
    char ESP8266String[150] = "";

    // Connect to NIST site via TCP connection
    strcpy(ESP8266String, "AT+CIPSTART=\"TCP\",\"time.nist.gov\",13\r\n");
    int success = 0;
    do
    {
        success = ESP8266_SendCommand(ESP8266String, 1);
        if(success == 0)
        {
            SysTick_delay(5000);
        }
    } while(success == 0);
    SysTick_delay(500);

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
    uint8_t success = 0;
    do
    {
        success = ESP8266_SendCommand(ESP8266String, 1);
        SysTick_delay(500);
    } while(success == 0);

    sprintf(PostSensorData,"GET /pushingbox?devid=v044C7149636F3E6&temperature=%.1f&humidity=%.1f&pressure=%.2f "
        "HTTP/1.1\r\nHost: api.pushingbox.com\r\nUser-Agent: ESP8266/1.0\r\nConnection: close\r\n\r\n", temp, humi, pres);
    int formLength = strlen(PostSensorData);

    // send api request for encrypting sensor data
    memset(ESP8266String, '\0', 150);
    sprintf(ESP8266String, "AT+CIPSEND=%d\r\n", formLength);
    ESP8266_RetryCommand(ESP8266String, 10, 1);
    SysTick_delay(500);

    ESP8266_RetryCommand(PostSensorData, 10, 1);
}

uint8_t ESP8266_SendCommand(char* command, uint8_t clear)
{
    uint8_t success = 0, i = 0;

    // send command to ESP8266
    for(i = 0; i < strlen(command); i++)
    {
        MAP_UART_transmitData(EUSCI_A2_BASE, command[i]);
    }

    // wait for response by looking for possible responses
    while(strstr(RX_Buffer, "OK") == NULL &&
          strstr(RX_Buffer, "ERROR") == NULL &&
          strstr(RX_Buffer, "FAIL") == NULL);

    // received success response
    if(strstr(RX_Buffer, "OK") != NULL || strstr(RX_Buffer, "ALREADY CONNECTED") != NULL)
    {
        success = 1;
    }

    if(clear == 1)
    {
        // clear response buffer
        RX_Count = 0;
        memset(RX_Buffer, '\0', RX_BUFFER_SIZE);
    }

    return success;
}

uint8_t ESP8266_RetryCommand(char* command, uint16_t delay_ms, uint8_t clear)
{
    uint8_t retry = 0;

    // retry sending the command if not succeeded
    do
    {
        // check for success
        if(ESP8266_SendCommand(command, clear) == 1)
            return 1;

        SysTick_delay(delay_ms);
        retry++;
    } while(retry < 3);

    return 0;
}

void ESP8266_GetForecastData(void)
{
    char ESP8266String[150] = "";
    strcpy(ESP8266String, "AT+CIPSTART=\"TCP\",\"api.wunderground.com\",80\r\n");
    uint8_t success = 0;
    do
    {
        success = ESP8266_SendCommand(ESP8266String, 1);
        SysTick_delay(500);
    } while(success == 0);

    char PostSensorData[150] = "";
    sprintf(PostSensorData,"GET http://api.wunderground.com/api/24e8cb99501b03ce/conditions/q/MI/Grand_Rapids.json"
            " HTTP/1.1\r\nHost:api.wunderground.com\r\nConnection: close\r\n\r\n");
    int formLength = strlen(PostSensorData);

    // send api request for encrypting sensor data
    memset(ESP8266String, '\0', 150);
    sprintf(ESP8266String, "AT+CIPSEND=%d\r\n", formLength);
    ESP8266_RetryCommand(ESP8266String, 10, 1);
    SysTick_delay(500);

    ESP8266_RetryCommand(PostSensorData, 10, 1);
    while(strstr(RX_Buffer, "CLOSED") == NULL);

    ParseForecastData();
}

void ParseForecastData(void)
{
    sprintf(forecastResults,"");      // Clear previous results

    sprintf(forecastFields, "weather temp_f relative_humidity wind_dir wind_mph pressure_in "
            "windchill_f feelslike_f visibility_mi precip_1hr_in precip_today_in");

    char* token = strtok(forecastFields, " ");

    while(token != NULL)
    {
        int parsing = 1, index = 0;
        char field[50] = "", currentResults[50] = "";

        sprintf(field, "\"%s\":", token);

        char* substr = strstr(RX_Buffer, field);
        int startIndex = substr - (char *)(&RX_Buffer) + (strlen(field));
        if (RX_Buffer[startIndex] == '"')
            startIndex++;

        while(parsing)
        {
            sprintf(forecastResults, "%s%c", forecastResults, RX_Buffer[startIndex + index++]);
            if(RX_Buffer[startIndex + index] == '"' || RX_Buffer[startIndex + index] == ',')
            {
                parsing = 0;
            }
        }

        sprintf(forecastResults, "%s ", forecastResults);
        token = strtok(NULL, " ");
    }

    // clear response buffer
    RX_Count = 0;
    memset(RX_Buffer, '\0', RX_BUFFER_SIZE);
}
