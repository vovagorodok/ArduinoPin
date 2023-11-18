#include "DigitalPin.h"

DigitalPin::DigitalPin(uint8_t num, uint8_t mode) :
    DigitalPin(num, mode, HIGH) {}

DigitalPin::DigitalPin(uint8_t num, uint8_t mode, bool activeState) :
    num(num), inactiveState(!activeState)
{
    pinMode(num, mode);
}

DigitalPin::DigitalPin(uint8_t num, uint8_t mode, bool activeState, bool initialValue) :
    DigitalPin(num, mode, activeState)
{
    setValue(initialValue);
}

DigitalPin& DigitalPin::operator=(const DigitalPin& other)
{
    setValue(other.value());
    return *this;
}

DigitalPin& DigitalPin::operator=(bool value)
{
    setValue(value);
    return *this;
}

DigitalPin::operator bool() const
{
    return value();
}

bool DigitalPin::value() const
{
    return digitalRead(num) xor inactiveState;
}

void DigitalPin::setValue(bool value)
{
    digitalWrite(num, inactiveState xor value);
}

void DigitalPin::on()
{
    setValue(true);
}

void DigitalPin::off()
{
    setValue(false);
}

void DigitalPin::change()
{
    setValue(!value());
}

void DigitalPin::setMode(uint8_t mode)
{
    pinMode(num, mode);
}

void DigitalPin::detachInterrupt()
{
    ::detachInterrupt(digitalPinToInterrupt(num));
}

#if defined(ESP32)
void DigitalPin::attachInterrupt(FunctionPtr functionPtr, uint8_t mode)
{
    ::attachInterrupt(digitalPinToInterrupt(num), functionPtr, mode);
}

void DigitalPin::attachInterrupt(MethodPtr methodPtr, ObjectPtr objectPtr, uint8_t mode)
{
    ::attachInterruptArg(digitalPinToInterrupt(num), methodPtr, objectPtr, mode);
}
#else
void DigitalPin::attachInterrupt(FunctionPtr functionPtr, PinStatus mode)
{
    ::attachInterrupt(digitalPinToInterrupt(num), functionPtr, mode);
}
#endif


DigitalInputPin::DigitalInputPin(uint8_t num) :
    DigitalPin(num, INPUT) {}
DigitalInputPin::DigitalInputPin(uint8_t num, bool activeState) :
    DigitalPin(num, INPUT, activeState) {}

DigitalPulledPin::DigitalPulledPin(uint8_t num) :
    DigitalPulledPin(num, HIGH) {}
DigitalPulledPin::DigitalPulledPin(uint8_t num, bool activeState) :
    DigitalPin(num, activeState ? INPUT_PULLDOWN : INPUT_PULLUP, activeState) {}

DigitalOutputPin::DigitalOutputPin(uint8_t num) :
    DigitalOutputPin(num, false) {}
DigitalOutputPin::DigitalOutputPin(uint8_t num, bool initialValue) :
    DigitalOutputPin(num, initialValue, HIGH) {}
DigitalOutputPin::DigitalOutputPin(uint8_t num, bool initialValue, bool activeState) :
    DigitalPin(num, OUTPUT, activeState, initialValue) {}

DigitalOutputPin& DigitalOutputPin::operator=(const DigitalPin& other)
{
    setValue(other.value());
    return *this;
}

DigitalOutputPin& DigitalOutputPin::operator=(bool value)
{
    setValue(value);
    return *this;
}