# Arduino Pin

Objective arduino pins like:
- `DigitalPin` - pin object, can be used as input or output
- `DigitalInputPin` - open collector input
- `DigitalPulledPin` - pulled input
- `DigitalOutputPin` - output
- `AnalogInputPin` - analog input
- `ScopedOn` - RAII switch that turns off when out of scope

## Configuration
Library requires c++14 or greater.  
For PlatformIO. Add to `platformio.ini`:
```
build_flags =
	-std=c++14
	-std=gnu++14
build_unflags =
	-std=gnu++11
```

For Arduino IDE. At boards package installation folder create `platform.local.txt`:
```
compiler.cpp.extra_flags=-std=c++14
```