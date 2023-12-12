# Solar-Powered ESP8266 DHT11 Temperature and Humidity Monitoring Project

This project involves creating a solar-powered temperature and humidity monitoring system using an ESP8266 microcontroller with a DHT11 sensor. The system is powered by a lithium-ion battery charged through a TP4056 charging module using solar cells. Collected data is sent to a MySQL database, and a Node.js web application is used to display the latest values.

## Components Used

- ESP8266 microcontroller
- DHT11 temperature and humidity sensor
- Lithium-ion battery
- TP4056 charging module
- Solar cell
- MySQL database
- Node.js for web application

## Project Overview

1. **Arduino Setup (ESP8266):**
   - Program the ESP8266 with the Arduino IDE to read data from the DHT11 sensor.
   - Configure the ESP8266 to send temperature and humidity data to a specific IP address.

2. **Power Management:**
   - Use a lithium-ion battery as the power source for the ESP8266.
   - Implement a TP4056 charging module to charge the battery using a solar cell.

3. **MySQL Database Setup:**
   - Install MySQL server on your chosen platform.
   - Create a new database (`esp8266`) and a table (`sensor_data`) to store temperature and humidity values.

4. **Node.js Application Setup:**
   - Develop a Node.js web application to display the latest temperature and humidity values.
   - The application queries the MySQL database for the most recent data and renders it on a web page.

5. **How to Run:**
   - Ensure the ESP8266 is sending data to the MySQL database.
   - Run the Node.js web application to start the server.
   - Access the web application in a browser at `http://localhost:3000/` to view the latest temperature and humidity values.

## Notes

- Ensure that the required Node.js packages are installed.
- Make sure the ESP8266 is correctly configured to send data to the server running the Node.js application.

Feel free to customize and expand the project based on your requirements.
