// secrets.h

// WiFi Credentials
const char* ssid = "ssid"; // Replace with your WiFi SSID
const char* password = "password"; // Replace with your WiFi password

// MQTT Broker Settings
const char* mqtt_server = "mqtt_server.com"; // Replace with your MQTT broker address
const int mqtt_port = 8883; // MQTT SSL port, usually 8883

// SSL Certificate for the MQTT broker
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"
"TzELazCCA1OgAwIBAgIRAIIQz7DSQONZIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"
"cmNoIazCCA1OgAwIBAgIRAIIQz7DSQONIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n"
"WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n"
"-----END CERTIFICATE-----\n";
