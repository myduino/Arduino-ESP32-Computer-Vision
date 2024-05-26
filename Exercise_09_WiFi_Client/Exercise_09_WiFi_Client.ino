#include <WiFi.h>

const char ssid[] = "";
const char password[] = "";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }
}