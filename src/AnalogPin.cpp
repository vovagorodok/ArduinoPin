#include "AnalogPin.h"

AnalogInputPin::AnalogInputPin(uint8_t num) :
    num(num) {}

AnalogInputPin::operator AnalogValue() const
{
    return value();
}

AnalogValue AnalogInputPin::value() const
{
    return analogRead(num);
}