#ifndef ILI9341_USERINTERFACE_H_
#define ILI9341_USERINTERFACE_H_

/* Project Includes */
#include "BME280/bme280_support.h"
#include "ili9341.h"
#include "colors.h"
#include "hal.h"

extern char forecastData[11][30];
extern char stockData[20][32];

void DisplayEnvironmentalData(void);
void displayHeader(const char *screenTitle1, const char *screenTitle2);

#endif /* ILI9341_USERINTERFACE_H_ */
