#ifndef ILI9341_USERINTERFACE_H_
#define ILI9341_USERINTERFACE_H_

/* Project Includes */
#include "BME280/bme280_support.h"
#include "ili9341.h"
#include "colors.h"
#include "hal.h"

extern uint8_t pageDrawn;
extern char forecastData[22][30];
extern char stockData[20][32];
extern char screenTitle1[10];
extern char screenTitle2[10];
extern uint8_t LCD_Initialized;

void DisplayStockData(void);
void DisplayForecastData(void);
void DisplayEnvironmentalData(void);
void displayHeader();

#endif /* ILI9341_USERINTERFACE_H_ */
