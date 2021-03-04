#ifndef simpleLed_h
#define simpleLed_h

#include <Arduino.h>

class simpleLed
{
    public:
        simpleLed(int ledPin, int ledDelay = 10, int ledChannel = 0);
        void loop();
        void setDelay(int ledDelay);
        int getDelay();
        enum enumLedState
        {
            reset,
            directionUp,
            directionDown,
            turnOn,
            turnOff,
        };
        enumLedState ledState = reset;
        void ledTurnOff();
        void ledTurnOn();
        void toggle();
        enumLedState getState();
    private:
        int _ledPin;
        int _ledDelay = 3;
        int _brightness = 0;
        int _ledChannel;
        unsigned long _lastUpdate;
};

#endif