#include <Arduino.h>
#include "simpleLed.h"

// Create LED and set transition delay to 4 ms
simpleLed led1(LED_BUILTIN, 4);

void setup()
{
    // Do Nothing..
}

void loop()
{   
    // Very Simple turn on / turn off
    led1.turnOn();
    delay(5000);
    led1.turnOff();
    delay(5000);
}