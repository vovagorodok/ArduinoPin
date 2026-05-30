#include <ArduinoPin.h>
#include <Arduino.h>

#define POTENTIOMETER_NUM 4
AnalogInputPin potentiometer(POTENTIOMETER_NUM);

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println(potentiometer.value());
    delay(1000);
}
