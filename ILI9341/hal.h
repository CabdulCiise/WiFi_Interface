
#include "msp.h"
#include "driverlib.h"


#ifndef HW_HAL_H_
#define HW_HAL_H_

void HAL_STARTUP (void);
void assert_LED (void);
void deassert_LED (void);
void assert_LEDR (void);
void deassert_LEDR (void);
void assert_LEDG (void);
void deassert_LEDG (void);
void assert_LEDB (void);
void deassert_LEDB (void);
void assert_LCD_DC (void);
void deassert_LCD_DC (void);
void assert_LCD_RESET (void);
void deassert_LCD_RESET (void);
void assert_LCD_CS (void);
void deassert_LCD_CS (void);

#endif /* HW_HAL_H_ */
