#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include "secrets/Secrets.h"  // Include your WiFi and MQTT settings

#define DHTPIN 25
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure espClient;
PubSubClient client(espClient);

const int deepSleepTime = 2 * 60 * 1000000;  // Deep sleep time in microseconds (2 minutes)

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectToMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker.");
      client.subscribe("yourTopic");  // Subscribe to your topic
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
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
      Serial.println("Sensor data published to test topic.");
    } else {
      Serial.println("Failed to publish sensor data.");
    }
  } else {
    Serial.println("Failed to read from DHT sensor.");
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

  Serial.println("Waking up, starting system...");

  connectToWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  espClient.setCACert(ca_cert);

  reconnectToMQTT();
  client.loop();
  publishSensorData();

  Serial.println("Going to deep sleep now...");
  esp_sleep_enable_timer_wakeup(deepSleepTime);
  esp_deep_sleep_start();
}

void loop() {
  // Empty - operations are in setup, as setup is called after each deep sleep wake-up
}
