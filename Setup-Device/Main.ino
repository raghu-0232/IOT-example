// Include necessary libraries
#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // For handling JSON serialization
#include "secrets/Secrets.h"  // Contains WiFi and MQTT settings

// Global variables
String offlineMessage; // Stores the message when offline
bool hasOfflineMessage = false; // Flag to check if there's an offline message

// Initialize the WiFi and MQTT client objects
WiFiClientSecure espClient; // For SSL/TLS connection
PubSubClient client(espClient); // MQTT client

// Function to connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // Connect to WiFi network
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP()); // Print the IP address
}

// Function to publish a test message
void publishTestMessage() {
  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    // Store the message if not connected
    offlineMessage = "Hello MQTT";
    hasOfflineMessage = true;
  } else {
    // Create a JSON document
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["message"] = "Hello MQTT";
    char jsonBuffer[256];
    serializeJson(jsonDoc, jsonBuffer); // Serialize JSON object to string

    // Publish the JSON string to the MQTT topic
    client.publish("test", jsonBuffer);
    Serial.println("JSON message published to test topic");
  }
}

// Function to reconnect to MQTT broker
void reconnectToMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected");
      client.subscribe("yourTopic"); // Subscribe to a topic
      
      // Check if there's an offline message
      if (hasOfflineMessage) {
        client.publish("test", offlineMessage.c_str());
        Serial.println("Offline message published to test topic");
        hasOfflineMessage = false; // Reset flag
      }
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds");
      delay(5000);
    }
  }
}

// Callback function to handle incoming messages
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]); // Print each byte of the message
  }
  Serial.println();
}

// Setup function
void setup() {
  Serial.begin(115200); // Start serial communication
  connectToWiFi(); // Connect to WiFi
  client.setServer(mqtt_server, mqtt_port); // Set MQTT server and port
  client.setCallback(callback); // Set the callback function
  espClient.setCACert(ca_cert); // Set the CA certificate for SSL/TLS
}

// Main loop function
void loop() {
  // Check MQTT connection
  if (!client.connected()) {
    reconnectToMQTT(); // Reconnect if disconnected
  } else {
    client.loop(); // Maintain MQTT connection
    unsigned long currentMillis = millis();
    static unsigned long lastPublishTime = 0;
    // Publish a message every 10 seconds
    if (currentMillis - lastPublishTime >= 10000) {
      lastPublishTime = currentMillis;
      publishTestMessage(); // Publish test message
    }
  }
}
