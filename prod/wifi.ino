// This sketch establishes a Wi-Fi connection and turns on the built-in LED when connected.
// It prints the local IP address to the serial monitor.
// Created by: Raghu

#include <ESP8266WiFi.h>

// If STASSID is not defined, set default Wi-Fi credentials
#ifndef STASSID
#define STASSID "Ravi"
#define STAPSK "7093081041"
#endif

// Define Wi-Fi credentials
const char* ssid = STASSID;
const char* password = STAPSK;

// Define the pin number for the built-in LED on the ESP8266
const int ledPin = LED_BUILTIN;

// Flag to track if the IP address has been printed
bool printedIP = false;

// Setup function runs once when the ESP8266 is powered on or reset
void setup() {
  // Begin serial communication at a baud rate of 115200
  Serial.begin(115200);

  // Print messages to indicate the beginning of the setup process
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Set the ESP8266 to be a Wi-Fi client and initiate the connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for the Wi-Fi connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print a new line to separate the Wi-Fi connection messages
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the local IP address only once
  if (!printedIP) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    printedIP = true;  // Set the flag to true to indicate that the IP has been printed
  }

  // Set up the built-in LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Turn on the built-in LED (active low) to indicate Wi-Fi connection
  digitalWrite(ledPin, LOW);
}

// Loop function runs repeatedly after the setup function
void loop() {
  // Your loop can remain empty or contain other non-Wi-Fi-related code.
  // This sketch is now simplified to focus on Wi-Fi connection.
}
