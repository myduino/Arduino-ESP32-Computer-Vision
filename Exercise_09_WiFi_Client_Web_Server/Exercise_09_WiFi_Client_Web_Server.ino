#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "";
const char* password = "";
const char* yourName = "";

// Create an instance of the web server running on port 80
WebServer server(80);

// Function to handle requests to the root URL
void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32 " + String(yourName));
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to Wi-Fi: " + String(ssid) + " ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server
  server.on("/", handleRoot);  // Associate the handler function to the root URL
  
  server.begin();  // Start the server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // Listen for incoming clients
}
