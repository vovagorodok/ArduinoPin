#pragma once

template <typename T>
class ScopedOn
{
public:
    inline ScopedOn(T& sw) : ref(sw)
    { ref.on(); }
    inline ~ScopedOn()
    { ref.off(); }
private:
    T& ref;
};

template <typename T>
class ScopedOff
{
public:
    inline ScopedOff(T& sw) : ref(sw)
    { ref.off(); }
    inline ~ScopedOff()
    { ref.on(); }
private:
    T& ref;
};