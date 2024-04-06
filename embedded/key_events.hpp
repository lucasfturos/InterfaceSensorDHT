#pragma once

// Constants
const uint8_t KEY_SERIAL = 19;
const uint8_t KEY_WIFI = 18;
const uint8_t KEY_BLUETOOTH = 5;

static uint8_t keyEvents() {
    pinMode(KEY_SERIAL, INPUT);
    pinMode(KEY_WIFI, INPUT);
    pinMode(KEY_BLUETOOTH, INPUT);

    if (digitalRead(KEY_SERIAL) == HIGH)
        return 1;
    if (digitalRead(KEY_WIFI) == HIGH)
        return 2;
    if (digitalRead(KEY_BLUETOOTH) == HIGH)
        return 3;

    return 0;
}