#include <Arduino.h>
#include "simpleLed.h"

simpleLed::simpleLed(int ledPin, int ledDelay, int ledChannel)
{
    _ledDelay = ledDelay;
    _ledPin = ledPin;
    _ledChannel = ledChannel;

    #if ESP32
    ledcAttachPin(_ledPin, _ledChannel);
    ledcSetup(_ledChannel, 1000, 8);
    #else
    pinMode(_ledPin, OUTPUT);
    #endif
}

void simpleLed::loop()
{
    switch (ledState)
    {
    case reset:
        _lastUpdate = millis();
        _brightness = 1;
        #if ESP32
        ledcWrite(_ledChannel, _brightness);
        #else
        analogWrite(_ledPin, _brightness);
        #endif

        ledState = directionUp;
        break;

    case directionUp:
        if ((millis() - _lastUpdate) > _ledDelay && (_brightness + 1) <= 255)
        {
            _brightness++;
            #if ESP32
            ledcWrite(_ledChannel, _brightness);
            #else
            analogWrite(_ledPin, _brightness);
            #endif
            _lastUpdate = millis();
        }
        else if (_brightness == 255)
        {
            ledState = directionDown;
        }
        break;

    case directionDown:
        if ((millis() - _lastUpdate) > _ledDelay && (_brightness - 1) >= 1)
        {
            _brightness--;

            #if ESP32
            ledcWrite(_ledChannel, _brightness);
            #else
            analogWrite(_ledPin, _brightness);
            #endif

            _lastUpdate = millis();
        }
        else if (_brightness == 1)
        {
            ledState = directionUp;
        }
        break;

    case turnOff:
        if((millis() - _lastUpdate) > _ledDelay && _brightness > 0)
        {
            _brightness--;
            #if ESP32
            ledcWrite(_ledChannel, _brightness);
            #else
            analogWrite(_ledPin, _brightness);
            #endif
            _lastUpdate = millis();
        }
        break;

    case turnOn:
        if(_brightness < 255)
        {
            ledState = directionUp;
        } else {
            ledState = directionDown;
        }
        break;
    }
}

void simpleLed::ledTurnOn()
{
    if(ledState == turnOff)
    {
        ledState = turnOn;
    }
}

void simpleLed::ledTurnOff()
{
    if(ledState != turnOff)
    {
        ledState = turnOff;
    }
}

void simpleLed::toggle()
{
    if(ledState == turnOff)
    {
        ledState = turnOn;
    } else {
        ledState = turnOff;
    }
}

ledController::enumLedState simpleLed::getState()
{
    return ledState;
}