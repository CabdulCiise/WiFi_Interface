#ifndef ESP8266_ESP8266_H_
#define ESP8266_ESP8266_H_

/* DriverLib Includes */
#include "driverlib.h"

void ESP8266_Init(void);
void ESP8266_SetInternetAccess(void);

uint8_t ESP8266_SendCommand(char* command);

uint8_t ESP8266_GetTimeDate(RTC_C_Calendar* time);
uint8_t ESP8266_SendSensorData(void);

uint8_t ESP8266_GetForecastData(void);
void ParseForecastData(void);

uint8_t ESP8266_GetStockData(void);
void ParseStockData(void);

#endif /* ESP8266_ESP8266_H_ */
