#include <ArduinoPin.h>
#include <Arduino.h>

void buttonChanged() {
    Serial.println("Button changed");
}

#define BUTTON_NUM 3
#define BUTTON_ACTIVE_STATE LOW
DigitalPulledPin button(BUTTON_NUM, BUTTON_ACTIVE_STATE);

#define LED_NUM 4
#define LED_ACTIVE_STATE HIGH
DigitalOutputPin led(LED_NUM, false, LED_ACTIVE_STATE);

void setup() {
    Serial.begin(115200);
    button.attachInterrupt(buttonChanged, CHANGE);
}

void loop() {
    led = button;
}