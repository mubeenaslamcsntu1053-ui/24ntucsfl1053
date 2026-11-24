#include <Arduino.h>
#include <WiFi.h>

String encryptionTypeToString(wifi_auth_mode_t authMode) {
  switch (authMode) {
    case WIFI_AUTH_OPEN:
      return "OPEN";
    case WIFI_AUTH_WEP:
      return "WEP";
    case WIFI_AUTH_WPA_PSK:
      return "WPA-PSK";
    case WIFI_AUTH_WPA2_PSK:
      return "WPA2-PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA/WPA2-PSK";
    case WIFI_AUTH_WPA3_PSK:
      return "WPA3-PSK";
    case WIFI_AUTH_WPA2_WPA3_PSK:
      return "WPA2/WPA3-PSK";
    default:
      return "UNKNOWN";
  }
}

void scanNetworks() {
  Serial.println("\nScanning WiFi networks...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  int networkCount = WiFi.scanNetworks();

  if (networkCount == 0) {
    Serial.println("No WiFi networks found.");
  } else if (networkCount < 0) {
    Serial.println("WiFi scan failed.");
  } else {
    Serial.print("Found ");
    Serial.print(networkCount);
    Serial.println(" networks:");
    Serial.println("------------------------------------------------------------");

    for (int i = 0; i < networkCount; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" | RSSI: ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm | Ch: ");
      Serial.print(WiFi.channel(i));
      Serial.print(" | ");
      Serial.println(encryptionTypeToString(WiFi.encryptionType(i)));
      delay(10);
    }
    Serial.println("------------------------------------------------------------");
  }

  WiFi.scanDelete();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 WiFi Scanner Ready");
}

void loop() {
  scanNetworks();
  delay(10000);
}