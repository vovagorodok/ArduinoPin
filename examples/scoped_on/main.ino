#include <DigitalPin.h>
#include <ScopedOn.h>
#include <Arduino.h>

#define LED_NUM 4
#define LED_ACTIVE_STATE HIGH
DigitalOutputPin led(LED_NUM, false, LED_ACTIVE_STATE);

void setup() {
    Serial.begin(115200);
}

void loop() {
    delay(1000);
    ScopedOn on(led);
    delay(1000);
}