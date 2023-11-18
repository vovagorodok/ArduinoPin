#pragma once
#include <Arduino.h>

class DigitalPin
{
public:
    DigitalPin(uint8_t num, uint8_t mode);
    DigitalPin(uint8_t num, uint8_t mode, bool activeState);
    DigitalPin(uint8_t num, uint8_t mode, bool activeState, bool initialValue);
    DigitalPin& operator=(const DigitalPin&);
    DigitalPin& operator=(bool);

    operator bool() const;
    bool value() const;
    void setValue(bool value);
    void on();
    void off();
    void change();

    void setMode(uint8_t mode);

    using FunctionPtr = void(*)();
    using ObjectPtr = void*;
    using MethodPtr = void(*)(ObjectPtr);

    void detachInterrupt();
#if defined(ESP32)
    void attachInterrupt(FunctionPtr functionPtr, uint8_t mode);
    void attachInterrupt(MethodPtr methodPtr, ObjectPtr objectPtr, uint8_t mode);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"
    template <typename MethodPtrT, typename ObjectPtrT>
    void attachInterrupt(MethodPtrT methodPtr, ObjectPtrT objectPtr, uint8_t mode) {
        attachInterrupt((MethodPtr)methodPtr, (ObjectPtr)objectPtr, mode);
    }
    template <typename CallableT>
    void attachInterrupt(const CallableT& callable, uint8_t mode) {
        attachInterrupt((MethodPtr)&CallableT::operator(), (ObjectPtr)&callable, mode);
    }
#pragma GCC diagnostic pop

#else
    void attachInterrupt(FunctionPtr functionPtr, PinStatus mode);
#endif

private:
    const uint8_t num;
    const bool inactiveState;
};

class DigitalInputPin : public DigitalPin
{
public:
    DigitalInputPin(uint8_t num);
    DigitalInputPin(uint8_t num, bool activeState);
};

class DigitalPulledPin : public DigitalPin
{
public:
    DigitalPulledPin(uint8_t num);
    DigitalPulledPin(uint8_t num, bool activeState);
};

class DigitalOutputPin : public DigitalPin
{
public:
    DigitalOutputPin(uint8_t num);
    DigitalOutputPin(uint8_t num, bool initialValue);
    DigitalOutputPin(uint8_t num, bool initialValue, bool activeState);
    DigitalOutputPin& operator=(const DigitalPin&);
    DigitalOutputPin& operator=(bool);
};