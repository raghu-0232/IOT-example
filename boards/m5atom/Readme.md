# ESP32 MQTT Client with SSL/TLS

This project demonstrates how to connect an ESP32 to an MQTT broker using SSL/TLS for secure communication. It includes the functionality to handle WiFi and MQTT reconnections and publish messages in JSON format.

## Features

- **WiFi Connectivity**: Connects to a WiFi network.
- **MQTT SSL/TLS Communication**: Communicates with an MQTT broker over a secure SSL/TLS connection.
- **Reconnection Handling**: Automatically attempts to reconnect to WiFi and MQTT broker if the connection is lost.
- **JSON Messaging**: Publishes messages in JSON format.
- **Offline Message Handling**: Stores a message when offline and sends it when reconnected to avoid data loss.

## Hardware Requirements

- ESP32 Development Board
- M5Atom (Optional, for advanced integration)

## Software Dependencies

- [ArduinoJson](https://arduinojson.org/): For handling JSON serialization.
- [PubSubClient](https://github.com/knolleary/pubsubclient): For MQTT communication.
- Arduino IDE or compatible IDE for code compilation and ESP32 programming.

## Setup and Configuration

1. **WiFi Configuration**:
   - Set your WiFi credentials (`ssid` and `password`) in the `secrets/Secrets.h` file.

2. **MQTT Broker Configuration**:
   - Define your MQTT broker settings (`mqtt_server` and `mqtt_port`) in the `secrets/Secrets.h` file.
   - Include your broker's SSL/TLS CA certificate in the `secrets/Secrets.h` file.

3. **JSON Message Format**:
   - The default message format is `{"message": "Hello MQTT"}`.
   - Modify the `publishTestMessage` function for custom message formats.

4. **Upload the Code**:
   - Compile and upload the code to your ESP32 using Arduino IDE.

## Usage

Once the ESP32 is powered and the code is running:

- The ESP32 will automatically connect to the configured WiFi network.
- After connecting to WiFi, it will establish a secure connection with the MQTT broker.
- The ESP32 will publish a JSON message every 10 seconds.
- In case of WiFi or MQTT disconnection, the ESP32 will try to reconnect.
- If disconnected, the ESP32 will store a message and send it upon reconnection.

## Troubleshooting

- Ensure the correct WiFi credentials and MQTT broker details are provided.
- Verify the CA certificate matches your MQTT broker's SSL/TLS certificate.
- Check the Serial Monitor for connection logs and error messages.

