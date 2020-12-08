
#include <thehal.h>

/*****************************************************************************/

#define GPIO_LED 13

/*****************************************************************************/

Time MyTime;

/*****************************************************************************/

void setup()
{
    pinMode(GPIO_LED, LOW);
}

void loop()
{
    digitalWrite(GPIO_LED, HIGH);
    MyTime.delay_ms(500);
    digitalWrite(GPIO_LED, LOW);
    MyTime.delay_ms(500);
}
