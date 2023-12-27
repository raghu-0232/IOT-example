#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "secrets/Secrets.h"

#define DHTPIN 25  // M5Atom uses GPIO 25 for DHT
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

float t = 0.0;
float h = 0.0;

const long interval = 10000;
unsigned long previousMillis = 0;

void setup() {
  M5.begin();
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  Serial.println(WiFi.localIP());

  client.setServer(mqttBroker, mqttPort);
}

void loop() {
  M5.update();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    if (!isnan(newT)) {
      t = newT;
    }

    float newH = dht.readHumidity();
    if (!isnan(newH)) {
      h = newH;
    }

    if (!client.connected()) {
      reconnect();
    }

    if (t == 0.0 && h == 0.0) {
      if (publishToMQTT("test", "Sensor not connected or error occurred", 1)) {
        Serial.println("Error message published to MQTT");
      } else {
        Serial.println("Failed to publish error message to MQTT. Retrying in 5 seconds...");
      }
    } else {
      String payload = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";
      if (publishToMQTT("test", payload, 1)) {
        Serial.println("Data published to MQTT");
      } else {
        Serial.println("Failed to publish data to MQTT. Retrying in 5 seconds...");
      }
    }

    delay(1000);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("M5AtomClient")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds");
      delay(5000);
    }
  }
}

bool publishToMQTT(const char *topic, const String &payload, int qos) {
  // Convert String payload to a character array.
  const char* charPayload = payload.c_str();

  // Publish with the correct parameters - topic, payload, and QoS
  if (client.publish(topic, charPayload, qos)) {
    return true;
  } else {
    Serial.print("Failed to publish to topic ");
    Serial.print(topic);
    Serial.println(". Retrying...");
    return false;
  }
}
