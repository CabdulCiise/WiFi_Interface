#ifndef ESP8266_ESP8266_H_
#define ESP8266_ESP8266_H_

/* DriverLib Includes */
#include "driverlib.h"

void ESP8266_Init(void);
void EUSCIA2_Init(void);
void EUSCIA2_ISR(void);
void ESP8266_Reset(void);
uint8_t ESP8266_SendCommand(char* command);
uint8_t ESP8266_RetryCommand(char* command, uint16_t delay_ms);
void ESP8266_SetInternetAccess(void);
void ESP8266_GetTimeDate(RTC_C_Calendar* time);
void ESP8266_SendSensorData(void);

#endif /* ESP8266_ESP8266_H_ */
