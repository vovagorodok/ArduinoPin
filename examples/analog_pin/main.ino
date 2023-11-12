#include <AnalogPin.h>
#include <Arduino.h>

#define POTENTIOMETR_NUM 4
AnalogInputPin potentiometer(POTENTIOMETR_NUM);

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println(potentiometer.value());
    delay(1000);
}