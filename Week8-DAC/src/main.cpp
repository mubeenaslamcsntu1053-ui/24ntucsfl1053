// Name: Mubeen 
// Week 8 DAC Part 3

#include <Arduino.h>

#define DAC_PIN 25
#define PWM_PIN 16

void setup()
{
    Serial.begin(115200);

    // ESP32 Core v3.x ka naya tareeqa
    ledcAttach(PWM_PIN, 5000, 8);
}

void loop()
{
    // DAC output code 128
    dacWrite(DAC_PIN, 128);

    // PWM duty value 128 (50% duty cycle)
    ledcWrite(PWM_PIN, 128);

    Serial.println("DAC=128 | PWM duty=128");

    delay(1000);
}