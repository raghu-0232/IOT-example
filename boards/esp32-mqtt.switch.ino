#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char *ssid = "Ravi";
const char *password = "7093081041";
const char *mqttBroker = "65.0.144.52";  // Replace with your MQTT broker address
const int mqttPort = 1883;  // Default MQTT port
const char* mqttUser = "raghu";  // Replace with your MQTT username
const char* mqttPassword = "123456";  // Replace with your MQTT password

#define DHTPIN 12
#define DHTTYPE DHT11
int LED_BUILTIN =2;
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

float t = 0.0;
float h = 0.0;

const long interval = 10000;
unsigned long previousMillis = 0;

const int ledPin = LED_BUILTIN; // Built-in LED pin (usually GPIO 2)

void setup()
{
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }

  Serial.println(WiFi.localIP());
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  client.setServer(mqttBroker, mqttPort);
  client.setCallback(callback); // Set the MQTT callback function
  reconnect(); // Connect to MQTT broker
  client.subscribe("switch"); // Subscribe to the "switch" topic
}

void loop()
{
  client.loop(); // Keep the MQTT connection alive

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    if (!isnan(newT))
    {
      t = newT;
    }

    float newH = dht.readHumidity();
    if (!isnan(newH))
    {
      h = newH;
    }

    // Create JSON payload
    String payload = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";

    // Publish payload to MQTT topic
    client.publish("test", payload.c_str());

    delay(1000); // Wait for a moment before the next reading
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle MQTT messages received on subscribed topics
  if (strcmp(topic, "switch") == 0) {
    // Check the payload for the desired action
    if (payload[0] == '1') {
      digitalWrite(ledPin, HIGH); // Turn the LED on
    } else if (payload[0] == '0') {
      digitalWrite(ledPin, LOW); // Turn the LED off
    }
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword))
    {
      Serial.println("Connected to MQTT broker");
      client.subscribe("switch"); // Re-subscribe to the "switch" topic
    }
    else
    {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds");
      delay(5000);
    }
  }
}
