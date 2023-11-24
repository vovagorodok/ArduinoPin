#pragma once
#include <Arduino.h>

class DigitalPin
{
public:
  constexpr DigitalPin(uint8_t num, uint8_t mode) :
    DigitalPin(num, mode, HIGH) {}
  constexpr DigitalPin(uint8_t num, uint8_t mode, bool activeState) :
    num(num), inactiveState(!activeState) {
    pinMode(num, mode);
  }
  constexpr DigitalPin(uint8_t num, uint8_t mode, bool activeState, bool initialValue) :
    DigitalPin(num, mode, activeState) {
    setValue(initialValue);
  }
  inline DigitalPin& operator=(const DigitalPin& other) {
    setValue(other.value());
    return *this;
  }
  inline DigitalPin& operator=(bool value) {
    setValue(value);
    return *this;
  }

  inline operator bool() const {
    return value();
  }
  inline bool value() const {
    return digitalRead(num) xor inactiveState;
  }
  inline void setValue(bool value) {
    digitalWrite(num, inactiveState xor value);
  }
  inline void on() {
    setValue(true);
  }
  inline void off() {
    setValue(false);
  }
  inline void change() {
    setValue(!value());
  }

  inline void setMode(uint8_t mode) {
    pinMode(num, mode);
  }

  using FunctionPtr = void(*)();
  using ObjectPtr = void*;
  using MethodPtr = void(*)(ObjectPtr);

  inline void detachInterrupt() {
    ::detachInterrupt(digitalPinToInterrupt(num));
  }
#if defined(ESP32)
  inline void attachInterrupt(FunctionPtr functionPtr, uint8_t mode) {
    ::attachInterrupt(digitalPinToInterrupt(num), functionPtr, mode);
  }
  inline void attachInterrupt(MethodPtr methodPtr, ObjectPtr objectPtr, uint8_t mode) {
    ::attachInterruptArg(digitalPinToInterrupt(num), methodPtr, objectPtr, mode);
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"
  template <typename MethodPtrT, typename ObjectPtrT>
  inline void attachInterrupt(MethodPtrT methodPtr, ObjectPtrT objectPtr, uint8_t mode) {
    attachInterrupt((MethodPtr)methodPtr, (ObjectPtr)objectPtr, mode);
  }
  template <typename CallableT>
  inline void attachInterrupt(const CallableT& callable, uint8_t mode) {
    attachInterrupt((MethodPtr)&CallableT::operator(), (ObjectPtr)&callable, mode);
  }
#pragma GCC diagnostic pop

#else
  inline void attachInterrupt(FunctionPtr functionPtr, PinStatus mode) {
    ::attachInterrupt(digitalPinToInterrupt(num), functionPtr, mode);
  }
#endif

private:
  const uint8_t num;
  const bool inactiveState;
};

class DigitalInputPin : public DigitalPin
{
public:
  constexpr DigitalInputPin(uint8_t num) :
    DigitalPin(num, INPUT) {}
  constexpr DigitalInputPin(uint8_t num, bool activeState) :
    DigitalPin(num, INPUT, activeState) {}
};

class DigitalPulledPin : public DigitalPin
{
public:
  constexpr DigitalPulledPin(uint8_t num) :
    DigitalPulledPin(num, HIGH) {}
  constexpr DigitalPulledPin(uint8_t num, bool activeState) :
    DigitalPin(num, activeState ? INPUT_PULLDOWN : INPUT_PULLUP, activeState) {}
};

class DigitalOutputPin : public DigitalPin
{
public:
  constexpr DigitalOutputPin(uint8_t num) :
    DigitalOutputPin(num, false) {}
  constexpr DigitalOutputPin(uint8_t num, bool initialValue) :
    DigitalOutputPin(num, initialValue, HIGH) {}
  constexpr DigitalOutputPin(uint8_t num, bool initialValue, bool activeState) :
    DigitalPin(num, OUTPUT, activeState, initialValue) {}
  inline DigitalOutputPin& operator=(const DigitalPin& other) {
    setValue(other.value());
    return *this;
  }
  inline DigitalOutputPin& operator=(bool value) {
    setValue(value);
    return *this;
  }
};