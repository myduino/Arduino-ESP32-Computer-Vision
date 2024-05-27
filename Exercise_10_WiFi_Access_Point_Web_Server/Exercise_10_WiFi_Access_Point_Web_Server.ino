#include <WiFi.h>
#include <WebServer.h>

// Network credentials
const char *ssid = "";
const char *password = "";  // Minimum 8 characters
const char *yourName = "";

// Create an instance of the web server running on port 80
WebServer server(80);

// Function to handle requests to the root URL
void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32 " + String(yourName));
}

void setup() {
  Serial.begin(115200);
  
  // Set up the access point
  Serial.println("Setting Up Wi-Fi Access Point: " + String(ssid));
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP Address: ");
  Serial.println(IP);
  
  // Set up the web server
  server.on("/", handleRoot);  // Associate the handler function to the root URL
  
  server.begin();  // Start the server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // Listen for incoming clients
}
