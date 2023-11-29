#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Ravi"
#define STAPSK "7093081041"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const int ledPin = LED_BUILTIN;
bool printedIP = false;

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address only once
  if (!printedIP) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    printedIP = true;  // Set the flag to true to indicate that the IP has been printed
  }

  // Turn on the built-in LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Note: LOW turns the LED on (active low)
}

void loop() {
  // Your loop can remain empty or contain other non-Wi-Fi-related code.
  // This sketch is now simplified to focus on Wi-Fi connection.
}
