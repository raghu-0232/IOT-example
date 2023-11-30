# Solar-Powered ESP8266 DHT11 Temperature and Humidity Monitoring Project

This project involves creating a solar-powered temperature and humidity monitoring system using an ESP8266 microcontroller with a DHT11 sensor. The system is powered by a lithium-ion battery charged through a TP4056 charging module using solar cells. Collected data is sent to a MySQL database, and a Flask web application is used to display the latest values.

## Components Used

- ESP8266 microcontroller
- DHT11 temperature and humidity sensor
- Lithium-ion battery
- TP4056 charging module
- Solar cell
- MySQL database
- Python (Flask) for web application

## Project Overview

1. **Arduino Setup (ESP8266):**
   - Use the Arduino IDE to program the ESP8266 to read data from the DHT11 sensor.
   - Set up the ESP8266 to send temperature and humidity data to a specific IP address.

2. **Power Management:**
   - Utilize a lithium-ion battery as the power source for the ESP8266.
   - Implement a TP4056 charging module to charge the battery using a solar cell.

3. **MySQL Database Setup:**
   - Install MySQL server on your chosen platform.
   - Create a new database (`esp8266`) and a table (`sensor_data`) to store temperature and humidity values.

4. **Python Script (Sensor Data Insertion):**
   - Write a Python script (`insert_into_database.py`) to insert temperature and humidity data into the MySQL database.
   - Update the database configuration (`db_config`) and ESP8266 IP address (`esp_ip`) in the script.

5. **Flask Web Application Setup:**
   - Write a Flask web application (`app.py`) to display the latest temperature and humidity values.
   - The web application queries the MySQL database for the most recent data and renders an HTML template (`templates/index.html`).

6. **How to Run:**
   - Run the `insert_into_database.py` script to start collecting and inserting sensor data into the MySQL database.
   - Run the Flask web application (`app.py`) to start the web server.
   - Access the web application in a browser at `http://127.0.0.1:5000/` to view the latest temperature and humidity values.


## Notes

- Ensure that the required Python packages (`requests`, `datetime`, `time`, `mysql.connector`) are installed.
- Make sure the ESP8266 is correctly configured to send data to the server running the `insert_into_database.py` script.

Feel free to customize and expand the project based on your requirements.

