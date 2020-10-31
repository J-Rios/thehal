
#include <thehal.h>

/*****************************************************************************/

#define GPIO_LED 13

/*****************************************************************************/

DigitalOut MyLed(GPIO_LED);

/*****************************************************************************/

void setup()
{
    MyLed.setup();
}

void loop()
{
    // Heart Beat
    for(uint8_t i = 0; i < 2; i++)
    {
        MyLed.set_high();
        delay(120);
        MyLed.set_low();
        delay(120);
    }
    delay(500);
}
