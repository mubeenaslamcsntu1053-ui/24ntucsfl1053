#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
const int LED1_PIN = 18;
const int LED2_PIN = 19;

// PWM Properties
const int freq1 = 1000;    // 1 kHz for LED 1
const int freq2 = 5000;    // 5 kHz for LED 2
const int channel1 = 0;
const int channel2 = 1;
const int resolution = 8;  // 8-bit resolution (0 - 255)

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();

  // Configure LEDC channels (Updated for ESP32 Arduino Core v3.x)
  ledcAttach(LED1_PIN, freq1, resolution);
  ledcAttach(LED2_PIN, freq2, resolution);
}

void loop() {
  // Fade both LEDs up and down
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle += 5) {
    ledcWrite(channel1, dutyCycle);
    ledcWrite(channel2, 255 - dutyCycle);

    int percent1 = (dutyCycle * 100) / 255;
    int percent2 = ((255 - dutyCycle) * 100) / 255;

    // Update OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    display.setCursor(0, 0);
    display.println(F("PWM MONITOR"));
    
    display.setCursor(0, 20);
    display.print(F("LED1: "));
    display.print(percent1);
    display.print(F("%"));
    
    display.setCursor(0, 30);
    display.print(F("F:"));
    display.print(freq1);
    display.println(F("Hz"));
    
    display.setCursor(0, 45);
    display.print(F("LED2: "));
    display.print(percent2);
    display.print(F("%"));
    
    display.setCursor(0, 55);
    display.print(F("F:"));
    display.print(freq2);
    display.println(F("Hz"));
    
    display.display();
    delay(30);
  }

  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle -= 5) {
    ledcWrite(channel1, dutyCycle);
    ledcWrite(channel2, 255 - dutyCycle);

    int percent1 = (dutyCycle * 100) / 255;
    int percent2 = ((255 - dutyCycle) * 100) / 255;

    // Update OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    display.setCursor(0, 0);
    display.println(F("PWM MONITOR"));
    
    display.setCursor(0, 20);
    display.print(F("LED1: "));
    display.print(percent1);
    display.print(F("%"));
    
    display.setCursor(0, 30);
    display.print(F("F:"));
    display.print(freq1);
    display.println(F("Hz"));
    
    display.setCursor(0, 45);
    display.print(F("LED2: "));
    display.print(percent2);
    display.print(F("%"));
    
    display.setCursor(0, 55);
    display.print(F("F:"));
    display.print(freq2);
    display.println(F("Hz"));
    
    display.display();
    delay(30);
  }
}