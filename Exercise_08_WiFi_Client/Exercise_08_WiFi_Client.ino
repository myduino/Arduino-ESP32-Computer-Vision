#include <WiFi.h>

// Replace with your network credentials
const char ssid[] = "";
const char password[] = "";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi: " + String(ssid) + " ...");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }
  Serial.println(" connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
}