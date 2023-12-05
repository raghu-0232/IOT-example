#include <M5Atom.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char *ssid = "Ravi";
const char *password = "7093081041";
const char *mqttBroker = "65.0.144.52";  // Replace with your MQTT broker address
const int mqttPort = 1883;  // Default MQTT port
const char *mqttUser = "raghu";  // Replace with your MQTT username
const char *mqttPassword = "123456";  // Replace with your MQTT password

#define DHTPIN 25  // M5Atom uses GPIO 25 for DHT
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

float t = 0.0;
float h = 0.0;

const long interval = 10000;
unsigned long previousMillis = 0;

void setup()
{
  M5.begin();
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

  client.setServer(mqttBroker, mqttPort);
}

void loop()
{
  M5.update();
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

    // Connect to MQTT broker
    if (!client.connected())
    {
      reconnect();
    }

    // Create JSON payload
    String payload = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";

    // Publish payload to MQTT topic
    client.publish("m5Atom/dht", payload.c_str());

    delay(1000); // Wait for a moment before the next reading
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("M5AtomClient"))
    {
      Serial.println("Connected to MQTT broker");
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
