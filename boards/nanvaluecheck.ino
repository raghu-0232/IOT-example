#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi and MQTT Broker Settings
const char* ssid = "Ravi";
const char* password = "7093081041";
const char* mqttBroker = "65.0.144.52";
const int mqttPort = 1883;
const char* mqttUser = "raghu";
const char* mqttPassword = "123456";

// DHT Sensor Settings
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

// Active and Sleep Duration Settings
const long activeDuration = 60000; // 1 minute in milliseconds
const long sleepDuration = 120e6;  // 2 minutes in microseconds

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Turn on the LED

  // Full WiFi reset
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  delay(100);

  // Reconnect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());

  // Initialize MQTT connection
  client.setServer(mqttBroker, mqttPort);
  reconnect();

  unsigned long startMillis = millis();
  while (millis() - startMillis < activeDuration) {
    readSensorAndPublish();
    delay(10000); // Wait for 10 seconds before next reading
  }

  digitalWrite(LED_BUILTIN, HIGH); // Turn off the LED before sleeping

  // Go to Deep Sleep
  ESP.deepSleep(sleepDuration);
}

void loop() {
  // Empty - all operations are done in setup as the ESP restarts after deep sleep
}

void readSensorAndPublish() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (don't publish).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String payload = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
  client.publish("test", payload.c_str());
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT Broker!");
    } else {
      Serial.print("Failed to connect to MQTT Broker. Error State: ");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds");
      delay(5000);
    }
  }
}
