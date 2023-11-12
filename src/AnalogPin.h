#pragma once
#include <Arduino.h>

#if defined(ESP32)
using AnalogValue = uint16_t;
#else
using AnalogValue = int;
#endif

class AnalogInputPin
{
public:
    AnalogInputPin(uint8_t num);

    operator AnalogValue() const;
    AnalogValue value() const;

private:
    const uint8_t num;
};