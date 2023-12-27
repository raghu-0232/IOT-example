#include <M5Atom.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "secrets/Secrets.h"

#define DHTPIN 25 // M5Atom uses GPIO 25 for DHT
#define DHTTYPE DHT11
const long interval = 10000; 

// Class Definitions
class DHTSensor {
public:
    DHT dht;
    DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}
    void begin() { dht.begin(); }
    float readTemperature() { return dht.readTemperature(); }
    float readHumidity() { return dht.readHumidity(); }
};

class MQTTManager {
private:
    PubSubClient client;
public:
    MQTTManager(WiFiClientSecure& espClient) : client(espClient) {}
    void begin(const char* broker, uint16_t port) {
        client.setServer(broker, port);
    }
    bool isConnected() { return client.connected(); }
    void connect(const char* clientId) {
        while (!client.connected()) {
            if (client.connect(clientId)) {
                Serial.println("Connected to MQTT broker");
            } else {
                Serial.print("Failed, rc=");
                Serial.print(client.state());
                Serial.println(" Retrying in 5 seconds");
                delay(5000);
            }
        }
    }
    bool publish(const char *topic, const String &payload, int qos) {
        return client.publish(topic, payload.c_str(), qos);
    }
};

// Global Objects
DHTSensor dhtSensor(DHTPIN, DHTTYPE);
WiFiClientSecure espClient;
MQTTManager mqttManager(espClient);

// Function Declarations
void setupWiFi();
void publishSensorData();

void setup() {
    M5.begin();
    Serial.begin(115200);
    dhtSensor.begin();

    setupWiFi();

    espClient.setCACert(rootCACertificate);
    espClient.setCertificate(clientCertificate);
    espClient.setPrivateKey(clientPrivateKey);

    mqttManager.begin(mqttBroker, mqttPort);
}

void loop() {
    M5.update();

    if (!mqttManager.isConnected()) {
        mqttManager.connect("M5AtomClient");
    }

    publishSensorData();
    delay(1000); // Consider using a non-blocking delay
}

void setupWiFi() {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println(".");
    }
    Serial.println("Connected to WiFi, IP address: " + WiFi.localIP().toString());
}

void publishSensorData() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        float temperature = dhtSensor.readTemperature();
        float humidity = dhtSensor.readHumidity();

        if (!isnan(temperature) && !isnan(humidity)) {
            String payload = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
            if (mqttManager.publish(mqttTopic, payload, 1)) {
                Serial.println("Data published to MQTT");
            } else {
                Serial.println("Failed to publish data to MQTT. Retrying in 5 seconds...");
            }
        } else {
            Serial.println("Sensor read error");
        }
    }
}
