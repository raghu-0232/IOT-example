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


# Setting up Arduino IDE for ESP8266 Development

## Install Arduino IDE

1. **Download Arduino IDE:**
   - Visit the [Arduino Software](https://www.arduino.cc/en/Main/Software) page.
   - Download the latest version of Arduino IDE suitable for your operating system (Windows, macOS, or Linux).

2. **Install Arduino IDE:**
   - Follow the installation instructions provided for your operating system.
   - Launch Arduino IDE after installation.

## Install CH340 Drivers

1. **Download CH340 Drivers:**
   - If you are using a NodeMCU or other ESP8266 boards with a CH340 USB-to-serial chip, download the CH340 drivers.
   - Search for "CH340 driver" on your preferred search engine.
   - Download and install the driver suitable for your operating system.

2. **Install CH340 Drivers:**
   - Follow the installation instructions provided with the driver.
   - After installation, restart your computer to apply the changes.

## Install ESP8266 Board Support

1. **Open Arduino IDE:**
   - Launch Arduino IDE on your computer.

2. **Open Preferences:**
   - Navigate to `File > Preferences` in the Arduino IDE.

3. **Add ESP8266 Board Manager URL:**
   - In the Preferences window, find the "Additional Boards Manager URLs" field.
   - Add the following URL:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```

4. **Install ESP8266 Boards:**
   - Open the Boards Manager: `Tools > Board > Boards Manager`.
   - Type "esp8266" in the search bar.
   - Select "esp8266" by ESP8266 Community.
   - Click "Install" to download and install the ESP8266 boards.

5. **Select ESP8266 Board:**
   - After installation, select your ESP8266 board from `Tools > Board` menu.
   - Choose the appropriate board variant based on your ESP8266 module.

## Install ESP8266 Libraries

1. **Open Library Manager:**
   - Go to `Sketch > Include Library > Manage Libraries`.

2. **Install DHT Library:**
   - In the Library Manager, search for "DHT" and install the "DHT sensor library" by Adafruit.

3. **Install Additional Libraries:**
   - Depending on your project requirements, search for and install additional libraries as needed.

## Verify Installation

1. **Verify ESP8266 Board:**
   - Write a simple Arduino sketch for your ESP8266 board.
   - Select your board and COM port under `Tools` menu.
   - Click the "Verify" (checkmark) icon to compile the sketch.

2. **Upload to ESP8266:**
   - Connect your ESP8266 to your computer.
   - Click the "Upload" (right arrow) icon to compile and upload the sketch to your ESP8266.

3. **Open Serial Monitor:**
   - Open the Serial Monitor (`Tools > Serial Monitor`) to view serial output from your ESP8266.

Congratulations! Your Arduino IDE is now set up for ESP8266 development, and you can start creating projects for your ESP8266 board.


