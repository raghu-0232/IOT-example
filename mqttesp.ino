#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Ravi";
const char* password = "7093081041";
const char* mqttServer = "65.0.144.52";  // Replace with your MQTT broker's IP or domain
const int mqttPort = 1883;  // Default MQTT port
const char* mqttUser = "raghu";  // Replace with your MQTT username
const char* mqttPassword = "123456";  // Replace with your MQTT password

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
    // Handle incoming messages from subscribed topics
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    
    float temperature = 25.5;  // Replace with your temperature value
    float humidity = 60.0;     // Replace with your humidity value

    // Create a string with your data
    String payload = String(temperature) + "," + String(humidity);

    // Publish data to a specific MQTT topic
    client.publish("your_topic", payload.c_str());

    // Wait for a minute before sending the next data point
    delay(60000);
}
