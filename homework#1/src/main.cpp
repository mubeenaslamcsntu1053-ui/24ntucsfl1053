// home work 2 task 1
// Name: Mubeen Aslam
// Reg no: 24-NTU-CS-FL-1053

#include <Arduino.h>

const int redLed = 18;
const int yellowLed = 19;

const int redChannel = 0;
const int yellowChannel = 2;

const int redFrequency = 1000;
const int yellowFrequency = 5000;
const int resolution = 8;

int redDuty = 0;
int yellowDuty = 255;

int redStep = 5;
int yellowStep = -5;

void setup() {
  ledcSetup(redChannel, redFrequency, resolution);
  ledcSetup(yellowChannel, yellowFrequency, resolution);

  ledcAttachPin(redLed, redChannel);
  ledcAttachPin(yellowLed, yellowChannel);
}

void loop() {
  ledcWrite(redChannel, redDuty);
  ledcWrite(yellowChannel, yellowDuty);

  redDuty += redStep;
  yellowDuty += yellowStep;

  if (redDuty >= 255) {
    redDuty = 255;
    redStep = -5;
  }

  if (redDuty <= 0) {
    redDuty = 0;
    redStep = 5;
  }

  if (yellowDuty >= 255) {
    yellowDuty = 255;
    yellowStep = -5;
  }

  if (yellowDuty <= 0) {
    yellowDuty = 0;
    yellowStep = 5;
  }

  delay(30);
}