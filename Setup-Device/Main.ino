#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <DHT.h>

// Include your WiFi and MQTT settings from secrets file
#include "secrets/Secrets.h"

#define DHTPIN 25
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure espClient;
PubSubClient client(espClient);

const long interval = 10000; // Publishing interval
unsigned long previousMillis = 0;

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

void reconnectToMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected");
      client.subscribe("yourTopic"); // Subscribe to your topic
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds");
      delay(5000);
    }
  }
}

void publishSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["temperature"] = temperature;
    jsonDoc["humidity"] = humidity;
    char jsonBuffer[256];
    serializeJson(jsonDoc, jsonBuffer);

    if (client.publish("test", jsonBuffer)) {
      Serial.println("Sensor data published to test topic");
    } else {
      Serial.println("Failed to publish sensor data. Retrying in 5 seconds...");
    }
  } else {
    Serial.println("Failed to read from DHT sensor!");
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
  M5.begin();
  Serial.begin(115200);
  dht.begin();
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
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      publishSensorData();
    }
  }
}
