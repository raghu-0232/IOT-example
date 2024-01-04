// Secrets.h

// Wi-Fi credentials
const char *ssid = "Ravi";
const char *password = "7093081041";
const char *mqttBroker = "65.0.144.52";  // Replace with your MQTT broker address
const int mqttPort = 1883;  // Default MQTT port
const char *mqttUser = "raghu";  // Replace with your MQTT username
const char *mqttPassword = "123456";  // Replace with your MQTT password



// secrets.h

// WiFi Credentials
const char* ssid = "Ravi"; // Replace with your WiFi SSID
const char* password = "7093081041"; // Replace with your WiFi password

// MQTT Broker Settings
const char* mqtt_server = "devopsonsensors.com"; // Replace with your MQTT broker address
const int mqtt_port = 8883; // MQTT SSL port, usually 8883

// SSL Certificate for the MQTT broker
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \

"-----END CERTIFICATE-----\n";
