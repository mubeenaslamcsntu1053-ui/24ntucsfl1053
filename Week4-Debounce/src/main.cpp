// Week3-Lecture1
// Interrupt (External Button) with Debounce
// Embedded IoT System Fall-2026

// Name: Umm E salma
// Reg#: 24-Ntu-Cs-Fl-1095

#include <Arduino.h>

#define BUTTON_PIN 32
#define LED_PIN 4

hw_timer_t *debounceTimer = NULL;

volatile bool debounceActive = false;

void IRAM_ATTR onButtonISR()
{
    if (!debounceActive)
    {
        debounceActive = true;

        // Reset timer
        timerWrite(debounceTimer, 0);

        // 50 ms one-shot timer
        timerAlarmWrite(debounceTimer, 50000, false);
        timerAlarmEnable(debounceTimer);
    }
}

void IRAM_ATTR onDebounceTimer()
{
    // Check button again after 50 ms
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        // Valid button press
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }

    debounceActive = false;
}

void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    // Timer: 1 MHz = 1 microsecond per tick
    debounceTimer = timerBegin(0, 80, true);

    timerAttachInterrupt(debounceTimer, &onDebounceTimer, true);

    // Button interrupt
    attachInterrupt(
        digitalPinToInterrupt(BUTTON_PIN),
        onButtonISR,
        FALLING
    );
}

void loop()
{
    // Main program continues normally
}