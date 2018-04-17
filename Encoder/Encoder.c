/* DriverLib Includes */
#include "driverlib.h"

/* Project Includes */
#include "Encoder/Encoder.h"

uint8_t screenIndex;

void EncoderInit(void)
{
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN6);

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_registerInterrupt(GPIO_PORT_P2, PORT2_ISRHandler);
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);

    screenIndex = 1; // initialize to first screen
}

void PORT2_ISRHandler(void)
{
    uint8_t CLK, DT;

    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);

    if(status & GPIO_PIN5)
    {
        CLK = MAP_GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5);
        DT = MAP_GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN6);
    }

    if(CLK == 0 && DT == 1)             // Clockwise rotation
    {
        screenIndex++;
        if(screenIndex >= 4)            // Increment screen index
            screenIndex = 1;
    }
    else if(CLK == 0 && DT == 0)        // Counterclockwise rotation
    {
        screenIndex--;
        if(screenIndex <= 0)            // Decrement screen index
            screenIndex = 3;
    }
}
