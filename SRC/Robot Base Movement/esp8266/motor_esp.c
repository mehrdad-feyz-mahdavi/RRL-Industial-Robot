#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char* ssid = "mehrdad";
const char* password = "12345678";
const char* host = "laptop.local";
const uint16_t port = 3001;

WiFiClient client;
unsigned long lastReconnect = 0;
const unsigned long RECONNECT_INTERVAL = 1000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // LED off
  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
  
  if (!MDNS.begin("robot")) {
  } 
  
  connectToServer();
}

void loop() {
  if (!client.connected()) {
    if (millis() - lastReconnect > RECONNECT_INTERVAL) {
      connectToServer();
      lastReconnect = millis();
    }
    // return;
  }

  // Forward laptop → STM32
  if (client.available()) {
    String cmd = client.readStringUntil('E');
    Serial.print(cmd);
    Serial.print("E");
    digitalWrite(LED_BUILTIN, 1);
  }

  // Forward STM32 → laptop
  if (Serial.available()) {
    String response = Serial.readStringUntil('E');
    client.println(response);
  }
}

void connectToServer() {
  digitalWrite(LED_BUILTIN, HIGH); // LED on = connecting
  
  if (client.connect(host, port)) {
    digitalWrite(LED_BUILTIN, HIGH); // LED off = connected
    client.println("MOV"); // Identification
  } 
  // else {
  //   // Fallback to direct IP
  //   client.connect("192,168,61,123", port); // Replace with laptop IP
  // }
  digitalWrite(LED_BUILTIN, LOW); // LED on = connecting
}
