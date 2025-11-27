#pragma once
#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)
using AnalogValue = uint16_t;
#else
using AnalogValue = int;
#endif

class AnalogInputPin
{
public:
  constexpr AnalogInputPin(uint8_t num) :
    num(num) {}

  inline operator AnalogValue() const {
    return value();
  }
  inline AnalogValue value() const {
    return analogRead(num);
  }
#if defined(ARDUINO_ARCH_ESP32)
  inline uint32_t millivolts() const {
    return analogReadMilliVolts(num);
  }
#endif

private:
  const uint8_t num;
};