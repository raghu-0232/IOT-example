/**
 * DHT11 Temperature Reader with Wi-Fi Connection and Web Server for ESP8266
 * This sketch reads temperature data from the DHT11 sensor, prints the value to the serial port,
 * establishes a Wi-Fi connection, and creates a simple web server to display the temperature.
 * The built-in LED is turned on only when connected.
 *
 * Author: Dhruba Saha (Temperature Reader), Raghu (Wi-Fi Connection & Web Server)
 * Version: 1.0.0
 * License: MIT
 */

#include <ESP8266WiFi.h>
#include <DHT11.h>
#include <ESP8266WebServer.h>

// If STASSID is not defined, set default Wi-Fi credentials
#ifndef STASSID
#define STASSID "Ravi"
#define STAPSK "7093081041"
#endif

// Define Wi-Fi credentials
const char* ssid = STASSID;
const char* password = STAPSK;

// Create an instance of the DHT11 class.
DHT11 dht11(12);  // Connect the sensor to Digital I/O Pin 12.

// Create an instance of the ESP8266WebServer class
ESP8266WebServer server(80);

// Flag to track if the IP address has been printed
bool printedIP = false;

void setup() {
  // Begin serial communication at a baud rate of 115200
  Serial.begin(115200);

  // Print messages to indicate the beginning of the setup process
  Serial.println();
  Serial.println("DHT11 Temperature Reader with Wi-Fi Connection and Web Server");
  Serial.println("Initializing...");

  // Set up the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Initially turn off the LED

  // Connect to Wi-Fi
  connectToWiFi();

  // Set up the web server
  setupServer();

  // Print a new line to separate the setup messages
  Serial.println("Setup complete.");
}

void loop() {
  // Handle web server requests
  server.handleClient();

  // Attempt to read the temperature value from the DHT11 sensor.
  int temperature = dht11.readTemperature();

  // Check the result of the reading.
  // If there's no error, print the temperature value.
  // If there's an error, print the appropriate error message.
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println(DHT11::getErrorString(temperature));
  }

  // Check Wi-Fi connection and update LED status
  checkWiFiStatus();

  // Wait for 10 seconds before the next reading.
  delay(10000);
}

// Function to connect to Wi-Fi
void connectToWiFi() {
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
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    printedIP = true;  // Set the flag to true to indicate that the IP has been printed
  }

  // Turn on the built-in LED (active low) to indicate Wi-Fi connection
  digitalWrite(LED_BUILTIN, LOW);
}

// Function to check Wi-Fi connection status and update LED
void checkWiFiStatus() {
  if (WiFi.status() != WL_CONNECTED) {
    // If not connected, turn off the LED
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // If connected, turn on the LED
    digitalWrite(LED_BUILTIN, LOW);
  }
}

// Function to set up the web server
void setupServer() {
  // Handle requests to the root URL ("/") with the temperature
  server.on("/", HTTP_GET, []() {
    int temperature = dht11.readTemperature();
    String message = "Temperature: " + String(temperature) + " °C";
    server.sendHeader("Content-Type", "text/html; charset=UTF-8");
    server.send(200, "text/html", message);
  });

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}
