#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // Include the ArduinoJson library
#include "secrets/Secrets.h"  // Make sure this file contains your WiFi and MQTT settings

String offlineMessage;
bool hasOfflineMessage = false;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void publishTestMessage() {
  if (WiFi.status() != WL_CONNECTED) {
    // Store message for later if not connected
    offlineMessage = "Hello MQTT";
    hasOfflineMessage = true;
  } else {
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["message"] = "Hello MQTT";
    char jsonBuffer[256];
    serializeJson(jsonDoc, jsonBuffer);

    client.publish("test", jsonBuffer);
    Serial.println("JSON message published to test topic");
  }
}

void reconnectToMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected");
      client.subscribe("yourTopic");

      if (hasOfflineMessage) {
        client.publish("test", offlineMessage.c_str());
        Serial.println("Offline message published to test topic");
        hasOfflineMessage = false; // Reset the flag
      }
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  espClient.setCACert(ca_cert);
}

void loop() {
  if (!client.connected()) {
    reconnectToMQTT();
  } else {
    client.loop();
    unsigned long currentMillis = millis();
    static unsigned long lastPublishTime = 0;
    if (currentMillis - lastPublishTime >= 10000) {
      lastPublishTime = currentMillis;
      publishTestMessage();
    }
  }
}
