#pragma once

template <typename SwitchT>
class ScopedOn
{
public:
    inline ScopedOn(SwitchT& sw) : ref(sw)
    { ref.on(); }
    inline ~ScopedOn()
    { ref.off(); }

private:
    SwitchT& ref;
};