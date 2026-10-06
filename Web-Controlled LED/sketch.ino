#include <WiFi.h>
#include <WebServer.h>

// Wokwi Virtual Wi-Fi Credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int LED_PIN = 4;

// Initialize WebServer on default HTTP port 80
WebServer server(80);

// HTML Page Generator
void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; margin-top: 50px; background-color: #f4f4f4; }";
  html += ".btn { display: inline-block; padding: 15px 30px; font-size: 20px; color: white; text-decoration: none; border-radius: 8px; margin: 10px; }";
  html += ".btn-on { background-color: #4CAF50; }";
  html += ".btn-off { background-color: #f44336; }";
  html += "</style></head><body>";
  html += "<h1>ESP32 Web Controlled LED</h1>";
  html += "<p>Click a button to change LED state:</p>";
  html += "<a href=\"/led/on\" class=\"btn btn-on\">TURN ON</a>";
  html += "<a href=\"/led/off\" class=\"btn btn-off\">TURN OFF</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(LED_PIN, HIGH);
  server.sendHeader("Location", "/"); 
  server.send(303);
}

void handleLEDOff() {
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/"); 
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Connect to Wokwi virtual network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

Serial.println("\nWiFi Connected!");
Serial.print("Open in Wokwi Browser: ");
Serial.print("http://");
Serial.println(WiFi.localIP());

  // Set up URL routing
  server.on("/", handleRoot);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Listen for and handle incoming HTTP client requests
  server.handleClient();
}
