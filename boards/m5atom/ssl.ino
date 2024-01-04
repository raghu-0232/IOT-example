#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "secrets/Secrets.h"

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

#include <ArduinoJson.h>  // Include the ArduinoJson library

void publishTestMessage() {
  // Create a JSON object
  StaticJsonDocument<200> jsonDoc; // Adjust size based on your data needs
  jsonDoc["message"] = "Hello MQTT";
  //jsonDoc["timestamp"] = millis();

  // Convert JSON object to string
  char jsonBuffer[256];
  serializeJson(jsonDoc, jsonBuffer);

  // Publish the JSON string to the MQTT topic
  client.publish("test", jsonBuffer);
  Serial.println("JSON message published to test topic");
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

void reconnectToMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected");
      client.subscribe("yourTopic");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds");
      delay(5000);
    }
  }
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
