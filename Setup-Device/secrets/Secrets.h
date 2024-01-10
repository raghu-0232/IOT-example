// secrets.h

// WiFi Credentials
const char* ssid = "Ravi"; // Replace with your WiFi SSID
const char* password = "7093081041"; // Replace with your WiFi password

// MQTT Broker Settings
const char* mqtt_server = "devopsonsensors.com"; // Replace with your MQTT broker address
const int mqtt_port = 8883; // MQTT SSL port, usually 8883
const char* mqttTopic = "test";
// SSL Certificate for the MQTT broker
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"
"-----END CERTIFICATE-----\n";
