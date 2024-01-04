---

# ESP32 M5Atom Lite Setup with Arduino IDE

This guide provides comprehensive instructions for setting up the Arduino IDE to work with the ESP32 M5Atom Lite microcontroller. It covers the installation of necessary boards, libraries, and details on how to upload code to the device.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Arduino IDE Setup](#arduino-ide-setup)
3. [Connecting DHT11 Sensor to ESP32 M5 Atom](#connecting-dht11-sensor-to-esp32-m5-atom)
4. [Uploading the Code](#uploading-the-code)
5. [Troubleshooting](#troubleshooting)

<a name="prerequisites"></a>
## Prerequisites
- A computer with Arduino IDE installed.
- ESP32 M5Atom Lite microcontroller.
- USB cable for connecting the ESP32 to your computer.

<a name="arduino-ide-setup"></a>
## Arduino IDE Setup

### Step 1: Install Arduino IDE
Download and install the Arduino IDE from the [Arduino website](https://www.arduino.cc/en/software).

### Step 2: Install ESP32 Board in Arduino IDE
1. In Arduino IDE, navigate to `File > Preferences`.
2. Add the following URLs to the "Additional Board Manager URLs" field:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
   Click "OK" to save.
3. Go to `Tools > Board > Boards Manager`, search for "ESP32" and install the "ESP32 by Espressif Systems" board.

### Step 3: Install Required Libraries
1. Go to `Sketch > Include Library > Manage Libraries`.
2. Install the following libraries:
   - `WiFi`
   - `PubSubClient`
   - `ArduinoJson`
   - Additional libraries specific to M5Atom Lite, if required.

### Step 4: Selecting the Board and Port
1. Connect the ESP32 M5Atom Lite to your computer via USB.
2. Select "M5Stick-C" from `Tools > Board`.
3. Choose the correct COM port from `Tools > Port`.

<a name="connecting-dht11-sensor-to-esp32-m5-atom"></a>
## Connecting DHT11 Sensor to ESP32 M5 Atom

### Wiring Diagram
- **GND to GND**: Connect the GND pin of the DHT11 to the GND on the M5 Atom.
- **VCC to 3.3V**: Connect the VCC pin of the DHT11 to a 3.3V pin on the M5 Atom.
- **Data to GPIO 25**: Connect the data pin of the DHT11 to GPIO 25 on the M5 Atom.
- **Power On**: Ensure all connections are secure before powering on the M5 Atom.

<a name="uploading-the-code"></a>
## Uploading the Code
1. Copy the provided code into a new sketch in the Arduino IDE. Ensure the `Secrets.h` file is in the correct directory.
2. With the ESP32 connected, click the "Upload" button in the Arduino IDE.
3. The code will compile and upload to the ESP32. Use the Serial Monitor to view the output.

<a name="troubleshooting"></a>
## Troubleshooting
- Ensure the correct COM port and board are selected in the Arduino IDE.
- Some ESP32 boards might require pressing the boot button during the upload process.
- Verify that all necessary libraries are installed correctly.

---

This README offers a structured guide to setting up and programming the ESP32 M5Atom Lite, including connecting a DHT11 sensor for temperature and humidity measurement.
