
#include <thehal.h>

/*****************************************************************************/

#define GPIO_LED 13

/*****************************************************************************/

DigitalOut MyLed;

/*****************************************************************************/

void setup()
{
    // Initialize GPIO_LED pin as digital output and LOW level
    MyLed.setup(GPIO_LED, LOW);
}

void loop()
{
    // Heart Beat
    for(uint8_t i = 0; i < 2; i++)
    {
        MyLed.set_high(); // Same as: digitalWrite(GPIO_LED, HIGH);
        delay(120);
        MyLed.set_low();  // Same as: digitalWrite(GPIO_LED, LOW);
        delay(120);
    }
    delay(500);
}
