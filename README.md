---

# ESP32-based Temperature and Humidity Monitoring System

This project demonstrates a complete IoT setup for monitoring temperature and humidity using an ESP32-based M5 Atom microcontroller with a DHT11 sensor. The data is sent to a Mosquitto MQTT broker running on an AWS EC2 instance, stored in a MySQL database, and displayed through a Node.js web server. The system uses SSL for secure communication.

## System Overview

- **ESP32 M5 Atom Controller**: Reads temperature and humidity data from a DHT11 sensor and publishes it to the MQTT broker.
- **Mosquitto MQTT Broker**: Hosted on AWS EC2, receives data from ESP32 and relays it to the web server and database.
- **MySQL Database**: Stores temperature and humidity data received from the MQTT broker.
- **Node.js Web Server**: Displays the sensor data on a webpage and interacts with the MySQL database.

## Prerequisites

- An AWS account with an EC2 instance.
- Domain name for SSL configuration.
- ESP32 M5 Atom microcontroller and DHT11 sensor.
- Basic knowledge of MQTT, Node.js, and MySQL.

## Components

1. **AWS EC2 Instance**: Running Ubuntu 20.04 with Mosquitto MQTT broker, MySQL server, and Node.js web server.
2. **Mosquitto MQTT Broker**: Installed on EC2, configured with SSL.
3. **MySQL Server**: Running on EC2, secured with SSL.
4. **Node.js Web Server**: Serves a webpage to display sensor data, communicates with MQTT broker and MySQL database, secured with SSL.
5. **ESP32 M5 Atom**: Programmed to read data from the DHT11 sensor and publish it to the MQTT broker.

## Setup

### MQTT Broker Setup

1. Install and configure Mosquitto MQTT broker on EC2.
2. Secure the broker with SSL (use Let's Encrypt or similar).

### MySQL Database Setup

1. Install MySQL on EC2.
2. Secure the database with SSL and set up tables for storing sensor data.

### Node.js Web Server Setup

1. Install Node.js and set up a server to interface with the MQTT broker and MySQL database.
2. Implement SSL for secure HTTP requests.

### ESP32 M5 Atom Setup

1. Connect the DHT11 sensor to the ESP32.
2. Program the ESP32 to read sensor data and publish it to the MQTT broker.

## Usage

- The ESP32 reads temperature and humidity data and sends it to the MQTT broker.
- The broker relays this data to the MySQL database and the Node.js server.
- The Node.js server displays this data on a webpage.

## Possible Additions

- **Data Visualization**: Implement charts or graphs on the web interface for better data representation.
- **Real-time Data Updates**: Use WebSocket or AJAX for real-time updates on the webpage.
- **Security Enhancements**: Ensure all components follow best security practices, like using secure MQTT (MQTTS), HTTPS, and secure database connections.
- **Backup and Recovery**: Implement backup strategies for the database to handle data recovery.

## Conclusion

This project sets up a complete IoT system for temperature and humidity monitoring using an ESP32-based M5 Atom controller, AWS EC2, Mosquitto MQTT broker, MySQL database, and a Node.js web server.

---

Remember to replace placeholders like `example.com` with your actual domain and provide specific setup instructions or scripts if you have them. This README provides a general overview and setup guide for your project.
